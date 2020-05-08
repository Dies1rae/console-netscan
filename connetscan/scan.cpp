#include "log.h"
#include "scan.h"
#include <iostream>
#include <string>
#include <winsock2.h>
#include <stdio.h>
#include <WS2tcpip.h>
#include <thread>
using namespace std;
#pragma comment(lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS


void scan::set_scan_option(string I, int P, int T, char TY, logg* L) {
	this->IpAddr = I;
	this->port.push_back(P);
	this->timeout = T;
	this->type = TY;
	this->log = L;
}

void scan::set_scan_option() {
	string I;
	int P;
	char TY;
	cout << "Enter type of scan(s-simple(1 ip-hostname, 1 port)/##a-auto(range of ip, 1 port)##/r-ranged(1 ip-hostname, range of port))" << endl;
	cin >> TY;
	this->type = TY;
	cout << "Enter Hostname or IP address" << endl;
	cin >> I;
	this->IpAddr = I;
	if (TY == 's') {
		cout << "Enter port" << endl;
		cin >> P;
		this->port.push_back(P);
	}
	if (TY == 'r') {
		int ptr = 2;
		while (ptr) {
			cout << "Enter port range(80 443|from * to)" << endl;
			cin >> P;
			this->port.push_back(P);
			ptr--;
		}
	}
}

void scan::cout_scan_option() {
	for (auto ptrport : this->port) {
		cout << this->IpAddr << " : " << ptrport << " : " << this->timeout << " : " << this->type << endl;
	}
}

string scan::get_scan_option() {
	string res = this->IpAddr + "_";
	for (auto ptrport : this->port) {
		res += to_string(ptrport) + "-";
	}
	return res;
}

void scan::cout_scan_result() {
	cout << this->Result << endl;
}

string scan::get_scan_result() {
	return this->Result;
}

void scan::set_init_log(logg* L) {
	this->log = L;
}

void scan::thread_start_scan() {
	//init
	WSAData Data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &Data);
	if (wsResult != 0) {
		this->Result = "Can't start Winsock, error! " + to_string(wsResult);
		cerr << "Can't start Winsock, error!" << wsResult << endl;
		WSACleanup();
		return;
	}
	//Create socket
	SOCKET Clsock = socket(AF_INET, SOCK_STREAM, 0);
	if (Clsock == INVALID_SOCKET) {
		cerr << "Can't create Client socket, error! " << WSAGetLastError() << endl;
		this->Result = "Can't create Client socket, error! " + WSAGetLastError();
		WSACleanup();
		return;
	}
	//hint
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	//chek hostname or IP in this->IpAddr string
	//-------------------
	if (!ip_or_hostname_check(this->IpAddr)) {
		inet_pton(AF_INET, this->IpAddr.c_str(), &hint.sin_addr);
	}
	else {
		int ptr0 = 0;
		char* hostname;
		hostname = (char*)this->IpAddr.c_str();
		struct hostent* host_info;
		struct in_addr addr;
		host_info = gethostbyname(hostname);
		DWORD dw;
		if (host_info == NULL) {
			dw = WSAGetLastError();
			if (dw != 0) {
				if (dw == WSAHOST_NOT_FOUND) {
					//cout << "Host is not found" << endl;
					this->Result += "Host is not found";
					this->log->add_log_string(this->Result);
					closesocket(Clsock);
					WSACleanup();
					return;
				}
				else if (dw == WSANO_DATA) {
					//cout << "No data record is found" << endl;
					this->Result += "No data record is found";
					this->log->add_log_string(this->Result);
					closesocket(Clsock);
					WSACleanup();
					return;
				}
				else {
					//cout << "Function failed with an error : " << dw << endl;
					this->Result += "Function failed with an error : " + to_string(dw);
					this->log->add_log_string(this->Result);
					closesocket(Clsock);
					WSACleanup();
					return;
				}
			}
		}
		else {
			while (host_info->h_addr_list[ptr0] != 0) {
				addr.s_addr = *(u_long*)host_info->h_addr_list[ptr0++];
				cout << "IP Address: " << inet_ntoa(addr) << endl;
				string IpAdd = inet_ntoa(addr);
				inet_pton(AF_INET, IpAdd.c_str(), &hint.sin_addr);
			}
		}
	}
	//--------------
	//ports
	for (int ptrPort = this->port[1] / 2; ptrPort <= this->port[1]; ptrPort++) {
		hint.sin_port = htons(ptrPort);
		//connect serv
		//-------------
		int connResult = connect(Clsock, (sockaddr*)&hint, sizeof(hint));
		if (connResult == SOCKET_ERROR) {
			if (WSAGetLastError() == 10061) {
				this->Result = "Cant connect to " + this->IpAddr + ":" + to_string(ptrPort) + " " + to_string(WSAGetLastError()) + "|" + "You could not make a connection because the target machine actively refused it";
				//cout << "Cant connect to " << this->IpAddr << ":" << to_string(ptrPort) << " " << to_string(WSAGetLastError()) << "|" << "You could not make a connection because the target machine actively refused it" << endl;
				this->log->add_log_string(this->Result);
			}
			else {
				this->Result = "Cant connect to " + this->IpAddr + ":" + to_string(ptrPort) + " " + to_string(WSAGetLastError());
				//cout << "Cant connect to " << this->IpAddr << ":" << to_string(ptrPort) << " " << to_string(WSAGetLastError()) << endl;
				this->log->add_log_string(this->Result);
			}
		}
		else {
			this->Result = "Client connected to " + this->IpAddr + ":" + to_string(ptrPort) + " - Port is open.";
			//cout <<  "Client connected to " << this->IpAddr + ":" + to_string(ptrPort) << " - Port is open." << endl;
			this->log->add_log_string(this->Result);
		}
		//-------------
	}
	//close sock
	closesocket(Clsock);
	WSACleanup();
	return;
}

