//the main algorithms
#include "stdafx.h"

//AdjustMatrix to accelerate the computing
//stores the whole metro graph
bool *AdjustMatrix = nullptr;
size_t StationNum = 0;	//the width and height of AdjustMatrix
						//a inline function to access AdjustMatrix as an 2-d array
static inline bool &ajm(size_t i, size_t j) { return *(AdjustMatrix + (i * StationNum + j)); }

void FillInAdjustMatrix()
{
	//get an array dynamically
	StationNum = StationList.size();
	AdjustMatrix = new bool[StationNum*StationNum];

	//fill the ajm with 0
	bool *p = AdjustMatrix;
	for (size_t i = 0; i < StationNum*StationNum; ++i)
		*p++ = false;

	for (size_t id = 0; id < StationNum; ++id)	//for each row in ajm
	{
		Station &s = GetStation(id);
		for (Station::Adjoins_t::iterator iter = s.adjoins.begin();
			iter != s.adjoins.end();
			++iter)
		{
			ajm(id, iter->StationId) = true;
		}
	}
}

//a function to compute the fewest transfer
void do_FillInAdjustMatix_FT(Station_id_t start, Station_id_t dest)
{
	//first compute the least transfer lines
	std::vector<MetroLine_id_t> lines, adding;
	bool flag = false; //found flag

	//add lines
	for (MetroLine_id_t line : GetStation(start).MetroLines)
	{
		adding.push_back(line);
		if (std::count(GetStation(dest).MetroLines.begin(),
			GetStation(dest).MetroLines.end(),
			line) > 0)	//dest is on adding line
		{
			flag = true;
			lines.push_back(line);
		}
	}
	
	while (!flag) //adding another transfer
	{
		std::vector<MetroLine_id_t> newadding;
		for (MetroLine_id_t line : adding)
		{
			lines.push_back(line);
			newadding.push_back(line);
		}
		adding.clear();

		for (MetroLine_id_t line : newadding)//for the lines in last transfer level
		{
			for (Station_id_t station : GetMetroLine(line).Stations)//iterate every station to transfer to new line
			{
				for (MetroLine_id_t newline : GetStation(station).MetroLines)//newly find line
				{
					if ((newline == line) || (std::count(lines.begin(), lines.end(), newline) > 0))
						continue;
					//truly new line
					adding.push_back(newline);
					if (std::count(GetStation(dest).MetroLines.begin(),
						GetStation(dest).MetroLines.end(),
						newline) > 0)	//dest is on adding line
					{
						flag = true;
						lines.push_back(newline);
					}
				}
			}
		}
	}

	std::vector<bool> station_allow(StationList.size(), false);	//whether a station is on lines

	for (MetroLine_id_t line : lines)
		for (Station_id_t station : GetMetroLine(line).Stations)
			station_allow[station] = true;

	//Now the stations are confirmed, fill in the matrix
	FillInAdjustMatrix();
	//clear the stations not on lines
	for (Station_id_t sid = 0; sid < StationNum; ++sid)
	{
		if (!station_allow[sid])
			for (Station_id_t i = 0; i < StationNum; ++i)
				ajm(sid, i) = false, ajm(i, sid) = false;
	}
	

}

//a type to store the path information
typedef std::vector<Station::EdgeAndStation_t> path_t;
//a function to search the shortest path in adjust matrix by Breadth-first Search,
//the result is giving as path_t. The start and dest should be valid Station id.
path_t do_ShortestPath_BFS(Station_id_t start, Station_id_t dest)
{
	typedef std::vector<Station_id_t> Stations_t;

	const size_t StationAmount = StationList.size();
	Stations_t searching, nextsearch;//stores the current level and next level of stations

	//stores the distances between a station and the destination
	unsigned int *distances = nullptr;
	distances = new unsigned int[StationAmount];
	
	//stores whether a station has been searched
	bool *searched = nullptr;
	searched = new bool[StationAmount];

	if (searched == nullptr || distances == nullptr)
		throw(string("Memory allocate failed."));

	for (size_t i = 0; i < StationAmount; ++i)
	{
		distances[i] = UINT_MAX;
		searched[i] = false;
	}

	//initialize searching
	searching.push_back(dest);//searching from destination
	size_t SearchedCycle = 0;
	size_t level = 1;
	distances[dest] = 0;
	searched[dest] = true;

	//start searching
	//for each level
	while (SearchedCycle < StationAmount && !searched[start])
	{
		//for each station
		for (Stations_t::iterator iter = searching.begin(); iter != searching.end(); ++iter)
		{
			Station_id_t to = *iter;
			//for each station can reach this station
			for (Station_id_t from = 0; from < StationAmount; ++from)
			{
				if (!ajm(from, to) || from == to)
					continue;
				if (!searched[from])//on the right line and never been searched
				{
					nextsearch.push_back(from);//search it's adjusts next level
					searched[from] = true;
					distances[from] = level;
#ifdef DEBUG
					cout << "DEBUG " << level << GetStation(from).getName() << endl;
#endif
				}
			}
			++SearchedCycle;
		}
		searching.clear();
		nextsearch.swap(searching);
		++level;
	}

	if (distances[start] == UINT_MAX)
		throw(string("Cannot reach destination from start."));

	//generate path
	path_t path;
	Station_id_t currentstation = start;
	while (true)//for each step
	{
		for (Station::Adjoins_t::iterator adj = GetStation(currentstation).adjoins.begin();
			adj != GetStation(currentstation).adjoins.end();
			++adj)//for possible next step
		{
			if (distances[adj->StationId] < distances[currentstation])
			{
				path.push_back(*adj);
				currentstation = adj->StationId;
				break;
			}
		}
		if (currentstation == dest)
			break;
	}

	//release heap memory
	delete[] searched;
	delete[] distances;
	searched = nullptr;
	distances = nullptr;

	return path;
}

//The controlflow function to find the shortest path (or fewest-transfer path) and print them
void ShortestPath(const string &station1, const string &station2, int type)
{
	try
	{
		Station_id_t sid1, sid2;
		sid1 = IdOfStation(station1);
		sid2 = IdOfStation(station2);
		//check the valid of station1 and station2
		if (sid1 >= StationList.size() || sid2 >= StationList.size())
			throw(string("The required station doesn't exist."));

		if (sid1 == sid2)
			cout << 1 << endl << station1 << endl;

		if (type == SHORTEST)
		{
			FillInAdjustMatrix();
		}
		else if(type == FEWEST_TRANSFER)
		{
			do_FillInAdjustMatix_FT(sid1, sid2);
		}
		else
			throw(string("ShortestPath(): Wrong parameter."));

		//calculate
		path_t path = do_ShortestPath_BFS(sid1, sid2);

		//print the path
		cout << (path.size() + 1) << endl;//the station number along the path
		cout << station1;//the starting station
		MetroLine_id_t lastline = path[0].EdgeLineId;//to store the board line
		for (path_t::iterator iter = path.begin(); iter != path.end(); ++iter)
		{
			if (iter->EdgeLineId != lastline)
			{
				lastline = iter->EdgeLineId;
				cout << "»»³Ë" << GetMetroLine(lastline).getName();
			}
			cout << endl << GetStation(iter->StationId).getName();
		}
		cout << endl;

		delete[] AdjustMatrix;
		AdjustMatrix = nullptr;
	}
	catch (string msg)
	{
		cerr << "Error: " << msg << endl;
		exit(EXIT_FAILURE);
	}
}

//The main function to response the station query. It wait the user to input a metro line name,
//print all the stations along the metro line and wait for next name again.
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

void TSP(const string &station)
{
	cout << "Not implemented." << endl;
}

