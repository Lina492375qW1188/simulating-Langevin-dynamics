#include <math.h>
#include <iostream>

#include "field.hpp"
#include "input.hpp"

using std::vector;

field::field()
{
	
	_inp = new input;
	
    _epsilon = _inp->epsilon;
    _sigma = _inp->sigma;
	
    _A = _inp->A;
	_B = _inp->B;
	_a = _inp->a;
    _x0 = _inp->x0;
    _width = _inp->width;
	
	_h_bias = _inp->h_bias;
	_w_bias = _inp->w_bias;
	_delta_beta = _inp->delta_beta;

	_coeff_x = _inp->coeff_x;
	_coeff_y = _inp->coeff_y;

}

field::~field()
{
	
	delete _inp;

}

/* ---------------------
force in x direction:
--------------------- */

double field::f_x(double xx, double yy)
{
	
	double epsilon = _epsilon;
	double sigma = _sigma;
	
	double A = _A;
	double x0 = _x0;
	double width = _width;
    
	return f_LJ(xx, epsilon, sigma) + f_Gaussian(xx, 0.3, 1.75, 0.2) + (yy+1)*f_Gaussian(xx, A, x0, width);
    
}

double field::f_x(double xx, double yy, vector<double> x0_bias)
{
	
	double epsilon = _epsilon;
	double sigma = _sigma;
	
	double A = _A;
	double x0 = _x0;
	double width = _width;
	
	double B = _B;
	double a = _a;
	
	double h_bias = _h_bias;
	double w_bias = _w_bias;

    return f_LJ(xx, epsilon, sigma) + f_Gaussian(xx, 0.3, 1.75, 0.2) + (yy+1)*f_Gaussian(xx, A, x0, width) + f_bias(xx, h_bias, x0_bias, w_bias);
		
}

double field::f_x(double xx, double yy, vector<double> x0_bias, vector<double> h0_bias)
{
	
	double epsilon = _epsilon;
	double sigma = _sigma;
	
	double A = _A;
	double x0 = _x0;
	double width = _width;
	
	double B = _B;
	double a = _a;
	
	double h_bias = _h_bias;
	double w_bias = _w_bias;
	double delta_beta = _delta_beta;

	return f_LJ(xx, epsilon, sigma) + f_Gaussian(xx, 0.3, 1.75, 0.2) + (yy+1)*f_Gaussian(xx, A, x0, width) + f_bias(xx, h_bias, x0_bias, w_bias, delta_beta, h0_bias);
		
}

double field::f_x(double xx, double yy, vector<double> x0_bias, vector<double> y0_bias, vector<double> h0_bias)
{
	
	double epsilon = _epsilon;
	double sigma = _sigma;
	
	double A = _A;
	double x0 = _x0;
	double width = _width;
	
	double B = _B;
	double a = _a;
	
	double h_bias = _h_bias;
	double w_bias = _w_bias;
	double delta_beta = _delta_beta;

	double coeff_x = _coeff_x;
	double coeff_y = _coeff_y;
    
	return f_LJ(xx, epsilon, sigma) + f_Gaussian(xx, 0.3, 1.75, 0.2) + (yy+1)*f_Gaussian(xx, A, x0, width) + coeff_x*f_bias(xx, yy, h_bias, x0_bias, y0_bias, w_bias, delta_beta, h0_bias, coeff_x, coeff_y);
	
}

/* ---------------------
force in y direction:
--------------------- */

double field::f_y(double xx, double yy)
{
	
	double A = _A;
	double B = _B;
	double a = _a;
	double x0 = _x0;
	double width = _width;
    
    return pe_Gaussian(xx, A, x0, width) + f_DW(yy, B, a);
	
}

double field::f_y(double xx, double yy, vector<double> y0_bias)
{
	
	double A = _A;
	double x0 = _x0;
	double width = _width;
	
	double B = _B;
	double a = _a;
	
	double h_bias = _h_bias;
	double w_bias = _w_bias;
    
    return pe_Gaussian(xx, A, x0, width) + f_DW(yy, B, a) + f_bias(yy, h_bias, y0_bias, w_bias);
	
}

double field::f_y(double xx, double yy, vector<double> y0_bias, vector<double> h0_bias)
{
	
	double A = _A;
	double x0 = _x0;
	double width = _width;
	
	double B = _B;
	double a = _a;
    
	double h_bias = _h_bias;
	double w_bias = _w_bias;
	double delta_beta = _delta_beta;
	
    return pe_Gaussian(xx, A, x0, width) + f_DW(yy, B, a) + f_bias(yy, h_bias, y0_bias, w_bias, delta_beta, h0_bias);
	
}

double field::f_y(double xx, double yy, vector<double> x0_bias, vector<double> y0_bias, vector<double> h0_bias)
{
	
	double A = _A;
	double x0 = _x0;
	double width = _width;
	
	double B = _B;
	double a = _a;
    
	double h_bias = _h_bias;
	double w_bias = _w_bias;
	double delta_beta = _delta_beta;

	double coeff_x = _coeff_x;
	double coeff_y = _coeff_y;
	
    return pe_Gaussian(xx, A, x0, width) + f_DW(yy, B, a) + coeff_y*f_bias(xx, yy, h_bias, x0_bias, y0_bias, w_bias, delta_beta, h0_bias, coeff_x, coeff_y);
	
}

