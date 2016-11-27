//! @file 
//! @brief Implementation file for the map class  
//!

#include "stdafx.h"
#include <iostream>
#include "Map.h"
using std::cout;
using std::cin;
using std::endl;


//! Implementation of the default constructor
Map::Map()
{
	//Default preset size
	mapX = MAX_WIDTH;
	mapY = MAX_LENGTH;
	//map = new char(mapX * mapY);
	for (int i = 0; i < mapX * mapY; i++) {
		MapObject* p = NULL;
		map.push_back(p);
	}
}

//! Implementation of a constructor with parameters
//! @param x : integer for width of the map
//! @param y : integer for length of the map
Map::Map(int x, int y)
{
	if (x > MAX_WIDTH || x <= 0)
		x = MAX_WIDTH;
	if (y > MAX_LENGTH || y <= 0)
		y = MAX_LENGTH;
	mapX = x;
	mapY = y;

	for (int i = 0; i < mapX * mapY; i++) {
		MapObject* p = NULL;
		map.push_back(p);
	}
}

//! Implementation getVertical to get the number of rows in the map (y)
//! @return : an integer value of the number of rows on the map
int Map::getMapY()
{
	return mapY;
}

//! Implementation getHorizontal to get the number of columns in the map (x)
//! @return : an integer value of the number of columns on the map
int Map::getMapX()
{
	return mapX;
}

//! Implementation of validatePath to check if the map is valid according to the rules
//! @return : a boolean true if a valid path was found, false otherwise
bool Map::validatePath()
{
	int playerPositionX;
	int playerPositionY;
	bool validMap = false;
	bool playerExists = false;
	correctPath = new bool[mapY * mapX];
	wasHere = new bool[mapY * mapX];


	for (int i = 0; i < mapY; i++)  //Sets boolean arrays to false values
		for (int j = 0; j < mapX; j++)
		{
			correctPath[j + i * mapX] = false;
			wasHere[j + i * mapX] = false;
			if (map[j + i * mapX] != NULL) {
				if (map[j + i * mapX]->getObjectType() == 'P') //Finds player start position
				{
					playerPositionX = j;
					playerPositionY = i;
					playerExists = true;
				}
			}
		}

	//If player exists, call findPath method
	if (playerExists)
		validMap = findPath(playerPositionX, playerPositionY);

	delete[] correctPath;
	delete[] wasHere;
	correctPath = NULL;
	wasHere = NULL;
	return validMap;
}


//! Implementation of findPath to find the possible path on a current location on the map
//! @param x : an integer value of the vertical index of the map's grid
//! @param y : an integer value of the horizontal index of the map's grid
//! @return : a boolean true if a path was found, false if a wall was encountered or if location was already visited
bool Map::findPath(int x, int y)
{
	if (map[x + y * mapX] != NULL) {
		if (map[x + y * mapX]->getObjectType() == DOOR) //Checks if the door was reached
			return true;
	}
	if (isOccupied(x, y) || wasHere[x + y * mapX]) //Checks if not an empty cell or if already visited
		return false;

	wasHere[x + y * mapX] = true;

	if (x != 0) //Checks if not on left column
		if (findPath(x - 1, y)) //Calls the method to go left
		{
			correctPath[x + y * mapX] = true;
			return true;
		}

	if (x != mapX - 1) //Checks if not on right column
		if (findPath(x + 1, y)) //Calls the method to go right
		{
			correctPath[x + y * mapX] = true;
			return true;
		}

	if (y != 0) //Checks if not on top row
		if (findPath(x, y - 1)) //Calls the method to go up
		{
			correctPath[x + y * mapX] = true;
			return true;
		}

	if (y != mapY - 1) //Checks if not on bottom row
		if (findPath(x, y + 1)) //Calls method to go down
		{
			correctPath[x + y * mapX] = true;
			return true;
		}

	return false;
}

//! Implementataion setTile to set a specific tile on the map
//! @param x : an integer value of the vertical index of the map's grid
//! @param y : an integer value of the horizontal index of the map's grid
//! @param object : a char value to set on the map
void Map::setTile(int x, int y, MapObject* object)
{
	if (object != NULL) {
		if (x > getMapX() || x < 0 || y > getMapY() || y < 0)
		{
			cout << "Invalid x,y input for setTile" << endl;
			return;
		}

		if (object->getObjectType() != EMPTY && object->getObjectType() != ENEMY && object->getObjectType() != DOOR &&
			object->getObjectType() != WALL && object->getObjectType() != PLAYER && object->getObjectType() != CHEST && object->getObjectType() != FRIEND)
		{
			cout << "Invalid object input for setTile, an empty object was placed" << endl;
			return;
		}
		MapObject* ptr = object;
		//If a player is already on the map, replace the last player position with an empty tile
		if (object->getObjectType() == PLAYER)
			for (int i = 0; i < mapY * mapX; i++)
			{
				if (map[i] != NULL) {
					if (map[i]->getObjectType() == PLAYER)
					{
						delete map[i];
						map[i] = NULL;
					}
				}
			}

		//If a door is already on the map, replace the last door position with an empty tile
		if (object->getObjectType() == DOOR)
			for (int i = 0; i < mapY * mapX; i++)
			{
				if (map[i] != NULL) {
					if (map[i]->getObjectType() == DOOR)
					{
						delete map[i];
						map[i] = NULL;
					}
						
				}
			}
		map[x + y * mapX] = ptr;
	}
	else
		map[x + y * mapX] = NULL;
}

//! Implementation getTile to retrieve a specific tile on the map
//! @param x : an integer value of the vertical index of the map's grid
//! @param y : an integer value of the horizontal index of the map's grid
//! @return : a char value of the specfied tile on the map
char Map::getTile(int x, int y)
{
	if (map[x + y * mapX] != NULL) {
		return map[x + y * mapX]->getObjectType();
	}
	else
		return 'X';
}

MapObject* Map::getObjectTile(int x, int y)
{
	return map[x + y * mapX];
}

//! Implementation movePlayer to move player on the map on the desired cell
//! empties the cell of the previous position occupied by player
//! @param x : an integer value of the vertical index of the map's grid
//! @param y : an integer value of the horizontal index of the map's grid
void Map::movePlayer(int x, int y, MapObject* object)
{
	if (object->getObjectType() == PLAYER)
	{
		for (int i = 0; i < mapY * mapX; i++)
		{
			if (map[i] != NULL)
			{
				if (map[i]->getObjectType() == PLAYER)
				{
					map[i] = NULL;
				}
			}
		}
		map[x + y * mapX] = object;
	}
}


//! Implementation isOccupied to check if a tile has a wall
//! @param x: an integer value of vertical index of the map's grid
//! @param y: an integer value of horizontal index of the map's grid
//! @return : a boolean true if the cell is occupied false otherwise
bool Map::isOccupied(int x, int y)
{
	if (map[x + y * mapX] != NULL) {
		return map[x + y * mapX]->getObjectType() == WALL;
	}
	else
		return false;
}

//! Implementation showMap to display the map on the console
void Map::showMap()
{
	for (int i = 0; i < mapY; i++)
	{
		for (int j = 0; j < mapX; j++)
		{
			cout << getTile(j, i) << " ";
		}
		cout << endl;
	}
	cout << endl;
}

Map::~Map()
{
	//for (int i = 0; i < map.size(); i++) {
	//	delete map[i];
	//}
}
