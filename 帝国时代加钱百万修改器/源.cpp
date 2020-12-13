#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include "tlhelp32.h"

using namespace std;

class Animal {
public:
	virtual void speak() = 0;
};
class Cat :public Animal {
public:
	void speak() {
		cout << "cat speak" << endl;
	}
};

class Dog :public Animal {
public:
	void speak() {
		cout << "dog speak" << endl;
	}
};

void test01(Animal *p) {
	p->speak();
}
void writeTxt() {
	ofstream ofs;
	ofs.open("c:\\abcdefg.txt");
	ofs << "主城列表" << endl;
	ofs << "暴风城" << endl;
	ofs << "奥格瑞玛" << endl;
	ofs << "幽暗城" << endl;
	ofs << "银月城" << endl;
	ofs << "铁炉堡" << endl;
	ofs << "达纳苏斯" << endl;
	ofs.close();
}

void loadTxt() {
	ifstream ifs;
	ifs.open("c:\\12113213123.txt");
}
template <class T>
void plusaa(T a, T b) {
	Person<int, int> p(5, 5);
	p.showPerson();
	p.showPerson2();
	system("dir /p");
	cout << a << b << endl;
	system("pause");
}

template <class T1, class T2>
class Person {
public:
	T1 n1;
	T2 n2;
	Person(T1 n1, T2 n2) {
		this->n1 = n1;
		this->n2 = n2;
	}
	void showPerson() {
		cout << "姓名为1" << this->n1 << endl;
		cout << "年龄为1" << this->n2 << endl;
	}
	void showPerson2();
};
template <class T1, class T2>
void Person<T1, T2>::showPerson2() {
	cout << "姓名为2" << this->n1 << endl;
	cout << "年龄为2" << this->n2 << endl;
}
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	DWORD  pid = 0;
	GetWindowThreadProcessId(hwnd, &pid);
	if (pid == GetCurrentProcessId()) // 判断pid
	{
		char text[1024];
		GetWindowTextA(hwnd, (LPSTR)text, 1024); // 必须含有标题文字
		if (strlen(text) != 0 && IsWindowVisible(hwnd))
		{
			// printf("%s\n", text);
			// targetWindow = hwnd;
			return FALSE;
		}
	}
	return TRUE;
}

void changeGame(unsigned long &p1) {
	HWND gameHwnd = FindWindow(NULL, L"Age of Empires");
	//gameHwnd = (HWND)2596;
	//LPTSTR str=NULL;
	//GetWindowText(gameHwnd, str, 100);
	cout << gameHwnd << endl;
	DWORD processid;
	::GetWindowThreadProcessId(gameHwnd, &processid);
	cout << processid << endl;
	//打开指定进程
	HANDLE processH = ::OpenProcess(PROCESS_ALL_ACCESS, false, processid);
	cout << processH << endl;
	//读取指针
	int nSize = 0;
	unsigned long resourcesPtr1 = 0;
	ReadProcessMemory(processH, (void*)0x006a06b0, &resourcesPtr1, sizeof(resourcesPtr1), NULL);
	cout << "读取一级指针偏移" << (void*)resourcesPtr1 << endl;
	resourcesPtr1 = resourcesPtr1 + 0x40;
	unsigned long resourcesPtr2 = 0;
	ReadProcessMemory(processH, (void*)resourcesPtr1, &resourcesPtr2, sizeof(resourcesPtr2), NULL);
	cout << "读取二级指针偏移" << (void*)resourcesPtr2 << endl;
	resourcesPtr2 = resourcesPtr2 + 0x4;
	unsigned long resourcesPtr3 = 0;
	ReadProcessMemory(processH, (void*)resourcesPtr2, &resourcesPtr3, sizeof(resourcesPtr3), NULL);
	cout << "读取三级指针偏移" << (void*)resourcesPtr3 << endl;
	resourcesPtr3 = resourcesPtr3 + 0x50;
	unsigned long resourcesPtr4 = 0;
	ReadProcessMemory(processH, (void*)resourcesPtr3, &resourcesPtr4, sizeof(resourcesPtr4), NULL);
	cout << "读取4级指针偏移" << (void*)resourcesPtr4 << endl;
	p1 = resourcesPtr4;
	resourcesPtr4 = resourcesPtr4 + 0;
	unsigned long foodPtr = 0;
	ReadProcessMemory(processH, (void*)resourcesPtr4, &foodPtr, sizeof(foodPtr), NULL);
	cout << "读取食物" << *(float*)&foodPtr << endl;
	resourcesPtr4 = resourcesPtr4 + 4;
	unsigned long woodPtr = 0;
	ReadProcessMemory(processH, (void*)resourcesPtr4, &woodPtr, sizeof(woodPtr), NULL);
	cout << "读取木材" << *(float*)&woodPtr << endl;
	resourcesPtr4 = resourcesPtr4 + 4;
	unsigned long stonePtr = 0;
	ReadProcessMemory(processH, (void*)resourcesPtr4, &stonePtr, sizeof(stonePtr), NULL);
	cout << "读取石头" << *(float*)&stonePtr << endl;
	resourcesPtr4 = resourcesPtr4 + 4;
	unsigned long goldPtr = 0;
	ReadProcessMemory(processH, (void*)resourcesPtr4, &goldPtr, sizeof(goldPtr), NULL);
	cout << "读取黄金" << *(float*)&goldPtr << endl;
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
	/*Cat cat;
	Dog dog;

	writeTxt();
	test01(&cat);
	test01(&dog);

	system("pause");*/

	unsigned long  p1 = NULL;
	changeGame(p1);
	cout << "资源指针" << (float*)p1 << endl;



	system("pause");
	return 0;
}