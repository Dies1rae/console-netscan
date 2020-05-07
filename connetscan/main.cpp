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
	logg* dumplog = new logg("Starting");
	scan* test = new scan();
	test->set_init_log(dumplog);
	test->set_scan_option();
	test->start_scan();
	dumplog->cout_log_string();
	cout << endl << endl << "TOTAL RESULT: ";
	cout << test->get_scan_result() << endl;

	return 0;
}