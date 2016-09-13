#pragma once

#include "stdafx.h"

//Pre-declarations
class MetroLine;
class Staion;
typedef std::vector<MetroLine> MetroLineList_t;
typedef std::vector<Station> StationList_t;
//the id type of a MetroLine and a Staion
typedef MetroLineList_t::size_type MetroLine_id_t;
typedef StationList_t::size_type Station_id_t;

//represents one metro line of the subway system, including the name and stations.
class MetroLine
{
	std::string name;
public:
	//stores the id of stations on this line
	typedef std::vector<Station_id_t> Stations_t;
	Stations_t Stations;

	MetroLine(const std::string &theName): name(theName) {}
	std::string getName() { return name; }
};

//represents one subway station, including the name and lines across it.
class Station
{
	std::string name;
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
	
	Station(const std::string &theName): name(theName) {}
	std::string getName() { return name; }
};

//declaration of global data structure
extern MetroLineList_t MetroLineList;	//Global MetroLine table
extern StationList_t StationList;	//Global Station table
