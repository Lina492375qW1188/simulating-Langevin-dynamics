#include <iostream>

#include "file.hpp"

using std::string;
using std::cerr;

file::file(string file_pos)
{
    inFile.open(file_pos);
	inFile2.open(file_pos);
	
	if(!inFile){
		cerr << "Unable to open file\n";
		exit(1); // call system to stop.
	}
	while(getline(inFile, line)){
		
	    inscript.push_back(line);
	}	
}

file::~file()
{
	inFile.close();
	inFile2.close();
}
