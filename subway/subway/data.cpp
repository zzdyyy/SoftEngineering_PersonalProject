//this file is the main code of data-processing
#include "stdafx.h"

//global data structure
MetroLineList_t MetroLineList;	//Global MetroLine table
StationList_t StationList;	//Global Station table

//add a new line into MetroLineList, and return the id
MetroLine_id_t AddLineToMetroLineList(const string &name)
{
	//ensure that there is no repeated name
	for (MetroLineList_t::iterator iter = MetroLineList.begin(); iter != MetroLineList.end(); ++iter)
	{
		if (iter->getName() == name)
			throw(string("Repeated MetroLine name found: " + name));
	}
	
	//No repeated name :), add new line
	MetroLineList.push_back(MetroLine(name));
	
	return MetroLineList.size() - 1;
}

//add a new station into StationList, and return the id
Station_id_t AddStationToStationList(const string &name)
{
	//find that if there exist one record
	for (StationList_t::iterator iter = StationList.begin(); iter != StationList.end(); ++iter)
	{
		if (iter->getName() == name)
			return iter - StationList.begin();
	}

	//No repeated name, add new station
	StationList.push_back(Station(name));

	return StationList.size() - 1;
}

//return the id of a metro line by name
MetroLine_id_t IdOfMetroLine(const string &name)
{
	MetroLineList_t::iterator iter = MetroLineList.begin();
	for (; iter != MetroLineList.end(); ++iter)
	{
		if (iter->getName() == name)
			break;
	}
	return iter - MetroLineList.begin();
}

//return the id of a station by name
Station_id_t IdOfStation(const string &name)
{
	StationList_t::iterator iter = StationList.begin();
	for (; iter != StationList.end(); ++iter)
	{
		if (iter->getName() == name)
			break;
	}
	return iter - StationList.begin();
}