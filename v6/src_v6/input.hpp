#ifndef input_hpp
#define input_hpp

#include <string>
#include "file.hpp"

class input{
public:
	
	input();
	~input();
	
	// Environment:
	int num_particle;
    int num_dim;
	int n;
	double h;
	double jwrite;
	
	// Coordinates:
	double *x;
	double *v;
	
	// Verlet:
	std::string method;
	double *alpha;
	double beta;
	double *gamma_x;

    // Force:
	std::string force;
	double A1;
    double A2;
    
    double B1;
	double B2;
	double B3;
    double C1;
    double C2;
	
	// Metadynamics:
    std::string metadynamics;
	double h_bias;
	double w_bias;
	int j_bias;
    double delta_beta; // delta_beta = 1/(k\Delta T)

	double coeff_x; // proportional to cosine of angle between new RC and x coordinate.
	double coeff_y; // proportional to sine.

protected:
	
    file *f;
	file *g;
	
	int *para_i;
	double *para_d;
    
	template <typename T>
    T* read_para(std::string, std::string, int);
	
	std::string read_string(std::string, std::string);
	void read_config();
	
};

#endif