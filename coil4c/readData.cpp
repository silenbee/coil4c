#include "readData.h"
#include<math.h>
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

vector<float> grad(vector<float> input) {
	vector<float> op;
	float tmp;
	for (int i = 0; i < input.size(); i++) {
		if (i >= 1 && i <= input.size() - 2)
			tmp = (input[i + 1] - input[i - 1]) / 2.0;
		else if (i == 0)
			tmp = input[1] - input[0];
		else tmp = input[i-1] - input[i];
		op.push_back(abs(tmp));
	}
	return op;
}

vector<float> m_conv(vector<float> input,int r,bool mean) {
	vector<float> res;
	int in_size = input.size();
	for (int i = 0; i < in_size; i++) {
		float sum = 0;
		float cnt = 0;
		if (i<r){
			for (int j = 0; j < i; j++) {
				sum += input[j];
				cnt += 1;
			}
		}
		else {
			for (int j = i - r; j <= i; j++) {
				sum += input[j];	
			}
			cnt += r;
		}
		sum += input[i];	//add itself
		if (i + r > in_size - 1) {
			for (int j = i+1; j < in_size; j++) {
				sum += input[j];
				cnt += 1;
			}
		}
		else {
			for (int j = i + 1; j < i+r+1; j++)
				sum += input[j];
			cnt += r;
		}
		if (mean)
			res.push_back(sum / cnt);
		else res.push_back(sum);
	}
	return res;
}