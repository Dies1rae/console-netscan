#pragma once
#include <string>
#include <iostream>
#include <vector>
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
	void add_log_string(string L);
	void cout_log_string();
	vector <string> get_all_log_string();
};

