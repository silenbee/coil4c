// coil4c.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
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

//#include<stdio.h>
//#include<stdlib.h>
//#include<math.h>
//#include"fftw3.h"
//using namespace std;
//
//const double M_PI = 3.1415;
//
//int main() {
//	printf("--------------start---------------\n");
//	int len = 8;
//	float* in = NULL;
//	// 如果要使用float版本,需先引用float版本的lib库,然后在fftw后面加上f后缀即可.
//	fftwf_complex* out = NULL;  // fftwf_complex --> 即为float版本
//	fftwf_plan p;
//	in = (float*)fftwf_malloc(sizeof(float) * len);
//	out = (fftwf_complex*)fftwf_malloc(sizeof(fftw_complex) * len);
//	float dx = 1.0 / len;
//
//	// 输入纯实数
//	for (int i = 0; i < len; i++) {
//		in[i] = sinf(2 * M_PI * dx * i) + sinf(4 * M_PI * dx * i);
//
//		printf("%.2f ", in[i]);
//	}
//	printf("\n\n");
//
//	// 傅里叶变换
//	p = fftwf_plan_dft_r2c_1d(len, in, out, FFTW_ESTIMATE);
//	fftwf_execute(p);
//
//	// 输出幅度谱
//	for (int i = 0; i < len; i++) {
//		float len = sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
//		printf("%.2f ", len);
//	}
//	printf("\n");
//
//	// 释放资源
//	fftwf_destroy_plan(p);
//	fftwf_free(in);
//	fftwf_free(out);
//
//
//	printf("--------------end---------------\n");
//	return 0;
//}


