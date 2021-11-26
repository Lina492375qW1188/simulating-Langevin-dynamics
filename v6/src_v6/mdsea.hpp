#ifndef mdsea_hpp
#define mdsea_hpp

#include <vector>

#include "input.hpp"
#include "particle.hpp"
#include "integrate.hpp"

class mdsea
{
public:
	
	mdsea();
	~mdsea();
	void update();
	
protected:
	
	int num_particle;
	int num_dim;
	std::vector<particle*> q;

private:

	input *_inp;
	integrate *_intgrt;
	
};

#endif