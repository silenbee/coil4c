#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<string>
using namespace std;

vector<vector<string>> readcsv(string filePath);
vector<float> grad(vector<float> input);

vector<float> m_conv(vector<float> input,int r,bool mean);