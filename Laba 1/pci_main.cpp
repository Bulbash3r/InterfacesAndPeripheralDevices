#include "PCI.h"

using namespace std;

int main() {
		setlocale(LC_ALL, "Russian");

		HDEVINFO deviceInfoSet = getDeviceInfoSet();
		getInfoPCI(deviceInfoSet);

		if (!SetupDiDestroyDeviceInfoList(deviceInfoSet)) {
				cout << GetLastError();
		}
		system("pause");
		return 0;
}