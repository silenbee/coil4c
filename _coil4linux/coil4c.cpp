﻿// coil4c.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

//#include "readData.h"
//#include <iostream>
//
//int main()
//{
//	vector<vector<string>> strArray;
//	strArray = readcsv("E://data.csv");
//	for (int i = 0; i < strArray.size(); i++)
//	{
//		for (int j = 0; j < 10; j++)
//			cout << strArray[i][j] << "  ";
//		cout << endl;
//	}
//}
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<vector>
#include<string>
#include"fftw3.h"
#include"readData.h"
using namespace std;

const double PI = 3.1415;
int N = 4000;
int step = 5;

void compute_data(vector<vector<int> > &intArray, vector<double> &res);
int check_data(const vector<double> &res, vector<double>& grad_value);

int main(){
	// read data csv
	vector<vector<string> > strArray;
	vector<vector<int> > intArray;
	vector<double> grad_value;
	vector<double> res;
	string dataAddr = "./data.csv";
	strArray = readcsv(dataAddr.c_str());
	for (int i = 0; i < 4; i++) {
		vector<int> s;
		intArray.push_back(s);
	}
	for (int i = 0; i < strArray.size(); i++)
	{
		for (int j = 0; j < strArray[i].size(); j++)
			intArray[i].push_back(atoi(strArray[i][j].c_str()));
	}

	// after read data
	
	compute_data(intArray, res);

	printf("res.size: %ld\n", res.size());
	printf("res:\n");
	for (int i = 0; i < 10; i++) {
		printf("%f ", res[i]);
	}
	// check 
	int grad_max_point = check_data(res, grad_value);
	//debug part
	
	if(ampli_check(intArray[0], grad_max_point)){
		printf("abnormal point detected at: %d",grad_max_point);
		// printf("")
	}

	return 0;
}


void compute_data(vector<vector<int> > &intArray, vector<double> &res){
	// do fft

	//-----define
	int len = 4000;
	double* in = NULL;
	// 如果要使用float版本,需先引用float版本的lib库,然后在fftw后面加上f后缀即可.
	fftw_complex* out = NULL;  // fftwf_complex --> 即为float版本
	fftw_plan p;
	in = (double*)fftw_malloc(sizeof(double) * len);
	out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * len);
	cout << "passed" << endl;
	//-----define
	// only tackle the index 0
	for (int i = (int)(N / 2); i < (50000 - (int)(N / 2)); i += step) {
		//vector<int> tmp;
		//copy(intArray[0].begin() + (i - N / 2), intArray[0].begin() + (i + N / 2), tmp.begin()); //区间拷贝
		vector<int> tmp(intArray[0].begin() + (i - N / 2), intArray[0].begin() + (i + N / 2));
		// fourier 
		for (int j = 0; j < tmp.size(); j++)
			in[j] = double(tmp[j]);
		p = fftw_plan_dft_r2c_1d(len, in, out, FFTW_ESTIMATE);
		fftw_execute(p);
		
		double len = sqrt(out[2][0] * out[2][0] + out[2][1] * out[2][1]);
		len /= (N / 2);
		res.push_back(len);
		fftw_destroy_plan(p);
	}

	fftw_free(in);
	fftw_free(out);

}

int check_data(const vector<double> &res, vector<double>& grad_value){
	grad_value = grad(res);
	printf("\ngrad value of res:\n");
	for (int i = 0; i < 10; i++) {
		printf("%f ", grad_value[i]);
	}
	printf("\n");

	grad_value = m_conv(grad_value, 500, true);
	grad_value = m_conv(grad_value, 100, false);

	printf("grad value after convolve:\n");
	for (int i = 0; i < 10; i++) {
		printf("%f ", grad_value[i]);
	}

	printf("\n");

	int k = 0;
	for (int i = 1; i < grad_value.size(); i++)
	{
		if (grad_value[i] > grad_value[k]) k = i;
	}
	// k = k * step + N / 2;
	printf("value of k: %d\n", k);
	k = k * step + N / 2;
	printf("index of max: %d\n", k);
	// 释放资源
	return k;
	
}