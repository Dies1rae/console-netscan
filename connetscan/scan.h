#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;


class scan {
private:
	//string to store data scan
	string Result;
	//ip addr to socket
	string IpAddr;
	//port, or several ports in vector elem 1 & 2
	vector <int> port;
	//futer options stealth scan
	int timeout;
	//type of scan - 1 port, several, quick, slow, standart
	char type;
public:
	scan() {
		this->Result = "";
		this->IpAddr = "";
		this->port;
		this->timeout = 0;
		this->type = 's';
	}
	scan(string I, int P, int T, char TY) :IpAddr(I), port(P), timeout(T), type(TY) {}
	~scan() { }

	void set_scan_option(string I, int P, int T, char TY);
	void set_scan_option();
	void cout_scan_option();
	string get_scan_option();
	void cout_scan_result();
	string get_scan_result();
	void start_scan();
	void result_to_file();
};

