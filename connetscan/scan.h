#pragma once
#include "log.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <thread>
#include <sstream>
using namespace std;
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS


class scan {
private:
	//string to store data scan
	string Result;
	//ip addr to socket
	vector <string> IpAddr;
	//hostname
	string hstnm;
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
		this->IpAddr;
		this->hstnm = "";
		this->port;
		this->timeout = 0;
		this->type = 's';
		this->log = NULL;
	}
	scan(string I, int P, int T, char TY, logg * L):port(P), timeout(T), type(TY), log(L){}
	~scan() { }

	//set scan option from already get variable
	void set_scan_option(string I, int P, int T, char TY, logg* L);

	//reload set scan without var. cin it
	void set_scan_option();

	//set scan option from already get variable
	void set_scan_option(string I, int P, char T);
	void set_scan_option(string I, int PF, int PT, char T);
	//cout options
	void cout_scan_option();

	//scan options to string var
	string get_scan_option();

	//cout result of scan
	void cout_scan_result();

	//result of scan to string var
	string get_scan_result();

	//start socket and try to connect by options for thread(if need to scan more than 9 ports)
	void thread_start_scan_second();
	void thread_start_scan_first();
	//start socket and try to connect by options
	void start_scan();

	//check ip or hostname give to us (true if hostname)
	bool ip_or_hostname_check(string IpAd);

	//log init(its a link to work with logg class)
	void set_init_log(logg* L);
	//get ipaddr of resource by hostname. and if its hostname it change it in IP in this->IpAddr
	void get_IP_by_hostname(string H);
	//fnc to copy hostname from this->IPaddr to this->hstnm if it is!
	void set_copy_hstnm(string H);
};

