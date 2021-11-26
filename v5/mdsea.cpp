#include <iostream>

#include "mdsea.hpp"

using std::cout;
using std::endl;

mdsea::mdsea()
{
	_inp = new input;
	num_particle = _inp->num_particle;
	num_dim = _inp->num_dim;
	for(int i=0; i<num_particle; i++) q.push_back(new particle(num_dim));
	_intgrt = new integrate;
	
}

mdsea::~mdsea()
{
	delete _intgrt;
	delete _inp;
}

void mdsea::update()
{
	
	int id = 0; // record of particle id.
	for(int i=0; i<num_particle; i++){
		for(int j=0; j<num_dim; j++){
			q[i]->x[j] = _inp->x[i+j+id];
			q[i]->v[j] = _inp->v[i+j+id];
		    }
		id += 1; // Jump to next line of configuration file. 
		         // Each line corresponds to one id(particle).
	    }

	cout << "\nSimulation Start: " << endl;	
	for(int i=0; i<num_particle; i++){
		for(int j=0; j<num_dim; j++){
			cout << "initial x" << j+1 << " of particle " << i+1 << ": " << q[i]->x[j] << endl;
			cout << "initial v" << j+1 << " of particle " << i+1 << ": " << q[i]->v[j] << endl;
			}
		}
		
	cout << "---------------------- " << endl;
	
	_intgrt->run(q); // run integration.
	
	cout << "Simulation End: " << endl;
    for(int i=0; i<num_particle; i++){
		for(int j=0; j<num_dim; j++){
			cout << "x" << j+1 << " of particle " << i+1 << ": " << q[i]->x[j] << endl;
			cout << "v" << j+1 << " of particle " << i+1 << ": " << q[i]->v[j] << endl;
		}
	}
	cout << "----------------------" << endl;
	
}
