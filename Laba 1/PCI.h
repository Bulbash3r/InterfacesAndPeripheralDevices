#pragma once

#define BUFFERSIZE 4000
#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <stdio.h>
#include <Windows.h>
#include <setupapi.h>
#include <vector>
#include <devguid.h>
#include <iostream>
#include <cctype>
#include <cstring>
#include <string>
#include <clocale>

#pragma comment(lib, "setupapi.lib")		//линкуем либу для функций из setupapi.h

using namespace std;

void findInFile(string DEV, string VEN);
void getInfoPCI(HDEVINFO deviceInfoSet);
HDEVINFO getDeviceInfoSet();