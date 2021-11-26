#include <iostream>
#include <fstream>

#include "integrate.hpp"

using std::vector;
using std::string;
using std::cerr;

integrate::integrate()
{
	
	_ver = new verlet;
	_inp = new input;
	_out = new output;
	
	// Environment:
	n = _inp->n;
	num_particle = _inp->num_particle;
	jwrite = _inp->jwrite;
	h_bias = _inp->h_bias;
	j_bias = _inp->j_bias;
	
	_metadynamics = _inp->metadynamics;
	
}

integrate::~integrate()
{
	
	delete _out;
	delete _inp;	
	delete _ver;
	
}

void integrate::run(vector<particle*> qq){
	
	string metadynamics = _metadynamics;
	
	if(metadynamics.compare("none") == 0) { }
	else if(metadynamics.compare("normal") == 0) _ver->update_bias(qq); // update bias_vec.
	else if(metadynamics.compare("well-tempered") == 0) _ver->update_bias_wt(qq);
	else if(metadynamics.compare("well-tempered oriented rc") == 0) _ver->update_bias_wt(qq);
	else{
		cerr << "Keyword missing.\n";
		exit(1);
	}
	
	_out->header(qq, _ver); // write header to the file.
	
	for(int j=0; j<n; j++){

		_ver->integrator(qq);

		if(metadynamics.compare("none") == 0) { }
		else if(metadynamics.compare("normal") == 0 && j%j_bias == 0 && j != 0) _ver->update_bias(qq); // update bias_vec.
		else if(metadynamics.compare("well-tempered") == 0 && j%j_bias == 0 && j != 0) _ver->update_bias_wt(qq);
		else if(metadynamics.compare("well-tempered oriented rc") == 0 && j%j_bias == 0 && j != 0) _ver->update_bias_wt(qq);
		
		if(j%jwrite == 0 && j != 0){
			_out->update(qq, _ver); // write x v y w trajectory to the file.
	    }
	}

}

// if separate particle and dimension here, the value would not change.

