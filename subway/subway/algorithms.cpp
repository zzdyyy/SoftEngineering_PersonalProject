//the main algorithms
#include "stdafx.h"

//AdjustMatrix to accelerate the computing
//In the FindShortestPath, it was used to store the whole metro graph
//In the FewestTranser, it may store the metro graph of specific MetroLines
unsigned char **AdjustMatrix;

void FillInAdjustMatrix()
{
	//TODO
}

void StationQuery()
{
	string line;
	while (cin >> line)
		cout << "station query" << endl;
}

void ShortestPath(const string &station1, const string &station2)
{
	cout << "shortest path:" << station1 << station2 << endl;
}

void FewestTransferPath(const string &station1, const string &station2)
{
	cout << "fewest transfer path:" << station1 << station2 << endl;
}

void TSP(const string &station)
{
	cout << "TSP path:" << station << endl;
}