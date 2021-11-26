#include <iostream>
#include <fstream>

#include <string>
#include <chrono>
#include <vector>

#include "mdsea.hpp"

using std::cout;

int main(){
	
	// Record start time
	auto start = std::chrono::high_resolution_clock::now();
	
	// Run simulation
	mdsea *mds = new mdsea;
	mds->update();
    
	// Record end time
	auto finish = std::chrono::high_resolution_clock::now();
	
	// Create duration
	std::chrono::duration<double> elapsed = finish - start;
	cout << "Elapsed time: " << elapsed.count() << "s\n";
	
    return 0;
	
}

