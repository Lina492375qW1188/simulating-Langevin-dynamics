#ifndef force_hpp
#define force_hpp

#include <vector>

#include "particle.hpp"
#include "field.hpp"
#include "input.hpp"

class force
{
	
public:
	
	force();
	~force();
	int num_dim;
	double *f;
	
	void set_force(particle*);
	void set_force(particle*, std::vector<double>);
	void set_force(particle*, std::vector<double>, std::vector<double>);
	void set_force(particle*, std::vector<double>, std::vector<double>, std::vector<double>);
	
private:	

	input *_inp;
	field *_ff;
	
};

#endif