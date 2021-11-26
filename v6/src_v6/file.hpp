#ifndef file_hpp
#define file_hpp

#include <vector>
#include <string>
#include <fstream>

class file{

public:
	file(std::string);
	~file();
	std::vector<std::string> inscript;
	std::string line;
	std::ifstream inFile_inscpt; // fstream object for input script.
	std::ifstream inFile_config;   // fstream object for configuration file.

};

#endif