/* ----------------
bias computation
---------------- */

// Well-tempered Bias force with rotated Reaction Coordinates:
double field::f_bias(double xx, double yy, double h_bias, vector<double> x0_bias, vector<double> y0_bias, double w_bias, double delta_beta, vector<double> h0_bias, double coeff_x, double coeff_y)
{
	
	double f_bias_sum = 0;
	for(vector<double>::size_type ix = 0; ix != x0_bias.size(); ++ix){
		f_bias_sum += f_Gaussian(coeff_x*xx+coeff_y*yy, h0_bias[ix], coeff_x*x0_bias[ix]+coeff_y*y0_bias[ix], w_bias);
	}
	return f_bias_sum;
	
}

// Well-tempered Bias potential with rotated Reaction Coordinates:
double field::pe_bias(double xx, double yy, double h_bias, vector<double> x0_bias, vector<double> y0_bias, double w_bias, double delta_beta, vector<double> h0_bias, double coeff_x, double coeff_y)
{
	
	double pe_bias_sum = 0;
	for(vector<double>::size_type ix = 0; ix != x0_bias.size(); ++ix){
		pe_bias_sum += pe_Gaussian(coeff_x*xx+coeff_y*yy, h0_bias[ix], coeff_x*x0_bias[ix]+coeff_y*y0_bias[ix], w_bias);
	}
	return pe_bias_sum;
	
}

// Well-tempered Bias force:
double field::f_bias(double xx, double h_bias, vector<double> x0_bias, double w_bias, double delta_beta, vector<double> h0_bias)
{
	
	double f_bias_sum = 0;
	for(vector<double>::size_type ix = 0; ix != x0_bias.size(); ++ix){
		f_bias_sum += f_Gaussian(xx, h0_bias[ix], x0_bias[ix], w_bias);
	}
	return f_bias_sum;
	
}

// Well-tempered Bias potential:
double field::pe_bias(double xx, double h_bias, vector<double> x0_bias, double w_bias, double delta_beta, vector<double> h0_bias)
{
	
	double pe_bias_sum = 0;
	for(vector<double>::size_type ix = 0; ix != x0_bias.size(); ++ix){
		pe_bias_sum += pe_Gaussian(xx, h0_bias[ix], x0_bias[ix], w_bias);
	}
	return pe_bias_sum;
	
}

// Compute height of bias Gaussian of well-tempered metadynamics:
double field::h_bias_wt(double xx, vector<double> x0_bias, vector<double> h0_bias)
{
	
	double h_bias_product = _h_bias;
	double w_bias = _w_bias;
	double delta_beta = _delta_beta;
	
	for(vector<double>::size_type ix = 1; ix != h0_bias.size(); ++ix){
		// ix begins with 1, so it never loops over the initialized element in h0_bias_vec which is 0.0.
		h_bias_product *= exp(-delta_beta*pe_Gaussian(xx, h0_bias[ix], x0_bias[ix], w_bias));
	}
	return h_bias_product;
	
}

// Bias force:
double field::f_bias(double xx, double h_bias, vector<double> x0_bias, double w_bias)
{
	
	double f_bias_sum = 0;
	for(vector<double>::iterator it = x0_bias.begin(); it != x0_bias.end(); ++it){
		f_bias_sum += f_Gaussian(xx, h_bias, *it, w_bias);
	}
	return f_bias_sum;
	
}
// Bias potential energy:
double field::pe_bias(double xx, double h_bias, vector<double> x0_bias, double w_bias)
{
	
	double pe_bias_sum = 0;
	for(vector<double>::iterator it = x0_bias.begin(); it != x0_bias.end(); ++it){
		pe_bias_sum += pe_Gaussian(xx, h_bias, *it, w_bias);
	}
	return pe_bias_sum;
	
}

/* ---------------------
independent potential
--------------------- */

// Lennard-Jones force:
double field::f_LJ(double xx, double epsilon, double sigma)
{
	return 4*epsilon*((12/xx)*pow(sigma/xx, 12) - (6/xx)*pow(sigma/xx, 6));
}
// Lennard-Jones potential energy:
double field::pe_LJ(double xx, double epsilon, double sigma)
{
	return 4*epsilon*(pow((sigma/xx),12)-pow((sigma/xx),6));
}

// Double well force:
double field::f_DW(double yy, double B, double a)
{
	return -4*B*(yy*yy*yy) + 4*B*a*yy;
}
// Double well potential energy:
double field::pe_DW(double yy, double B, double a)
{
	double d_yy = yy*yy-a;
	return B*d_yy*d_yy;
}

// Shifted Gaussian force:
double field::f_Gaussian(double xx, double A, double x0, double w)
{
	double d_xx = xx-x0;
	double sqr_d_xx = d_xx*d_xx;
	double sqr_ww = w*w;
	return (A/sqr_ww)*d_xx*exp(-0.5*sqr_d_xx/sqr_ww);
}
// Shifted Gaussian potential energy:
double field::pe_Gaussian(double xx, double A, double x0, double w)
{
	double d_xx = xx-x0;
	double sqr_d_xx = d_xx*d_xx;
	double sqr_ww = w*w;
	return A*exp(-0.5*sqr_d_xx/sqr_ww);
}