void scan::start_scan() {
	//init
	WSAData Data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &Data);
	if (wsResult != 0) {
		this->Result = "Can't start Winsock, error! " + to_string(wsResult);
		cerr << "Can't start Winsock, error!" << wsResult << endl;
		WSACleanup();
		return;
	}
	//Create socket
	SOCKET Clsock = socket(AF_INET, SOCK_STREAM, 0);
	if (Clsock == INVALID_SOCKET) {
		cerr << "Can't create Client socket, error! " << WSAGetLastError() << endl;
		this->Result = "Can't create Client socket, error! " + WSAGetLastError();
		WSACleanup();
		return;
	}
	//hint
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	//chek hostname or IP in this->IpAddr string
	//-------------------
	if (!ip_or_hostname_check(this->IpAddr)) {
			inet_pton(AF_INET, this->IpAddr.c_str(), &hint.sin_addr);
		}
	else {
			int ptr0 = 0;
			char* hostname;
			hostname = (char*)this->IpAddr.c_str();
			struct hostent* host_info;
			struct in_addr addr;
			host_info = gethostbyname(hostname);
			DWORD dw;
			if (host_info == NULL){
				dw = WSAGetLastError();
				if (dw != 0){
					if (dw == WSAHOST_NOT_FOUND){
						//cout << "Host is not found" << endl;
						this->Result += "Host is not found";
						this->log->add_log_string(this->Result);
						closesocket(Clsock);
						WSACleanup();
						return;
					}
					else if (dw == WSANO_DATA){
						//cout << "No data record is found" << endl;
						this->Result += "No data record is found";
						this->log->add_log_string(this->Result);
						closesocket(Clsock);
						WSACleanup();
						return;
					}
					else{
						//cout << "Function failed with an error : " << dw << endl;
						this->Result += "Function failed with an error : " + to_string(dw);
						this->log->add_log_string(this->Result);
						closesocket(Clsock);
						WSACleanup();
						return;
					}
				}
			}
			else {
				while (host_info->h_addr_list[ptr0] != 0) {
					addr.s_addr = *(u_long*)host_info->h_addr_list[ptr0++];
					cout << "IP Address: " << inet_ntoa(addr) << endl;
					string IpAdd = inet_ntoa(addr);
					inet_pton(AF_INET, IpAdd.c_str(), &hint.sin_addr);
				}
			}
		}
	//--------------
	//ports
	if (this->type == 's') {
		hint.sin_port = htons(this->port[0]);
		//connect serv
		//-------------
		int connResult = connect(Clsock, (sockaddr*)&hint, sizeof(hint));
		if (connResult == SOCKET_ERROR) {
			if (WSAGetLastError() == 10061) {
				this->Result = "Cant connect to " + this->IpAddr + ":" + to_string(this->port[0]) + " " + to_string(WSAGetLastError()) + "|" + "You could not make a connection because the target machine actively refused it";
				//cout << "Cant connect to " << this->IpAddr << ":" << to_string(this->port[0]) << " " << to_string(WSAGetLastError()) << "|" << "You could not make a connection because the target machine actively refused it" << endl;
				this->log->add_log_string(this->Result);
				closesocket(Clsock);
				WSACleanup();
				return;
			}
			else {
				this->Result = "Cant connect to " + this->IpAddr + ":" + to_string(this->port[0]) + " " + to_string(WSAGetLastError());
				//cout << "Cant connect to " << this->IpAddr << ":" << to_string(this->port[0]) << " " << to_string(WSAGetLastError()) << endl;
				this->log->add_log_string(this->Result);
				closesocket(Clsock);
				WSACleanup();
				return;
			}
		}
		else {
			this->Result = "Client connected to " + this->IpAddr + ":" + to_string(this->port[0]) + " - Port is open.";
			this->log->add_log_string(this->Result);
		}
		//-------------
	}
	else if (this->type == 'r' && this->port.size() == 2) {
		if (this->port.size() >= 10) {
			std::thread secondScan(&scan::thread_start_scan, this);
			for (int ptrPort = this->port[0]; ptrPort <= this->port[1]/2-1; ptrPort++) {
				hint.sin_port = htons(ptrPort);
				//connect serv
				//-------------
				int connResult = connect(Clsock, (sockaddr*)&hint, sizeof(hint));
				if (connResult == SOCKET_ERROR) {
					if (WSAGetLastError() == 10061) {
						this->Result = "Cant connect to " + this->IpAddr + ":" + to_string(ptrPort) + " " + to_string(WSAGetLastError()) + "|" + "You could not make a connection because the target machine actively refused it";
						//cout << "Cant connect to " << this->IpAddr << ":" << to_string(ptrPort) << " " << to_string(WSAGetLastError()) << "|" << "You could not make a connection because the target machine actively refused it" << endl;
						this->log->add_log_string(this->Result);
					}
					else {
						this->Result = "Cant connect to " + this->IpAddr + ":" + to_string(ptrPort) + " " + to_string(WSAGetLastError());
						//cout << "Cant connect to " << this->IpAddr << ":" << to_string(ptrPort) << " " << to_string(WSAGetLastError()) << endl;
						this->log->add_log_string(this->Result);
					}
				}
				else {
					this->Result = "Client connected to " + this->IpAddr + ":" + to_string(ptrPort) + " - Port is open.";
					//cout <<  "Client connected to " << this->IpAddr + ":" + to_string(ptrPort) << " - Port is open." << endl;
					this->log->add_log_string(this->Result);
				}
				//-------------
			}
			secondScan.join();
		}else{
			for (int ptrPort = this->port[0]; ptrPort <= this->port[1]; ptrPort++) {
				hint.sin_port = htons(ptrPort);
				//connect serv
				//-------------
				int connResult = connect(Clsock, (sockaddr*)&hint, sizeof(hint));
				if (connResult == SOCKET_ERROR) {
					if (WSAGetLastError() == 10061) {
						this->Result = "Cant connect to " + this->IpAddr + ":" + to_string(ptrPort) + " " + to_string(WSAGetLastError()) + "|" + "You could not make a connection because the target machine actively refused it";
						//cout << "Cant connect to " << this->IpAddr << ":" << to_string(ptrPort) << " " << to_string(WSAGetLastError()) << "|" << "You could not make a connection because the target machine actively refused it" << endl;
						this->log->add_log_string(this->Result);
					}
					else {
						this->Result = "Cant connect to " + this->IpAddr + ":" + to_string(ptrPort) + " " + to_string(WSAGetLastError());
						//cout << "Cant connect to " << this->IpAddr << ":" << to_string(ptrPort) << " " << to_string(WSAGetLastError()) << endl;
						this->log->add_log_string(this->Result);
					}
				}
				else {
					this->Result = "Client connected to " + this->IpAddr + ":" + to_string(ptrPort) + " - Port is open.";
					//cout <<  "Client connected to " << this->IpAddr + ":" + to_string(ptrPort) << " - Port is open." << endl;
					this->log->add_log_string(this->Result);
				}
				//-------------
			}
		}
	}
	//close sock
	closesocket(Clsock);
	WSACleanup();
	return;
}



//check ip or hostname give to us (true if hostname)
bool scan::ip_or_hostname_check(string IpAd) {
	for (char ptr0 : IpAd) {
		if ((ptr0 > 64 && ptr0 < 91) || (ptr0 > 96 && ptr0 < 123)) {
			return 1;
		}
	}
	return 0;
}

