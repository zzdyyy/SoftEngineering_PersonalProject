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