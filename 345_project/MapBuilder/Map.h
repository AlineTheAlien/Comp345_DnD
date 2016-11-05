//! @file 
//! @brief Header file for the map class  
//!
//! Map class by teammate Nassim El Sayed was used and modified.
//!
//! The following class implements a map according to the rules of Dungeons and Dragons
//! The map consists of a grid. The reason a dynamic array was used was to allow the player
//! to determine the size during creation. A one dimensional array allows simplicity and a better
//! performance than a 2D array. In each tile of the map, there could be an enemy, a chest, a wall,
//! a door or the player.
//! --
//! My modification to this class:
//! Since I worked on ItemContainer/Item for the first assignment, I obtained the Map class from my teammate.
//! I have changed the map slightly, in that each cell of a map is a pointer to a MapObject object.
//! This allows more flexibility when creating actual objects of different types that inherit from the MapObject
//! and storing them in a cell of the map. I have also simplified the map for the sake of this assignment to
//! only contain some methods. No other libraries were used.

#ifndef MAP_H
#define MAP_H
#include "MapObject.h"
#include "ItemContainer.h"
#include "Item.h"
#include "Character.h"

//! Class for the implementation of a game map
class Map
{
private:
	//! Constant integer for map length
	static const int MAX_LENGTH = 20;
	//! Constant integer for map width
	static const int MAX_WIDTH = 20;
	//! Integer for map vertical size
	int mapY;
	//! Integer for map horizontal size
	int mapX;
	//! Pointer to pointers of objects of the map, newly added
	MapObject** map;
public:
	static const char DOOR = 'D';
	static const char WALL = 'W';
	static const char PLAYER = 'P';
	static const char CHEST = 'C';
	Map();
	Map(int x, int y);
	~Map();

	void setChest(int x, int y, MapObject* chest); // Newly added method for builder pattern to set a chest in the map
	void setPlayer(int x, int y, MapObject* player); // Newly added method for builder pattern to set the player in the map
	void setEnemy(int x, int y, MapObject* enemy); // Newly added method for builder pattern to set an enemy in the map
	void setTile(int x, int y, MapObject* object); 

	int getNumOfOccupiedTiles(); // Newly added method to get the number of objects currently in the map
	int getMapY();
	int getMapX();
	MapObject* getTile(int x, int y);
	void displayTakenPositions(); // Newly added method to display map positions that currently have an object
	void displayObjectAtPosition(int x, int y); // Newly added method to display characteristics of an object at a position
	void showMap();
};
#endif