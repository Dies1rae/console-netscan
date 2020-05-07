#include <iostream>
#include <string>
#include "scan.h"
#include <winsock2.h>
#include <stdio.h>
#include <WS2tcpip.h>
#pragma once
using namespace std;


int main() {
	scan* test = new scan();
	test->set_scan_option();
	test->start_scan();
	test->cout_scan_result();

	return 0;
}