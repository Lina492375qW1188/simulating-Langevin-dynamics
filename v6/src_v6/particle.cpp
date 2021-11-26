#include "particle.hpp"

particle::particle()
{
	x = v = 0; // point to no object.
}

particle::particle(int num_dim_input) // initialization
{
	
	flag = 1;
	num_dim = num_dim_input;
    x = new double[num_dim];
	v = new double[num_dim];
	d = new double[num_dim];
	
	ke_each = new double;
	pe_each = new double;
	
	ke_tot = new double;
	pe_tot = new double;

	
}

particle::~particle()
{
	
	delete [] x;
	delete [] v;
	delete [] d;
	
}
