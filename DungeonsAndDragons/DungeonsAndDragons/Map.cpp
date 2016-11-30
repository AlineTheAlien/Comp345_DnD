//! @file 
//! @brief Implementation file for the map class  
//!

#include "stdafx.h"
#include <iostream>
#include "Map.h"
#include "Character.h"
#include "GameLogger.h"

using std::cout;
using std::cin;
using std::endl;

bool Map::logMap = true;


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
		ptr->setMapPosition(x, y);

	}
	else
		map[x + y * mapX] = NULL;

	NotifyGUI();
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

//! Implementation getObjectTile to retrieve a specific object on the map
//! @param x : an integer value of the vertical index of the map's grid
//! @param y : an integer value of the horizontal index of the map's grid
//! @return : a char value of the specified tile on the map
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
		if (map[x + y * mapX] != NULL)
		{
			delete map[x + y * mapX];
			map[x + y * mapX] = NULL;
		}
		map[x + y * mapX] = object;
		static_cast<Character*>(object)->setMapPosition(x, y);
		NotifyGUI();
	}
}

//! Implementation of a method that move a character and notify to the GUI
//! Empties the cell of the previous position occupied by character
//! @param x : an integer value of the vertical index of the map's grid
//! @param y : an integer value of the horizontal index of the map's grid
void Map::moveCharacter(int x, int y, MapObject* object)
{
	int j = static_cast<Character*>(object)->getMapX();
	int i = static_cast<Character*>(object)->getMapY();
	if (map[x + y * mapX] != NULL)
	{
		delete map[x + y * mapX];
		map[x + y * mapX] = NULL;
	}
	map[x + y * mapX] = object;
	map[j + i * mapX] = NULL;
	static_cast<Character*>(object)->setMapPosition(x, y);
	NotifyGUI();
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
//! Implementation unavailableTile to check if a tile is unavailable. This is used for combat movements.
//! @param x : an integer value of vertical index of the map's grid
//! @param y : an integer value of horizontal index of the map's grid
//! @return : a boolean true if the cell is occupied false otherwise
bool Map::unavailableTile(int x, int y) {
	if (map[x + y * mapX] != NULL) {
		bool verify = (map[x + y * mapX]->getObjectType() == CHEST || map[x + y * mapX]->getObjectType() == DOOR || map[x + y * mapX]->getObjectType() == WALL || map[x + y * mapX]->getObjectType() == PLAYER) || (map[x + y * mapX]->getObjectType() == ENEMY) || (map[x + y * mapX]->getObjectType() == FRIEND);
		return verify;
	}
	else
		return false;
}
//! Implementation showMap to display the map on the console
void Map::showMap()
{
	string s = "";

	if (logMap == true) {
		for (int i = 0; i < mapY; i++)
		{
			for (int j = 0; j < mapX; j++)
			{
				cout << getTile(j, i) << " ";
				s += (string(1, getTile(j, i)) + " ");
				//GameLogger::writeToLogFile(s1);
			}
			cout << endl;
			s += "\n";
			//GameLogger::writeToLogFile("\n");
		}
		cout << endl;
		s += "\n";
		//GameLogger::writeToLogFile("\n");
	}
	GameLogger::writeToLogFile(s);
}

Map::~Map()
{
	//for (int i = 0; i < map.size(); i++) {
	//	delete map[i];
	//}
}

//! Method to verify that a character is nearby
//! @param character : The targeted character
//! @param i : Position i of the player
//! @param j : Position j of the player
bool Map::verifyNearbyCharacter(MapObject* targetCharacter, int j, int i)
{
	bool check = false;
	int iOtherCharacter;
	int jOtherCharacter;

	if (targetCharacter != NULL) {
		iOtherCharacter = targetCharacter->getMapY();
		jOtherCharacter = targetCharacter->getMapX();
		// If other character at the top
		if (i - 1 == iOtherCharacter && j == jOtherCharacter) {
			check = true;
		}
		// If other character at the left
		if (i == iOtherCharacter && j - 1 == jOtherCharacter) {
			check = true;
		}
		// If other character at the right
		if (i == iOtherCharacter && j + 1 == jOtherCharacter) {
			check = true;
		}
		// If other character at the bottom
		if (i + 1 == iOtherCharacter && j == jOtherCharacter) {
			check = true;
		}
		// If other character at top left
		if (i - 1 == iOtherCharacter && j - 1 == jOtherCharacter) {
			check = true;
		}
		// If other character at top right
		if (i - 1 == iOtherCharacter && j + 1 == jOtherCharacter) {
			check = true;
		}
		// If other character at bottom left
		if (i + 1 == iOtherCharacter && j - 1 == jOtherCharacter) {
			check = true;
		}
		// If other character at bottom right
		if (i + 1 == iOtherCharacter && j + 1 == jOtherCharacter) {
			check = true;
		}
	}
	return check; // If other targeted character is not nearby, return false
}

//! Method to find all enemies on the map
//! return a vector of pointers to MapObject objects
vector<MapObject*> Map::findAllEnemies() {
	vector<MapObject*> v = vector<MapObject*>();
	for (int i = 0; i < mapY * mapX; i++)
	{
		if (map[i] != NULL) {
			if (map[i]->getObjectType() == ENEMY && static_cast<Character*>(map[i])->getHitPoints() > 0)
				v.push_back(map[i]);
		}
	}
	return v;
}

//! Method to find all friendly NPCs on the map
//! return a vector of pointers to MapObject objects
vector<MapObject*> Map::findAllFriends() {
	vector<MapObject*> v = vector<MapObject*>();
	for (int i = 0; i < mapY * mapX; i++)
	{
		if (map[i] != NULL) {
			if (map[i]->getObjectType() == FRIEND && static_cast<Character*>(map[i])->getHitPoints() > 0)
				v.push_back(map[i]);
		}
	}
	return v;
}