#include "stdafx.h"
#include "Campaign.h"
#include "iostream"

//! Default constructor of campaign
Campaign::Campaign()
{
}

//! Implementation of addMap to add a map to the mapPathList
//! @param mapName : a string representing the name of the map to add
void Campaign::addMap(string mapName)
{
	mapPathList.push_back(mapName);
	cout << "Current maps in the campaign: " << endl;
	for (int i = 0; i < mapPathList.size(); i++)
		cout << mapPathList.at(i) << " -> ";
	cout << "End" << endl;
}

//! Implementation of removeMap to remove the last map of the campaign in mapPathList
void Campaign::removeMap()
{
	if (!mapPathList.empty())
	{
		mapPathList.pop_back();
		cout << "Current maps in the campaign: " << endl;
		for (int i = 0; i < mapPathList.size(); i++)
			cout << mapPathList.at(i) << " -> ";
		cout << "End" << endl;
	}
	else
		cout << "Map list is empty" << endl;
}

//! Implementation of getMap to return the name of the map at a specific index
//! @param index : integer value of the index to find the map
//! @return : a string representating the specified map
string Campaign::getMap(int index)
{
	return mapPathList.at(index);
}

//! Implementation of getMapListSize to return the size of the campaign
//! @return : an integer value representing the size of the campaign
int Campaign::getMapListSize()
{
	return mapPathList.size();
}

//! Implementation of getName to return the name of the campaign
//! @return : a string value representing the name of the campaign
string Campaign::getName()
{
	return campaignName;
}

//! Implementation of setName to set the name of the campaign
void Campaign::setName(string name)
{
	campaignName = name;
}

//! Default destructor of class Campaign
Campaign::~Campaign()
{
}
