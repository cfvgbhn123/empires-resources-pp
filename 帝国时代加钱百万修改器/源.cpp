#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include "tlhelp32.h"

using namespace std;

void changeGame(unsigned long &p1) {
	HWND gameHwnd = FindWindow(NULL, L"Age of Empires");
	//gameHwnd = (HWND)2596;
	//LPTSTR str=NULL;
	//GetWindowText(gameHwnd, str, 100);
	cout << gameHwnd << endl;
	DWORD processid;
	::GetWindowThreadProcessId(gameHwnd, &processid);
	cout << processid << endl;
	//��ָ������
	HANDLE processH = ::OpenProcess(PROCESS_ALL_ACCESS, false, processid);
	cout << processH << endl;
	//��ȡָ��
	int nSize = 0;
	unsigned long resourcesPtr1 = 0;
	ReadProcessMemory(processH, (void*)0x006a06b0, &resourcesPtr1, sizeof(resourcesPtr1), NULL);
	cout << "��ȡһ��ָ��ƫ��" << (void*)resourcesPtr1 << endl;
	resourcesPtr1 = resourcesPtr1 + 0x40;
	unsigned long resourcesPtr2 = 0;
	ReadProcessMemory(processH, (void*)resourcesPtr1, &resourcesPtr2, sizeof(resourcesPtr2), NULL);
	cout << "��ȡ����ָ��ƫ��" << (void*)resourcesPtr2 << endl;
	resourcesPtr2 = resourcesPtr2 + 0x4;
	unsigned long resourcesPtr3 = 0;
	ReadProcessMemory(processH, (void*)resourcesPtr2, &resourcesPtr3, sizeof(resourcesPtr3), NULL);
	cout << "��ȡ����ָ��ƫ��" << (void*)resourcesPtr3 << endl;
	resourcesPtr3 = resourcesPtr3 + 0x50;
	unsigned long resourcesPtr4 = 0;
	ReadProcessMemory(processH, (void*)resourcesPtr3, &resourcesPtr4, sizeof(resourcesPtr4), NULL);
	cout << "��ȡ4��ָ��ƫ��" << (void*)resourcesPtr4 << endl;
	p1 = resourcesPtr4;
	resourcesPtr4 = resourcesPtr4 + 0;
	unsigned long foodPtr = 0;
	ReadProcessMemory(processH, (void*)resourcesPtr4, &foodPtr, sizeof(foodPtr), NULL);
	cout << "��ȡʳ��" << *(float*)&foodPtr << endl;
	resourcesPtr4 = resourcesPtr4 + 4;
	unsigned long woodPtr = 0;
	ReadProcessMemory(processH, (void*)resourcesPtr4, &woodPtr, sizeof(woodPtr), NULL);
	cout << "��ȡľ��" << *(float*)&woodPtr << endl;
	resourcesPtr4 = resourcesPtr4 + 4;
	unsigned long stonePtr = 0;
	ReadProcessMemory(processH, (void*)resourcesPtr4, &stonePtr, sizeof(stonePtr), NULL);
	cout << "��ȡʯͷ" << *(float*)&stonePtr << endl;
	resourcesPtr4 = resourcesPtr4 + 4;
	unsigned long goldPtr = 0;
	ReadProcessMemory(processH, (void*)resourcesPtr4, &goldPtr, sizeof(goldPtr), NULL);
	cout << "��ȡ�ƽ�" << *(float*)&goldPtr << endl;
	for (size_t i = 0; i < 4; i++)
	{
		float bbb = NULL;
		if (i == 0) {
			bbb = *(float*)&foodPtr;
		}
		else if (i == 1) {
			bbb = *(float*)&woodPtr;
		}
		else if (i == 2) {
			bbb = *(float*)&stonePtr;
		}
		else if (i == 3) {
			bbb = *(float*)&goldPtr;
		}
		bbb += 1000000;

		cout << bbb << endl;
		WriteProcessMemory(processH, (void*)(resourcesPtr4 - 4 * i), &bbb, sizeof(bbb), NULL);
	}

	//DWORD pid = 5676;

}
int main() {
	unsigned long  p1 = NULL;
	changeGame(p1);
	cout << "��Դָ��" << (float*)p1 << endl;
	system("pause");
	return 0;
}