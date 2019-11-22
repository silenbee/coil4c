// coil4c.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "readData.h"
#include <iostream>

int main()
{
	vector<vector<string>> strArray;
	strArray = readcsv("E://data.csv");
	for (int i = 0; i < strArray.size(); i++)
	{
		for (int j = 0; j < 10; j++)
			cout << strArray[i][j] << "  ";
		cout << endl;
	}
}


