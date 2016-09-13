#pragma once

#include "stdafx.h"

//the id type of a MetroLine and a Staion
typedef size_t MetroLine_id_t;
typedef size_t Station_id_t;

//represents one metro line of the subway system, including the name and stations.
class MetroLine
{
	string name;
public:
	//stores the id of stations on this line
	typedef std::vector<Station_id_t> Stations_t;
	Stations_t Stations;

	MetroLine(const string &theName): name(theName) {}
	string getName() { return name; }
};

//represents one subway station, including the name and lines across it.
class Station
{
	string name;
public:
	//stores the id of metrolines across the station
	typedef std::vector<MetroLine_id_t> MetroLines_t;
	MetroLines_t MetroLines;

	//stores the id and (the id of the line which connects the two stations) of adjoint stations
	struct EdgeAndStation_t
	{
		Station_id_t StationId;
		MetroLine_id_t EdgeLineId;
	};
	typedef std::list<EdgeAndStation_t> Adjoins_t;
	Adjoins_t adjoins;
	
	Station(const string &theName): name(theName) {}
	string getName() { return name; }
};

//declaration of global data structure
typedef std::vector<MetroLine> MetroLineList_t;
typedef std::vector<Station> StationList_t;
extern MetroLineList_t MetroLineList;	//Global MetroLine table
extern StationList_t StationList;	//Global Station table
