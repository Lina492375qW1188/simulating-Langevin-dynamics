#ifndef particle_hpp
#define particle_hpp

class particle
{
public:
    
    particle(); // constructor
	particle(int);
	~particle();
	
	int flag;
	int num_dim;
    double *x;
    double *v;
	double *d; // used to store previous step.
	
	double *ke_each;
	double *pe_each;
	
	double *ke_tot;
	double *pe_tot;

};

#endif
