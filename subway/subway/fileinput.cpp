//This file handles the input task from the file
#include "stdafx.h"
#include <fstream>
using std::ifstream;

#define SUBWAY_INFO_FILENAME "beijing-subway.txt"

//read data from the file and fill it in the MetroLineList and StationList
void ReadDataFromFile()
{
	try {
		//Open the input file
		ifstream fin(SUBWAY_INFO_FILENAME);
		if (!fin)
			throw(string("Can not open the file."));

		

		fin.close();
	}
	catch (string msg) {
		cerr << "Read input file \"" SUBWAY_INFO_FILENAME "\" error:" << endl
			<< msg << endl;
		int i; cin >> i;
		exit(EXIT_FAILURE);
	}
	return;
}
