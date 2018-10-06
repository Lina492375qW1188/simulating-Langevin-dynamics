#include <iostream>
#include <math.h>

#include "verlet.hpp"

using std::vector;
using std::string;
using std::cerr;
using std::mt19937;
using std::normal_distribution;

double verlet::r1;
double verlet::r2;

verlet::verlet()
{

    _f = new force;
	_ff = new field;
	_inp = new input;
	
    _h = _inp->h; // time step.
	
	_alpha = _inp->alpha;
	_beta = _inp->beta; // beta=1/temperature.
	_gamma_x = _inp->gamma_x;
	
	_metadynamics = _inp->metadynamics;
	
	// Initialize bias_vec
	int num_of_col = _inp->num_particle;
	int num_of_row = 1;
	double init_value(0.0);
	x0_bias_vec.resize(num_of_col, vector<double>(num_of_row, init_value));
	y0_bias_vec.resize(num_of_col, vector<double>(num_of_row, init_value));
	h0_bias_vec.resize(num_of_col, vector<double>(num_of_row, init_value));
	
}

verlet::~verlet()
{
	
	delete _f;
	delete _ff;
	delete _inp;

}

void verlet::integrator(vector<particle*> qq)
{
	
	double h = _h;
	double beta = _beta;
    double *gamma_x = _gamma_x;
	string metadynamics = _metadynamics;
	
	for(int i=0; i<qq.size(); i++){
		if(qq[i]->x[0] <= 30.5){       // Stop writing while particles reach 3.5.
			for(int j=0; j<qq[i]->num_dim; j++){
				
				double c1 = exp(-gamma_x[j]*0.5*h);
				double c2 = sqrt((1-c1*c1)/beta);
                
				if(metadynamics.compare("none") == 0) _f->set_force(qq[i]);
				else if(metadynamics.compare("normal") == 0) _f->set_force(qq[i], x0_bias_vec[i]);
				else if(metadynamics.compare("well-tempered") == 0) _f->set_force(qq[i], x0_bias_vec[i], h0_bias_vec[i]);
				else if(metadynamics.compare("well-tempered oriented rc") == 0) _f->set_force(qq[i], x0_bias_vec[i], y0_bias_vec[i], h0_bias_vec[i]);
				
				double fd = _f->f[j]; // record current force.
			    
				qq[i]->d[j] = qq[i]->x[j]; // record current position.
				r1 = normal_dist(0.0, 1);
				qq[i]->v[j] = c1*qq[i]->v[j] + c2*r1;
				qq[i]->x[j] += qq[i]->v[j]*h  + 0.5*h*h*_f->f[j]; // update postition.

				if(metadynamics.compare("none") == 0) _f->set_force(qq[i]);
				else if(metadynamics.compare("normal") == 0) _f->set_force(qq[i], x0_bias_vec[i]);
				else if(metadynamics.compare("well-tempered") == 0) _f->set_force(qq[i], x0_bias_vec[i], h0_bias_vec[i]);
				else if(metadynamics.compare("well-tempered oriented rc") == 0) _f->set_force(qq[i], x0_bias_vec[i], y0_bias_vec[i], h0_bias_vec[i]);

				qq[i]->v[j] += 0.5*h*(fd + _f->f[j]);
				r2 = normal_dist(0.0, 1);
				qq[i]->v[j] = c1*qq[i]->v[j] + c2*r2;
				
			}
		}
		else qq[i]->flag = 0; // It will keep running until the end of steps.
	}
	
}

void verlet::update_bias(vector<particle*> qq)
{
	
	for(int i=0; i<qq.size(); i++){
		if(qq[i]->flag == 1){
			x0_bias_vec.at(i).push_back(qq[i]->x[0]); // put current x to the end of x0_bias_vec.
			y0_bias_vec.at(i).push_back(qq[i]->x[1]); // put current y to the end of y0_bias_vec.
		}
	}

}

void verlet::update_bias_wt(vector<particle*> qq)
{
	
	for(int i=0; i<qq.size(); i++){
		if(qq[i]->flag == 1){
		    x0_bias_vec.at(i).push_back(qq[i]->x[0]);
		    y0_bias_vec.at(i).push_back(qq[i]->x[1]);
		    h0_bias_vec.at(i).push_back( _ff->h_bias_wt(x0_bias_vec[i].back(), x0_bias_vec[i], h0_bias_vec[i]) );
	    }
	}

}

double verlet::normal_dist(double mean, double sigma)
{
	
	mt19937 generator(rd());
	normal_distribution<double> distribution(mean, sigma);
	return distribution(generator);
	
}