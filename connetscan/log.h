#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class logg{
private:
	vector <string> logdump;
public:
	logg() {
		this->logdump = {""};
	}
	logg(string L){
		this->logdump.push_back(L);
	}
	~logg() {}

	//add string into log class
	void add_log_string(string L);
	//simple cout all from class
	void cout_log_string();
	//get all log(strings) in vector to somewhere 
	vector <string> get_all_log_string();

	//to file
	void write_logdump_to_file(string filepath);
};

