#include <iostream>
#include <string>
#include "scan.h"
#include "log.h"
#include <winsock2.h>
#include <stdio.h>
#include <WS2tcpip.h>
#pragma once
using namespace std;


int main() {
	//init log
	logg* dumplog = new logg("Starting");
	//init scan
	scan* test = new scan();
	//set log in scan
	test->set_init_log(dumplog);
	//set option
	test->set_scan_option();
	//start
	test->start_scan();
	//get res from log
	dumplog->cout_log_string();
	dumplog->write_logdump_to_file("C:\\Users\\Vergilius\\source\\repos\\console - netscan\\x64\\Debug\\log_file.txt");
	//get res last from scan
	cout << endl << endl << "TOTAL RESULT: ";
	cout << test->get_scan_result() << endl;

	return 0;
}