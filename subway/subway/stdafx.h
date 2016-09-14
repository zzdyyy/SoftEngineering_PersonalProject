// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#define DEBUG

// TODO:  在此处引用程序需要的其他头文件

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

//user-defined header
#include "data.h"

//functions from fileinput.cpp
void ReadDataFromFile();

//functions from algorithms.cpp
void StationQuery();
#define SHORTEST 0
#define FEWEST_TRANSFER 1
void ShortestPath(const std::string &station1, const std::string &station2, int type);
void TSP(const string &station);

