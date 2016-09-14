//the main algorithms
#include "stdafx.h"

//AdjustMatrix to accelerate the computing
//In the FindShortestPath, it was used to store the whole metro graph
//In the FewestTranser, it may store the metro graph of specific MetroLines
unsigned char *AdjustMatrix = nullptr;
size_t StationNum = 0;	//the width and height of AdjustMatrix
//a inline function to access AdjustMatrix as an 2-d array
static inline unsigned char &ajm(size_t i, size_t j) { return *(AdjustMatrix + i * StationNum + j); }

void FillInAdjustMatrix()
{
	//get an array dynamically
	StationNum = StationList.size();
	AdjustMatrix = new unsigned char[StationNum*StationNum];
	
	//fill the ajm with 0
	unsigned char *p = AdjustMatrix;
	for (size_t i = 0; i < StationNum*StationNum; ++i)
		*p++ = '\0';

	for (size_t id = 0; id < StationNum; ++id)	//for each row in ajm
	{
		Station s = GetStation(id);
		for (Station::Adjoins_t::iterator iter = s.adjoins.begin();
			iter != s.adjoins.end();
			++iter)
		{
			ajm(id, iter->StationId) = '\01';
		}
	}
}

void StationQuery()
{
	string linename;
	while (cin >> linename) //for each time the user input a line name
	{
		MetroLine_id_t id = IdOfMetroLine(linename);
		if (id >= MetroLineList.size())
		{
			cerr << "MetroLineName not founded. Please input again." << endl << endl;
			continue;
		}

		//print all stations in this metro line
		MetroLine &line = GetMetroLine(id);
		for (MetroLine::Stations_t::iterator iter = line.Stations.begin();
			iter != line.Stations.end();
			++iter)
		{
			cout << GetStation(*iter).getName() << endl;
		}
		cout << endl;
	}
}

void ShortestPath(const string &station1, const string &station2)
{
	FillInAdjustMatrix();
	cout << "shortest path:" << station1 << station2 << endl; system("pause");
}

void FewestTransferPath(const string &station1, const string &station2)
{
	cout << "fewest transfer path:" << station1 << station2 << endl;
}

void TSP(const string &station)
{
	cout << "TSP path:" << station << endl;
}