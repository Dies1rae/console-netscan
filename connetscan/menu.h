#pragma once
#include <iostream>
#include <windows.h>
#include <iomanip>
using namespace std;

//func declar
void help_menu_view();
void hidecursor();
void UNhidecursor();
void man_menu_view();
//display main menu
void man_menu_view() {
	hidecursor();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << endl << "***|";
	SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | 5);
	cout << "DIPscan";
	SetConsoleTextAttribute(hConsole, 7);
	cout << endl << "***|";
	SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | 5);
	cout << "Help menu";
	SetConsoleTextAttribute(hConsole, 7);
	SetConsoleTextAttribute(hConsole, 8);
	cout << endl << "***|" << "DIPscan(1)";
	SetConsoleTextAttribute(hConsole, 7);
	SetConsoleTextAttribute(hConsole, 8);
	cout << endl << "***|" << "SYNOPSIS:";
	SetConsoleTextAttribute(hConsole, 7);
	cout << endl << "***|" << "		dipscan [OPTION] ... [DATA] ... [DATA]";
	SetConsoleTextAttribute(hConsole, 8);
	cout << endl << "***|" << "DESCRIPTION:";
	SetConsoleTextAttribute(hConsole, 7);
	cout << endl << "***|" << "		./dipscan /s(simple portscan) ... IPADDRESS(1) or HOSTNAME(several IP's) ... PORT";
	cout << endl << "***|" << "		./dipscan /r(ranged portscan) ... IPADDRESS(1) or HOSTNAME(several IP's) ... PORT from scan ... PORT to scan";
	cout << endl << "***|" << "		./dipscan /a(ranged IP scan) ... FROM IPADDRESS(1) TO IPADDRESS(2) ... PORT";
	cout << endl << "***|" << "		./dipscan /u(ranged IP scan + ranged portscan) ... FROM IPADDRESS(1) TO IPADDRESS(2) ... PORT from scan ... PORT to scan";
	cout << endl << "***|" << "		./dipscan /?(help menu)";
	cout << endl << "***|" << "		./dipscan /man(man menu)";
	SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | 9);
	cout << endl << "...by Dies_Irae" << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	SetConsoleTextAttribute(hConsole, 7);
	UNhidecursor();
}

void help_menu_view() {
	cout << "Usage: dipsccan [OPTION] ... [HOSTNAME/IP] ... [PORT]" << endl << endl;
	cout << "OPTIONS: " << endl;
	cout << "s - Simple scan. One target IP or HOSTNAME(one or more ip) and ONE target PORT" << endl;
	cout << "r - Ranged port scan. One target IP or HOSTNAME(one or more ip), target port FROM and target port TO(range of ports from--->to)" << endl;
	cout << "a - Ranged IP scan. IP address from and IP address to, target port for all these IP" << endl;
	cout << "u - Ranged IP scan and ranged port scan. Target IP address from and target IP address to, target port FROM and target port TO(range of ports from--->to)" << endl;
	cout << "m - man menu" << endl;
	cout << "m - help menu" << endl << endl;
	cout << "OPTIONS: " << endl;
	cout << "dipscan.exe /s www.google.com 443" << endl;
	cout << "dipscan.exe /s 192.168.1.1 80" << endl << endl;
	cout << "dipscan.exe /r 192.168.1.1 80 160" << endl;
	cout << "dipscan.exe /r www.ya.ru 440 500" << endl << endl;
	cout << "dipscan.exe /a 192.168.1.1 192.168.1.10 500" << endl << endl;
	cout << "dipscan.exe /u 192.168.1.1 192.168.1.10 400 500" << endl << endl;
	cout << "dipscan.exe /h" << endl;
	cout << "dipscan.exe /?" << endl;
}

void hidecursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}
void UNhidecursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.bVisible = TRUE;
	SetConsoleCursorInfo(consoleHandle, &info);
}