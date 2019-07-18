#include "pch.h"
#include<iostream>
#include<Windows.h>

using namespace std;

int main() {

	int readBXP, oldBXP, newBXP, readTotal, oldTotal, newTotal = 0;
	double run = 0;

	cout << "How difficult would you like the game to be? Type a number 1 - 9, 1 being close to normal, 9 being extremly easy." << endl;
	cin >> run;

	if (run != 0) {

	HWND hwnd = FindWindowA(NULL, "FINAL FANTASY VII");
	if (hwnd == NULL) {
		cout << "Cannot find window." << endl;
		Sleep(3000);
		exit(-1);
	} else {
		DWORD procID;
		GetWindowThreadProcessId(hwnd, &procID);
		HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);

		if (procID = NULL) {
			cout << "Cannot obtain process." << endl;
			Sleep(3000);
			exit(-1);
		} else {
			run += 1.0;
			oldBXP = 0;
			oldTotal = 0;
			for (;;) {
				ReadProcessMemory(handle, (PBYTE*)0x00C06650, &readTotal, sizeof(readTotal), 0);
				if ( readTotal != oldTotal ) {
					oldTotal = readTotal;
					ReadProcessMemory(handle, (PBYTE*)0x0099E2C0, &readBXP, sizeof(readBXP), 0);
					if (readBXP != oldBXP) {
						if (readBXP != 0) {
							cout << "Old Battle XP: " << oldBXP << endl;
							cout << "Read Battle XP: " << readBXP << endl;
							oldBXP = readBXP;
							newBXP = run * readBXP;
							cout << "Total XP is now: " << readTotal << endl;
							newTotal = readTotal - readBXP;
							cout << "Total XP after reduction is: " << newTotal << endl;
							newTotal += newBXP;
							cout << "After Addition its: " << newTotal << endl;
							WriteProcessMemory(handle, (LPVOID)0x00C06650, &newTotal, sizeof(newTotal), 0);
							WriteProcessMemory(handle, (LPVOID)0x00DBFDC8, &newTotal, sizeof(newTotal), 0);
						}
					}
				}
			}
		}
	}
	}
	return 0;
}
