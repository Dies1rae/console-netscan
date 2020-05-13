#include <iostream>
#include <string>
#include "scan.h"
#include "log.h"
#include <winsock2.h>
#include <stdio.h>
#include <WS2tcpip.h>
#include "menu.h"
#pragma once
using namespace std;
#define _CRT_SECURE_NO_WARNINGS

int main(int argc, char* argv[]) {
	//init log
	logg* dumplog = new logg("Starting");
	//init scan
	//timestamp
	dumplog->add_log_string("Timestamp");
	scan* test = new scan();
	//set log in scan
	test->set_init_log(dumplog);
	//set option
	if (argc > 2 && argc < 4) {
		cerr << "Check connetscan.exe//? to propertly use program.";
	}
	if (argc == 2 && argv[1][0] == 'm') {
		man_menu_view();
	}
	if (argc == 2 && argv[1][0] == '?') {
		help_menu_view();
	}
	if (argc >= 4) {
		if (argc == 4 && argv[1][0] == 's') {
			string tempIP = argv[2];
			string tempP = argv[3];
			int Port = stoi(tempP);
			char T = argv[1][0];
			cout << "Program get: " <<T << "-" << tempIP << ":" << Port;
			test->set_scan_option(tempIP, Port , T);
			test->start_scan();
			dumplog->write_logdump_to_file(test->get_scan_option());
			cout << endl << endl << "TOTAL RESULT: ";
			cout << test->get_scan_result() << endl;
			system("PAUSE");
		}
		if (argc == 5 && argv[1][0] == 'r') {
			string tempIP = argv[2];
			string tmpPF = argv[3];
			string tmpPT = argv[4];
			int PortFrom = stoi(tmpPF);
			int PortTo = stoi(tmpPT);
			char T = argv[1][0];
			cout << "Program get: " << T << "-" << tempIP << ":" << PortFrom << "-" << PortTo << endl;;
			test->set_scan_option(tempIP, PortFrom, PortTo, T);
			test->start_scan();
			dumplog->write_logdump_to_file(test->get_scan_option());
			cout << endl << endl << "TOTAL RESULT: ";
			cout << test->get_scan_result() << endl;
			system("PAUSE");
		}
	}
	if (argc == 1) {
		test->set_scan_option();
		//start
		test->start_scan();
		//get res from log
		//dumplog->cout_log_string();
		dumplog->write_logdump_to_file(test->get_scan_option());
		//get res last from scan
		cout << endl << endl << "TOTAL RESULT: ";
		cout << test->get_scan_result() << endl;
		system("PAUSE");
	}
	return 0;
}