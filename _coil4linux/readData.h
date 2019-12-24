// #pragma once
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
using namespace std;

vector< vector<string> > readcsv(string filePath);
vector<float> grad(vector<float> input);
vector<double> grad(vector<double> input);
vector<float> m_conv(vector<float> input,int r,bool mean);
vector<double> m_conv(vector<double> input,int r,bool mean);

bool ampli_check(const vector<int> &input, int point);