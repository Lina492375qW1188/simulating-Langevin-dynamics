#ifndef output_hpp
#define output_hpp

#include <string>
#include <vector>
#include <fstream>

#include "particle.hpp"
#include "verlet.hpp"
#include "input.hpp"

class output
{
	
public:
	
	output();
	~output();
	
	std::ofstream *myfile;
	
	void header(std::vector<particle*>, verlet*);
	void update(std::vector<particle*>, verlet*);
	
protected:
	
	// Environment:
	int n;
	int num_particle;
	std::string h;
	
	// Verlet:
	std::string alpha;
	std::string beta;
	std::string gamma_x; 
	std::string gamma_y;

    // Force:
	std::string epsilon;
    std::string sigma;
    
    std::string A;
	std::string B;
	std::string a;
    std::string x0;
    std::string width;
	
private:
	
	input *_inp;
	
	std::string roundstr(double, int); // round double and output string of the rounded double.
	std::string roundstr(double); // overloaded method.

};

#endif