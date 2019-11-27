#include "readData.h"
#include<math.h>
vector<vector<string>> readcsv(string filePath) {
	ifstream inFile(filePath, ios::in);//inFile来自fstream,ifstream为输入文件流(从文件读入)
	string lineStr;
	vector<vector<string>> strArray;
	for (int i = 0; i < 4; i++) {
		vector<string> s;
		strArray.push_back(s);
	}
	for (int i = 0; i < 3; i++)
		getline(inFile, lineStr);	//jump to fist line
	while (getline(inFile, lineStr)) //getline来自sstream
	{
		stringstream ss(lineStr);//来自sstream
		string str;
		//按照逗号分隔
		getline(ss, str, ',');	//skip the time colume
		for (int i = 0; i < 4; i++) {
			if (getline(ss, str, ','))
				strArray[i].push_back(str);//一行数据以vector保存
		}
	}
	return strArray;
}

vector<float> grad(vector<float> input) {
	vector<float> op;
	float tmp;
	for (int i = 0; i < input.size(); i++) {
		if (i >= 2 && i <= input.size() - 2)
			tmp = (input[i + 1] - input[i - 1]) / 2;
		else if (i == 0)
			tmp = input[1] - input[0];
		else tmp = input[i-1] - input[i];
		op.push_back(abs(tmp));
	}
	return op;
}