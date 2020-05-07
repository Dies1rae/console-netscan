#include "scan.h"
#include <iostream>
#include <string>
#include <winsock2.h>
#include <stdio.h>
#include <WS2tcpip.h>
using namespace std;
#pragma comment(lib, "ws2_32.lib")


void scan::set_scan_option(string I, int P, int T, char TY) {
	this->IpAddr = I;
	this->port.push_back(P);
	this->timeout = T;
	this->type = TY;
}
void scan::set_scan_option() {
	string I;
	int P;
	char TY;
	cout << "Enter IP address" << endl;
	cin >> I;
	cout << "Enter port" << endl;
	cin >> P;
	cout << "Enter type of scan(s/a/)" << endl;
	cin >> TY;
	this->IpAddr = I;
	this->port.push_back(P);
	this->type = TY;
}
void scan::cout_scan_option() {
	for (auto ptrport : this->port) {
		cout << this->IpAddr << " : " << ptrport << " : " << this->timeout << " : " << this->type << endl;
	}
}
string scan::get_scan_option() {
	string res;
	for (auto ptrport : this->port) {
		res += this->IpAddr + " : " + to_string(ptrport) + " : " + to_string(this->timeout) + " : " + to_string(this->type) + '\0';
	}
	return res;
}
void scan::cout_scan_result() {
	cout << this->Result << endl;
}
string scan::get_scan_result() {
	return this->Result;
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
	if (this->type == 's') {
		hint.sin_port = htons(this->port[0]);
		inet_pton(AF_INET, this->IpAddr.c_str(), &hint.sin_addr);
		//connect serv
		int connResult = connect(Clsock, (sockaddr*)&hint, sizeof(hint));
		if (connResult == SOCKET_ERROR) {
			if (WSAGetLastError() == 10061) {
				this->Result = "Cant connect to " + this->IpAddr + ":" + to_string(this->port[0]) + " " + to_string(WSAGetLastError()) + "|" + "You could not make a connection because the target machine actively refused it";
				cerr << "Cant connect to " << this->IpAddr << ":" << to_string(this->port[0]) << " " << to_string(WSAGetLastError()) << "|" << "You could not make a connection because the target machine actively refused it" << endl;
				closesocket(Clsock);
				WSACleanup();
				return;
			}
			else {
				this->Result = "Cant connect to " + this->IpAddr + ":" + to_string(this->port[0]) + " " + to_string(WSAGetLastError());
				cout << "Cant connect to " << this->IpAddr << ":" << to_string(this->port[0]) << " " << to_string(WSAGetLastError()) << endl;
				closesocket(Clsock);
				WSACleanup();
				return;
			}
		}
		else {
			this->Result = "Client connected to " + this->IpAddr + ":" + to_string(this->port[0]) + " - Port is open.";
		}
		closesocket(Clsock);
		WSACleanup();
		return;
	}
}
