#ifndef verlet_hpp
#define verlet_hpp

#include <vector>
#include <random>
#include <string>

#include "particle.hpp"
#include "force.hpp"
#include "field.hpp"
#include "input.hpp"

class verlet
{
	
public:
	
	verlet();
	~verlet();
	
	static double r1;
	static double r2;
	
	std::vector<std::vector<double> > x0_bias_vec; // The space between > and > can be skipped in C++0x.
	std::vector<std::vector<double> > y0_bias_vec;
	std::vector<std::vector<double> > h0_bias_vec;

	void integrator(std::vector<particle*>);
	void update_bias(std::vector<particle*>);
	void update_bias_wt(std::vector<particle*>);
	
	double normal_dist(double, double);
	
private:
	
	double _h; // time step.
	double _h_bias;
	
	double *_alpha;
	double _beta;
	double *_gamma_x;
	
	std::string _metadynamics;
	
	input *_inp;
	field *_ff;
	force *_f;
	
	std::random_device rd;

};

#endif 
