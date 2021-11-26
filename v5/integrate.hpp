#ifndef integrate_hpp
#define integrate_hpp

#include <vector>
#include <string>

#include "particle.hpp"
#include "verlet.hpp"
#include "input.hpp"
#include "output.hpp"

class integrate
{
public:
	
	integrate();
	~integrate();
	
    void run(std::vector<particle*>);

protected:
	
	// Environment:
	int n;
	double h;
	int num_particle;
	int jwrite;
	double h_bias;
	int j_bias;
	
private:
	
	std::string _metadynamics;
	
	input *_inp;
	verlet *_ver;
	output *_out;
	
};

#endif