#include "log.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

void logg::add_log_string(string L) {
	this->logdump.push_back(L);
}
void logg::cout_log_string() {
	for (auto ptr : this->logdump) {
		cout << ptr << endl;
	}
}
vector <string> logg::get_all_log_string() {
	return this->logdump;
}