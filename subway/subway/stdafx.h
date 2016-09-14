// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#define DEBUG

// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�

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

