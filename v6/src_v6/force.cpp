#include <iostream>

#include "force.hpp"

using std::vector;

force::force() // qq1 means each single particle.
{
    
	_ff = new field;
	_inp = new input;
	
	num_dim = _inp->num_dim;
	f = new double[num_dim];
	
}


force::~force()
{
	
	delete _inp;
	delete _ff;
	delete [] f;
	
}

void force::set_force(particle* qq1)
{

	f[0] = _ff->f_x(qq1->x[0], qq1->x[1]);
	f[1] = _ff->f_y(qq1->x[0], qq1->x[1]);

} // It can also be used to set user_defined force.

void force::set_force(particle* qq1, vector<double> x0_bias)
{
	
	f[0] = _ff->f_x(qq1->x[0], qq1->x[1], x0_bias);
	f[1] = _ff->f_y(qq1->x[0], qq1->x[1]);
	
}

void force::set_force(particle* qq1, vector<double> x0_bias, vector<double> h0_bias)
{
	
	f[0] = _ff->f_x(qq1->x[0], qq1->x[1], x0_bias, h0_bias);
	f[1] = _ff->f_y(qq1->x[0], qq1->x[1]);
	
}

void force::set_force(particle* qq1, vector<double> x0_bias, vector<double> y0_bias, vector<double> h0_bias)
{
	f[0] = _ff->f_x(qq1->x[0], qq1->x[1], x0_bias, y0_bias, h0_bias);
	f[1] = _ff->f_y(qq1->x[0], qq1->x[1], x0_bias, y0_bias, h0_bias);
}
