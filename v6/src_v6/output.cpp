#include <iomanip> // setprecision
#include <sstream> // stringstream

#include "output.hpp"

using std::string;
using std::vector;
using std::endl;
using std::stringstream;
using std::setprecision;
using std::to_string;
using std::fixed;
using std::ofstream;

output::output()
{
	
	_inp = new input;

    // Environment:
	n = _inp->n;
	num_particle = _inp->num_particle;
	h = roundstr(_inp->h);
	
	// Verlet:
	alpha = roundstr(_inp->alpha[0], 1);
	beta = roundstr(_inp->beta, 1);
	gamma_x = roundstr(_inp->gamma_x[0], 1);
	gamma_y = roundstr(_inp->gamma_x[1], 1);
	
	string Environment = "_h"+h;
	string Verlet = "beta"+beta+"gammax"+gamma_x+"gammay"+gamma_y;
	
	myfile = new ofstream[num_particle];
	
	for(int i=0; i<num_particle; i++){	
		string file_pos = "xvyw"+to_string(i+1) + Verlet + Environment + ".txt";	
		myfile[i].open(file_pos.c_str());
	}
	
}

output::~output()
{

    delete [] myfile;
	delete _inp;

}

void output::header(vector<particle*> qq, verlet *ver){
	
	for(int i=0; i<num_particle; i++){
		for(int j=0; j<qq[i]->num_dim; j++) myfile[i] << "x_" << j+1 << " ";
		for(int j=0; j<qq[i]->num_dim; j++) myfile[i] << "v_" << j+1 << " ";

	    myfile[i] << "r1 r2 height x0_bias y0_bias" << endl;
		for(int j=0; j<qq[i]->num_dim; j++) myfile[i] << qq[i]->x[j] << " ";
		for(int j=0; j<qq[i]->num_dim; j++) myfile[i] << qq[i]->v[j] << " ";
		myfile[i] << ver->r1 << " " << ver->r2 << " ";
		myfile[i] << ver->h0_bias_vec.at(i).back() << " ";
		myfile[i] << ver->x0_bias_vec.at(i).back() << " " << ver->y0_bias_vec.at(i).back() << endl;
	}
	
}

void output::update(vector<particle*> qq, verlet* ver){
	
	/* Stop writing while particle is across barrier: */
	for(int i=0; i<num_particle; i++){
		if(qq[i]->flag == 1){
			for(int j=0; j<qq[i]->num_dim; j++) myfile[i] << qq[i]->x[j] << " ";
	    	for(int j=0; j<qq[i]->num_dim; j++) myfile[i] << qq[i]->v[j] << " ";
		    myfile[i] << ver->r1 << " " << ver->r2 << " ";
		    myfile[i] << ver->h0_bias_vec.at(i).back() << " ";
		    myfile[i] << ver->x0_bias_vec.at(i).back() << " " << ver->y0_bias_vec.at(i).back() << endl;
		}
	}
	
}

string output::roundstr(double parameter, int precision){
	
	string s;
	stringstream stream;
	
	stream << fixed << setprecision(precision) << parameter;
	stream >> s;
	
	return s;
	
}
// overloaded method:
string output::roundstr(double parameter){
	
	string s;
	stringstream stream;
	// If parameter = 1~10, this will return 1.0~9.0; otherwise the decimals will be truncated.
	if(parameter >= 1 && parameter < 10) stream << fixed << setprecision(1) << parameter;
	else stream << parameter;
	stream >> s;
	
	return s;
	
}
