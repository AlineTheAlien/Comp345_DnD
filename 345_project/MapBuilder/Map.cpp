//! @file 
//! @brief Implementation file for the map class  
//!
#include <iostream>
#include "Map.h"
#include "Character.h"
using std::cout;
using std::cin;
using std::endl;

//! Default constructor
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

//! Destructor
Map::~Map()
{
	for (int i = 0; i < mapX * mapY; i++) {
		delete map[i];
		map[i] = NULL;
	}
	delete[] map;
	map = NULL;
}

//! Cconstructor
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

//! Method to get the number of occupied tiles of the map
//! @return Number of objects on the map
int Map::getNumOfOccupiedTiles() {
	int ctr = 0;
	for (int i = 0; i < mapY; i++)
	{
		for (int j = 0; j < mapX; j++)
		{
			MapObject* p;
			p = getTile(j, i);
			if (p != NULL)
				ctr++;
		}
	}
	return ctr;
}

//! Implementation getVertical to get the number of rows in the map (y)
//! @return An integer value of the number of rows on the map
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

//! Method to place a chest on the map
//! @param x : Position x of the chest on the map as an integer value
//! @param y : Position y of the chest on the map as an integer value
//! @param chest : Pointer to a MapObject representing the chest
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
		map[x + y * mapX] = NULL;
		return;
	}
	map[x + y * mapX] = chest;
}

//! Method to place the player on the map
//! @param x : Position x of the player on the map as an integer value
//! @param y : Position y of the player on the map as an integer value
//! @param player : Pointer to a MapObject representing the player
void Map::setPlayer(int x, int y, MapObject* player)
{
	if (x > getMapX() || x < 0 || y > getMapY() || y < 0)
	{
		cout << "Invalid x,y input for setCharacter" << endl;
		return;
	}

	// If a player is already on the map, replace the last player position with an empty tile
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

//! Method to place an enemy on the map
//! @param x : Position x of the enemy on the map as an integer value
//! @param y : Position y of the enemy on the map as an integer value
//! @param enemy : a point to a MapObject object representing the enemy to be set on the map
void Map::setEnemy(int x, int y, MapObject* enemy)
{
	if (x > getMapX() || x < 0 || y > getMapY() || y < 0)
	{
		cout << "Invalid x,y input for setEnemy" << endl;
		return;
	}
 map[x + y * mapX] = enemy;
}

//! Method to set a door or a wall on the map
//! @param x : An integer value of the vertical index of the map's grid
//! @param y : An integer value of the horizontal index of the map's grid
//! @param object : A pointer to a MapObject object to set on the map
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
	
	// If a door is already on the map, replace the last door position with an empty tile
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

//! Method to retrieve a specific tile on the map
//! @param x : an integer value of the vertical index of the map's grid
//! @param y : an integer value of the horizontal index of the map's grid
//! @return A pointer to a MapObject found on the grid
MapObject* Map::getTile(int x, int y)
{
	return map[x + y * mapX];
}

//! Method to display the map on the console
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

//! Method to list all (x,y) positions of objects on the map grid
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

//! Method to display the characteristics of an object at a specified position
//! @param j : Position y in (i,j) of the object on the map as an integer value
//! @param i : Position x in (i,j)  of the object on the map as an integer value
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
