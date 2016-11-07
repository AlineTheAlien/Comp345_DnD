//! @file 
//! @brief Header file for the MapEditor class  
//! The following class implements the map editor according to the requirements.
//! It allows a user to modify, and create maps
//! The user can load previously created maps and save new ones
//! The library used for serialization of classes is Boost.Serialization
//! It was used because of its efficiency and portability. With Boost, it is possible
//! to serialize and export a class into a binary data file
//! Vectors were used to display the available maps. They are dynamic and useful when
//! the size of the map list isn't known in advance

#pragma once
#include "Map.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <boost/filesystem.hpp>
using namespace std;

class MapEditor
{
private:
	//!Current map instance
	Map* map;
	//!Available maps to load
	vector<string> availableMaps;
public:
	MapEditor();
	~MapEditor();
	void newMap(int mapX, int mapY);
	int getMapSizeX();
	int getMapSizeY();
	void setTile(int x, int y, char object);
	char getTile(int x, int y);
	string getAvailableMap(int index);
	void setAvailableMaps();
	int getAvailableMapsSize();
	bool loadMap(string mapName);
	void saveMap(string mapName);
};


