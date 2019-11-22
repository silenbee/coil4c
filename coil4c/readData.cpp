#include "readData.h"

vector<vector<string>> readcsv(string filePath) {
	ifstream inFile(filePath, ios::in);//inFile����fstream,ifstreamΪ�����ļ���(���ļ�����)
	string lineStr;
	vector<vector<string>> strArray;
	for (int i = 0; i < 4; i++) {
		vector<string> s;
		strArray.push_back(s);
	}
	for (int i = 0; i < 3; i++)
		getline(inFile, lineStr);	//jump to fist line
	while (getline(inFile, lineStr)) //getline����sstream
	{
		stringstream ss(lineStr);//����sstream
		string str;
		//���ն��ŷָ�
		getline(ss, str, ',');	//skip the time colume
		for (int i = 0; i < 4; i++) {
			if (getline(ss, str, ','))
				strArray[i].push_back(str);//һ��������vector����
		}
	}
	return strArray;
}