#define _CRT_SECURE_NO_WARNINGS
#include "PCI.h"

HDEVINFO getDeviceInfoSet()
{
		HDEVINFO deviceInfoSet;
		//GUID *guidDev = (GUID*)&GUID_DEVCLASS_USB;	//идентификатор устройства

		deviceInfoSet = SetupDiGetClassDevs(NULL,		//guidDev
				"PCI",																	//шина
				NULL,
				DIGCF_ALLCLASSES												//флаг "вернуть список установленных устройств класса"
		);

		if (deviceInfoSet == INVALID_HANDLE_VALUE)
		{
				return 0;
		}
		else return deviceInfoSet;
}

void getInfoPCI(HDEVINFO deviceInfoSet)
{
		TCHAR buffer[BUFFERSIZE];
		string DEV;
		string VEN;
		SP_DEVINFO_DATA DeviceInfoData;													//Указатель на структуру, хранящую данные об устройстве
		DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);				//Задаём размер в байтах

		//Перебираем все устройства
		for (int i = 0; SetupDiEnumDeviceInfo(deviceInfoSet,		//Набор устройств PCI
				i++,
				&DeviceInfoData)
				;)
		{
				ZeroMemory(&DeviceInfoData, sizeof(SP_DEVINFO_DATA));
				DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

				//Получаем данные об устройстве и проверяем, закончился ли список устройств
				if (SetupDiEnumDeviceInfo(deviceInfoSet,
						i,
						&DeviceInfoData) == FALSE)
				{
						if (GetLastError() == ERROR_NO_MORE_ITEMS)
						{
								break;
						}
				}
				//Получаем VendorID и DeviceID
				SetupDiGetDeviceInstanceId(deviceInfoSet,				
						&DeviceInfoData, 
						buffer, 
						sizeof(buffer), 
						0);	//nSize

				char tempDev[5];
				for (int j = 0; j < 4; j++) 
						tempDev[j] = tolower(strstr(buffer, "DEV")[j+4]);
				tempDev[4] = '\0';

				char tempVEN[5];
				for (int j = 0; j < 4; j++)
						tempVEN[j] = tolower(strstr(buffer, "VEN")[j+4]);
				tempVEN[4] = '\0';

				DEV = tempDev;
				VEN = tempVEN;

				cout << "Устройство №" << i << endl;
				findInFile(DEV, VEN);
				cout << endl;
		}
}

void findInFile(string DEV, string VEN)
{
		ifstream file("pci.id");
		while (file)
		{
				string str;
				getline(file, str);
				if ((int)str.find(VEN) == 0)
				{
						cout << "VendorID: " << VEN << endl;
						str.erase(str.begin(), str.begin() + 6);
						cout << "Производитель: " << str << endl;
						while (file)
						{
								getline(file, str);
								if ((int)str.find(DEV) != -1 && (int)str.find(DEV) == 1)
								{
										cout << "DeviceID: " << DEV << endl;
										str.erase(str.begin(), str.begin() + 7);
										cout << "Наименование: " << str << endl;
										break;
								}
						}
						break;
				}
		}
}