#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

#include "Heap.h"
#include "HuffmanTree.h"
#include "CharInfo.h"
#include "Compress.h"
#include "Uncompress.h"
#include "assert.h"
#include <string>
#include <windows.h>
#include <ctime>

int main()
{

	DWORD Start = ::GetTickCount();
	Compress<CharInfo> cf("Input.BIG");
	Uncompress<CharInfo> ucf("CompressFile.txt", "configFile.txt");
	DWORD End = ::GetTickCount();
	int TimeUsed = (End - Start) / 1000;

	cout << "TimeUsed:" << TimeUsed << endl;

	system("pause");
	return 0;
}
