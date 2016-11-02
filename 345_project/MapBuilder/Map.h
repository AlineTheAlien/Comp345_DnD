//! @file 
//! @brief Header file for the map class  
//! The following class implements a map according to the rules of Dungeons and Dragons
//! The map consists of a grid. The reason a dynamic array was used was to allow the player
//! to determine the size during creation. A one dimensional array allows simplicity and a better
//! performance than a 2D array. In each tile of the map, there could be an enemy, a chest, a wall,
//! a door or the player.

#ifndef MAP_H
#define MAP_H
#include "MapObject.h"
#include "ItemContainer.h"
#include "Item.h"
#include "Character.h"

//! Class implementing a game map
class Map
{
private:
	//! constant integer for map length
	static const int MAX_LENGTH = 20;
	//! constant integer for map width
	static const int MAX_WIDTH = 20;
	//! integer for map vertical size
	int mapY;
	//! integer for map horizontal size
	int mapX;
	//! Pointer to pointers of objects of the map
	MapObject** map;

public:

	//! constant character that represents the door on the map
	static const char DOOR = 'D';
	//! constant character that represents walls on the map
	static const char WALL = 'W';

	Map();
	Map(int x, int y);
	~Map();

	void setChest(int x, int y, MapObject* chest);
	void setPlayer(int x, int y, MapObject* player);
	void setEnemy(int x, int y, MapObject* enemy);
	void setTile(int x, int y, MapObject* object);

	int getMapY();
	int getMapX();
	MapObject* getTile(int x, int y);
	bool isOccupied(int x, int y);
	void displayTakenPositions();
	void displayObjectAtPosition(int x, int y);
	void showMap();
};
#endif