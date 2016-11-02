//! @file 
//! @brief Implementation file for the map class  
//!

#include <iostream>

#include "Map.h"
#include "Character.h"
using std::cout;
using std::cin;
using std::endl;


//! Implementation of the default constructor
Map::Map()
{
	//Default preset size
	mapX = MAX_WIDTH;
	mapY = MAX_LENGTH;
	map = new MapObject*[mapX*mapY];

	for (int i = 0; i < mapX * mapY; i++) {
		map[i] = NULL;
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
	map = new MapObject*[mapX*mapY];

	for (int i = 0; i < mapX * mapY; i++) {
		map[i] = NULL;
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

void Map::setChest(int x, int y, MapObject* chest)
{

	if (x > getMapX() || x < 0 || y > getMapY() || y < 0)
	{
		cout << "Invalid x,y input for setChest" << endl;
		return;
	}

	if (chest->getObjectType() != CHEST)
	{
		cout << "Invalid object input for setChest, an empty object was placed" << endl;
		return;
	}

	map[x + y * mapX] = chest;
}

void Map::setPlayer(int x, int y, MapObject* player)
{
	if (x > getMapX() || x < 0 || y > getMapY() || y < 0)
	{
		cout << "Invalid x,y input for setCharacter" << endl;
		return;
	}

	//If a player is already on the map, replace the last player position with an empty tile
	if (player->getObjectType() == PLAYER)
		for (int i = 0; i < mapY * mapX; i++)
		{
			if (map[i] != NULL) {
				if (map[i]->getObjectType() == PLAYER)
					map[i] = NULL;
			}
		}

	map[x + y * mapX] = player;
}

void Map::setEnemy(int x, int y, MapObject* enemy)
{
	if (x > getMapX() || x < 0 || y > getMapY() || y < 0)
	{
		cout << "Invalid x,y input for setEnemy" << endl;
		return;
	}
 map[x + y * mapX] = enemy;
}

//! Implementation setTile to set a specific tile on the map
//! @param x : an integer value of the vertical index of the map's grid
//! @param y : an integer value of the horizontal index of the map's grid
//! @param object : a MapObject object to set on the map
void Map::setTile(int x, int y, MapObject* object)
{
	if (x > getMapX() || x < 0 || y > getMapY() || y < 0)
	{
		cout << "Invalid x,y input for setTile" << endl;
		return;
	}

	if (object->getObjectType() != DOOR && object->getObjectType() != WALL)
	{
		cout << "Invalid object input for setTile, an empty object was placed" << endl;
		map[x + y * mapX] = NULL;
		return;
	}
	
	//If a door is already on the map, replace the last door position with an empty tile
	if (object->getObjectType() == DOOR)
		for (int i = 0; i < mapY * mapX; i++)
		{
			if (map[i] != NULL) {
				if (map[i]->getObjectType() == DOOR)
					map[i] = NULL;
			}
		}
	map[x + y * mapX] = object;
}

//! Implementation getTile to retrieve a specific tile on the map
//! @param x : an integer value of the vertical index of the map's grid
//! @param y : an integer value of the horizontal index of the map's grid
//! @return : a char value of the specfied tile on the map
MapObject* Map::getTile(int x, int y)
{
	return map[x + y * mapX];
}


//! Implementation isOccupied to check if a tile has a wall
//! @param x: an integer value of vertical index of the map's grid
//! @param y: an integer value of horizontal index of the map's grid
//! @return : a boolean true if the cell is occupied false otherwise
bool Map::isOccupied(int x, int y)
{
	return map[x + y * mapX]->getObjectType() == WALL;
}

//! Implementation showMap to display the map on the console
void Map::showMap()
{
	if (map == NULL)
	{
		cout << "There is currently no map." << endl;
	}
	else
	{
		for (int i = 0; i < mapY; i++)
		{
			for (int j = 0; j < mapX; j++)
			{
				MapObject* p;
				p = getTile(j, i);
				if (p != NULL)
					cout << p->getObjectType() << " ";
				else
					cout << "  ";
			}
			cout << endl;
		}
	}
	cout << endl;
}

void Map::displayTakenPositions()
{
	if (map == NULL)
	{
		cout << "There is currently no map." << endl;
	}
	else
	{
		for (int i = 0; i < mapY; i++)
		{
			for (int j = 0; j < mapX; j++)
			{
				MapObject* p;
				p = getTile(j, i);
				if (p != NULL)
					cout << "(" << i << "," << j << ")\n";
			}
		}
	}

}

void Map::displayObjectAtPosition(int j, int i) {
	MapObject* p;
	p = getTile(j, i);
	
	if (p == NULL) {
		cout << "There is no object at (" << i << "," << j << ")" << endl;
	}
	else {
		cout << "Characteristics of object at position (" << i << "," << j << "):" << endl;
		if (p->getObjectType() == 'P') {
			static_cast<Character*>(p)->displayCharacter();
		}
		else if (p->getObjectType() == 'D') {
			cout << "----" << endl;
			cout << "DOOR" << endl;
			cout << "----" << endl;
			cout << endl;
		}
		else if (p->getObjectType() == 'W') {
			cout << "----" << endl;
			cout << "WALL" << endl;
			cout << "----" << endl;
			cout << endl;
		}
		else if (p->getObjectType() == 'C') {
			static_cast<ItemContainer*>(p)->displayContainer();
		}
		else if (p->getObjectType() == 'E') {
			static_cast<Character*>(p)->displayCharacter();
		}
	}

}

Map::~Map()
{
	for (int i = 0; i < mapX * mapY; i++) {
		delete map[i];
		map[i] = NULL;
	}
	delete[] map;
	map = NULL;
}
