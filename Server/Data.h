#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <direct.h>
#include <fstream>
#include "shellapi.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>


class Data
{
public:

	// ----------[ Others ]----------
	std::vector<std::string> split(const std::string& str, char delimiter) {
		std::vector<std::string> tokens;
		std::string token;
		std::istringstream tokenStream(str);
		while (std::getline(tokenStream, token, delimiter)) {
			tokens.push_back(token);
		}
		return tokens;
	}

	void SendInformationNotification(const char* title, const char* message) {
		NOTIFYICONDATA nid = { sizeof(NOTIFYICONDATA) };    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
		nid.hIcon = LoadIcon(NULL, IDI_INFORMATION);    nid.uCallbackMessage = WM_USER;
		lstrcpy(nid.szTip, "Информация");
		Shell_NotifyIcon(NIM_ADD, &nid);
		nid.uFlags = NIF_INFO;    lstrcpyn(nid.szInfo, message, sizeof(nid.szInfo));
		lstrcpyn(nid.szInfoTitle, title, sizeof(nid.szInfoTitle));    nid.dwInfoFlags = NIIF_INFO;
		Shell_NotifyIcon(NIM_MODIFY, &nid);
		Sleep(5000); // Ожидание 5 секунд
		Shell_NotifyIcon(NIM_DELETE, &nid);
	}

	void COUT_CurrTime()
	{
		time_t currentTime = time(0);
		struct tm* localTime = localtime(&currentTime);
		std::cout << ", date -> " << localTime->tm_year + 1900 << "-" << localTime->tm_mon + 1 << "-" << localTime->tm_mday << " | " << localTime->tm_hour << ":" << localTime->tm_min << ":" << localTime->tm_sec << std::endl;

	}

};

inline Data g_data;




