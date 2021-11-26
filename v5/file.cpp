#include <iostream>

#include "file.hpp"

using std::string;
using std::cerr;

file::file(string file_dir)
{
    inFile_inscpt.open(file_dir);
	inFile_config.open(file_dir);
	
	if(!inFile_inscpt){
		cerr << "Unable to open file\n";
		exit(1); // call system to stop.
	}
	while(getline(inFile_inscpt, line)){
		
	    inscript.push_back(line);

	}	
}

file::~file()
{
	inFile_inscpt.close();
	inFile_config.close();
}
