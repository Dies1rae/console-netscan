#pragma once
#include "log.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <thread>
using namespace std;
#define _WINSOCK_DEPRECATED_NO_WARNINGS


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
	//pointer to log class
	logg* log;
public:
	scan() {
		this->Result = "";
		this->IpAddr = "";
		this->port;
		this->timeout = 0;
		this->type = 's';
		this->log = NULL;
	}
	scan(string I, int P, int T, char TY, logg * L):IpAddr(I), port(P), timeout(T), type(TY), log(L){}
	~scan() { }

	//set scan option from already get variable
	void set_scan_option(string I, int P, int T, char TY, logg* L);

	//reload set scan without var. cin it
	void set_scan_option();

	//cout options
	void cout_scan_option();

	//scan options to string var
	string get_scan_option();

	//cout result of scan
	void cout_scan_result();

	//result of scan to string var
	string get_scan_result();

	//start socket and try to connect by options for thread(if need to scan more than 9 ports)
	void thread_start_scan();
	//start socket and try to connect by options
	void start_scan();

	//check ip or hostname give to us (true if hostname)
	bool ip_or_hostname_check(string IpAd);

	//log init(its a link to work with logg class)
	void set_init_log(logg* L);
};

