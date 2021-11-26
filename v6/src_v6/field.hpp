#ifndef field_hpp
#define field_hpp

#include <vector>

#include "input.hpp"

class field
{

public:

    field();
	~field();

	double f_x(double, double);
	double f_x(double, double, std::vector<double>);
	double f_x(double, double, std::vector<double>, std::vector<double>);
	double f_x(double, double, std::vector<double>, std::vector<double>, std::vector<double>);
	
	double f_y(double, double);
	double f_y(double, double, std::vector<double>);
	double f_y(double, double, std::vector<double>, std::vector<double>);
	double f_y(double, double, std::vector<double>, std::vector<double>, std::vector<double>);

	double h_bias_wt(double, std::vector<double>, std::vector<double>);
	
	double f_bias(double, double, std::vector<double>, double);
	double f_bias(double, double, std::vector<double>, double, double, std::vector<double>);
	double f_bias(double, double, double, std::vector<double>, std::vector<double>, double, double, std::vector<double>, double, double);
	
	double pe_bias(double, double, std::vector<double>, double);
	double pe_bias(double, double, std::vector<double>, double, double, std::vector<double>);
	double pe_bias(double, double, double, std::vector<double>, std::vector<double>, double, double, std::vector<double>, double, double);
	
	double pe_LJ(double, double, double);
	double pe_DW(double, double, double);
	double pe_Gaussian(double, double, double, double);
	double pe_r4(double, double);
	
private:
	
    // Lenard Jones potential:    
	double _A1;
    double _A2;
	
    // Shifted Gaussian potential:
    double _B1;
	double _B2;
	double _B3;
    double _C1;
    double _C2;
	
	double _h_bias;
	double _w_bias;
	double _delta_beta;

	double _coeff_x;
	double _coeff_y;
	
	double f_LJ(double, double, double);
	double f_DW(double, double, double);
	double f_Gaussian(double, double, double, double);
	double f_r4_x(double, double);
	double f_r4_y(double, double);
	
    input *_inp;

};

#endif