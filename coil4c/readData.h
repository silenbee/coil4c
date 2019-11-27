#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<string>
using namespace std;

vector<vector<string>> readcsv(string filePath);
vector<float> grad(vector<float> input);