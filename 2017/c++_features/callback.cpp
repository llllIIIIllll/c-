#include "stdafx.h"
#include <stdio.h>
#include <process.h>
#include <Windows.h>
#include <iostream>
using namespace std;
DWORD WINAPI TestFun(LPVOID lpParam);

typedef void(* CallBackFunc)(int i, int j) Callfunc;

class Thread {
public:
	Thread(int n, int m) :Num(n), Test(m) {};
	int Test;
	int Num;
	int ThreadNew();
	
	void test(int a, Callfunc cal);

	Callfunc cal;

};

void Thread::test(int a, Callfunc cal)
{
	this->cal = cal;
	this->ThreadNew();
}

DWORD WINAPI TestFun(LPVOID lpParam)
{
	while (true)
	{
		Thread * ptrData = (Thread *)lpParam;
		//cout << ptrData->Num << "   " << ptrData->Test << endl;
		ptrData->Num += 1;
		cal(ptrData->Num, ptrData->Test);
		Sleep(100);
	}
	return 0;
}
int Thread::ThreadNew()
{
	CreateThread(NULL, 0, TestFun, this, 0, NULL);
	return 0;
}
int main(int argc, char *argv[])
{
	int ret, iSum;
	Thread TestData(1, 2);

	TestData.ThreadNew();
	cin >> ret;

	while (true)
	{
		cin >> ret;
		cout << TestData.Num << endl;
	}
	Sleep(100000);
	return 0;
}
