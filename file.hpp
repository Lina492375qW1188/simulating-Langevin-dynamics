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
	std::ifstream inFile;
	std::ifstream inFile2;

};

#endif