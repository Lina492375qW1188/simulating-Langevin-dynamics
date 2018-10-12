#include <iostream>
#include <fstream>
#include <typeinfo>

#include "input.hpp"
#include "file.hpp"
#include "verlet.hpp"

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::stod;
using std::stoi;

input::input()
{
	
	f = new file("./inscript.txt");
	g = new file("./config.txt");
	
	// Environment:
	para_i = read_para<int>(f->inscript[0], "num_particle", 1);
	num_particle = para_i[0];
	para_i = read_para<int>(f->inscript[1], "dimension", 1);
	num_dim = para_i[0];
	para_i = read_para<int>(f->inscript[2], "step", 1);
	n = para_i[0];
	para_d = read_para<double>(f->inscript[3], "time step", 1);
	h = para_d[0];
	para_i = read_para<int>(f->inscript[3], "time step", 2);
	jwrite = para_i[1];
	
	// Coordinates:
	x = new double[num_particle*num_dim];
	v = new double[num_particle*num_dim];
	read_config();
	
	// Verlet:
	method = read_string(f->inscript[4], "method");
	para_d = read_para<double>(f->inscript[5], "alpha", 1);
	alpha = para_d;
	para_d = read_para<double>(f->inscript[6], "beta", 1);
	beta = para_d[0];
	para_d = read_para<double>(f->inscript[7], "gamma", 2);
	gamma_x = para_d;
	
	// Force:
	force = read_string(f->inscript[8], "force");

	para_d = read_para<double>(f->inscript[9], "LJ", 2);
	epsilon = para_d[0];
	sigma = para_d[1];

	para_d = read_para<double>(f->inscript[10], "Shifted Gaussian", 3);
	A = para_d[0];
	x0 = para_d[1];
	width = para_d[2];
	
	para_d = read_para<double>(f->inscript[11], "Double Well", 2);
	B = para_d[0];
	a = para_d[1];
	
	// Metadynamics:
	metadynamics = read_string(f->inscript[12], "Metadynamics");
	
	para_d = read_para<double>(f->inscript[13], "Bias", 4);
	h_bias = para_d[0];
	w_bias = para_d[1];
	delta_beta = para_d[3];
	para_i = read_para<int>(f->inscript[13], "Bias", 3);
	j_bias = para_i[2];

	para_d = read_para<double>(f->inscript[14], "oriented_rc", 2);
	coeff_x = para_d[0];
	coeff_y = para_d[1];

}
input::~input()
{
    delete f;
}

template <typename T>
T* input::read_para(string str, string keyword, int num_para)
{
	
	T *arr = new T[num_para]; // record double type parameters.
	string::size_type keyword_pos = str.find(keyword);
	
	if(keyword_pos!=string::npos){
        vector<int> space_arr; // record pos of space characters.
		vector<string> para_arr; // record each parameters.
		para_arr.push_back( str.substr(keyword.size()+1) ); // initialize the vector with only parameters.
		for(int i=0; i<num_para; i++){
			
			string::size_type space = para_arr[i].find(" ");
			space_arr.push_back(space);
			para_arr.push_back(para_arr[i].substr(space+1));
			para_arr[i] = para_arr[i].substr(0, space_arr[i]);
			
			if (typeid(T) == typeid(int))          arr[i] = stoi(para_arr[i]);
			else if (typeid(T) == typeid(double))  arr[i] = stod(para_arr[i]);
			
		}
		return arr;
	}
	else{	
		cout << "keyword \"" << keyword << "\" not found!" << endl;
		return 0;
	}
	
}

string input::read_string(string str, string sub)
{
	
	string::size_type sub_pos = str.find(sub);
	if(sub_pos!=string::npos){
		string::size_type space = str.find(" ")+1;
		return str.substr(space);
	}
	else{
		cout << "keyword \"" << sub << "\" not found!" << endl;
		return 0;
	}
	
}

/* Configuration reading is weak. The configuration file should be exactly fit number of particles and dimensions.*/
void input::read_config()
{

	int id = 0; // record of particle id.
	for(int i=0; i<num_particle; i++){
		for(int j=0; j<num_dim; j++){ // read the first {num_dim} values.
	        g->inFile_config >> x[i+j+id];
		}
		for(int j=0; j<num_dim; j++){ // read three values followed by the first {num_dim} values.
			g->inFile_config >> v[i+j+id];
		}
		id += 1; // jump to next line of configuration file. each line corresponds to one id(particle).
	}
	
}
