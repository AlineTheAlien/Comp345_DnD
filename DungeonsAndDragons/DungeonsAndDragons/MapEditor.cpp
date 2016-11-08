#include "stdafx.h"
#include "MapEditor.h"



//! Default constructor for the MapEditor class
MapEditor::MapEditor()
{
	map = new Map();
	setAvailableMaps();
}


//! Implementation of setAvailableMaps to set all the available maps in the availableMaps vector
void MapEditor::setAvailableMaps()
{
	boost::filesystem::path path("Maps/");
	boost::filesystem::directory_iterator i(path);
	availableMaps.clear();
	cout << "Available maps : ";
	for (; i != boost::filesystem::directory_iterator(); i++)
	{
		availableMaps.push_back(i->path().filename().string());
		cout << i->path().filename().string() << ", ";
	}
	cout << endl;
}

//! Implementation of getAvailableMap to get a specific saved map 
//! @param index : an integer value of the position of the map in the array
//! @return : a string representing the name of the map
string MapEditor::getAvailableMap(int index)
{
	//get all maps available
	return availableMaps.at(index);
}

//! Implementation of getAvailableMapsSize to get the number of maps available
//! @return : an integer representing the size of the map
int MapEditor::getAvailableMapsSize()
{
	return availableMaps.size();
}

//! Implementation of newMap to create a new map
//! @param x : an integer value of the size in x axis of the map
//! @param y : an integer value of the size in y axis of the map
void MapEditor::newMap(int mapX, int mapY)
{
	delete map;
	map = NULL;
	map = new Map(mapX, mapY);
}

//! Implementation of getMapSizeX to get the map's size in X
//! @return : an integer value representing the the size of the map in x axis
int MapEditor::getMapSizeX()
{
	return map->getMapX();
}

//! Implementation of getMapSizeX to get the map's size in Y
//! @return : an integer value representing the the size of the map in y axis
int MapEditor::getMapSizeY()
{
	return map->getMapY();
}


//! Implementation of setTile to modifiy a map's tile
//! @param x : an integer value for the horizontal position
//! @param y : an integer value for the vertical position
//! @param object : a char value for the tile type
void MapEditor::setTile(int x, int y, MapObject* object)
{
	map->setTile(x, y, object);
	if (object == NULL) {
		cout << "Map was updated at position : " << x << ", " << y << " with 'X'"<< endl;
	}
	else
		cout << "Map was updated at position : " << x << ", " << y << " with " << object->getObjectType() << endl;
	map->showMap();
}


//! Implementation of getTile to get a specific tile
//! @param x : an integer value for the horizontal position
//! @param y : an integer value for the vertical position
//! @return : a char value for the tile type
char MapEditor::getTile(int x, int y)
{
	return map->getTile(x, y);
}

//! Implementation of saveMap to save the map as a binary file
//! @param mapName : name of the map to save
void MapEditor::saveMap(string mapName)
{
	//Create an output archive
	ofstream ofs("Maps/" + mapName, std::ios::binary);
	boost::archive::binary_oarchive ar(ofs);
	//Write data
	if (map->validatePath())
	{
		ar << map;
		cout << "Map is valid and was saved to file " << endl;
	}
	else
		cout << "Map is invalid!" << endl;
	ofs.close();
}


//! Implementation of loadMap to load a previously saved map
//! @param mapName : string representation the name of the map
bool MapEditor::loadMap(string mapName)
{
	delete map;
	map = NULL;
	//Create an input archive
	std::ifstream ifs("Maps/" + mapName, std::ios::binary);
	if (!ifs)
		return false;
	boost::archive::binary_iarchive ar(ifs);
	//read class state from archive
	ar >> map;
	ifs.close();
	if (!map->validatePath())
	{
		cout << "Loading the map has failed, it is not valid!" << endl;
		return false;
	}
	return true;
}
MapEditor::~MapEditor()
{
	delete map;
	map = NULL;
}
