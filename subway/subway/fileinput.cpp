//This file handles the input task from the file
#include "stdafx.h"
#include <fstream>
using std::ifstream;

#define SUBWAY_INFO_FILENAME "beijing-subway.txt"

//read data from the file and fill it in the MetroLineList and StationList
void ReadDataFromFile()
{
	try
	{
		//Open the input file
		ifstream fin(SUBWAY_INFO_FILENAME);
		if (!fin)
			throw(string("Can not open the file."));
		
		string linedirective, linename, stationdirective, edgedirective;
		int stationnum, edgenum;
		while (fin >> linedirective)//for each metro line
		{
			if (!(fin >> linename) || linedirective != string("line"))
				throw(string("Wrong format: MetroLine directive \"line\" and MetroLineName are needed."));

#ifdef DEBUG
			cerr << "DEBUG ReadDataFromFile(): at " << linename << endl;
#endif

			//now we got the name of metro line, let's add it into MetroLineList.
			MetroLine_id_t lineid = AddLineToMetroLineList(linename);
			
			//input station number
			if (!(fin >> stationdirective >> stationnum) || stationdirective != string("station"))
				throw(string("Wrong format: Station directive and a number are needed."));

			//input station names
			for (int i = 0; i < stationnum; ++i)
			{
				string stationname;
				if(!(fin>>stationname))
					throw(string("Wrong format: A StationName is needed."));

				//now we got the name of station, let's add it into StationList.
				Station_id_t stationid = AddStationToStationList(stationname);
				
				//update the MetroLine station table
				if (std::find(GetMetroLine(lineid).Stations.begin(),
							GetMetroLine(lineid).Stations.end(),
							stationid)
					!= GetMetroLine(lineid).Stations.end())
					throw(string("Repeated stations founded in one MetroLine."));
				GetMetroLine(lineid).Stations.push_back(stationid);

				//update the Station metroline list
				if (std::find(GetStation(stationid).MetroLines.begin(),
					GetStation(stationid).MetroLines.end(),
					lineid)
					!= GetStation(stationid).MetroLines.end())
					throw(string("Repeated stations founded in one MetroLine."));
				GetStation(stationid).MetroLines.push_back(lineid);
			}
			
			//input edge number
			if (!(fin >> edgedirective >> edgenum) || edgedirective != string("edge"))
				throw(string("Wrong format: Edge directive and a number are needed."));

			//construct edges
			for (int i = 0; i < edgenum; ++i)
			{
				string sdsign, station1, station2;
				Station_id_t sid1, sid2;
				if (!(fin >> sdsign >> station1 >> station2) || (sdsign!=string("s") && sdsign != string("d")))
					throw(string("Wrong format: An edge is needed."));

				//now we got a inputed edge, added it into our Station list
				sid1 = IdOfStation(station1);
				sid2 = IdOfStation(station2);
				if (sid1 >= StationList.size() || sid2 >= StationList.size())
					throw(string("An unexist station founded in an edge."));
				GetStation(sid1).adjoins.push_back(Station::EdgeAndStation_t(sid2, lineid));
				if(sdsign == string("d"))
					GetStation(sid2).adjoins.push_back(Station::EdgeAndStation_t(sid1, lineid));
			}
		}
		

		fin.close();
	}
	catch (string msg)
	{
		cerr << "Read input file \"" SUBWAY_INFO_FILENAME "\" error:" << endl
			<< msg << endl;
		exit(EXIT_FAILURE);
	}
	return;
}
