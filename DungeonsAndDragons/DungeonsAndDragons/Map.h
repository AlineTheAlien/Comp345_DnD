//! @file 
//! @brief Header file for the map class  
//! The following class implements a map according to the rules of Dungeons and Dragons
//! The map consists of a grid. In each tile of the map, there could be an enemy, a chest, a wall,
//! a door or the player. The player will be able to move everywhere except on wall tiles which are
//! considered as occupied tiles that the player can't walk on. After creation of the map, the validatePath()
//! method will be called to validate the map. A path must exist between the player and the door for the map to be valid. For now,
//! the rules allow only one door and one player on the map. The door is considered in the game as the exit point.
//! No external libraries were used. The map is presented in the console for simplicity as a matrix.

#pragma once
#include <boost/serialization/serialization.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
#include <vector>
#include "MapObject.h"
#include "Character.h"
#include "ItemContainer.h"
#include "Armor.h"
#include "Boots.h"
#include "Ring.h"
#include "Belt.h"
#include "Shield.h"
#include "Weapon.h"
#include "Helmet.h"
using namespace std;

//! Class implementing a game map
class Map
{
private:
	//! constant integer for map length
	const int MAX_LENGTH = 20;
	//! constant integer for map width
	const int MAX_WIDTH = 20;
	//! integer for map vertical size
	int mapY;
	//! integer for map horizontal size
	int mapX;
	//! vector of characters that represents the map
	vector<MapObject*> map;
	//! Pointer to a one dimensional dynamic array of booleans that represents the path a player can take
	bool *correctPath;
	//! Pointer to a one dimension dynamic array of booleans that represents the locations the player visited
	bool *wasHere;


	//Boost serialization
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & mapX;
		ar & mapY;
		ar & map;
	}

public:
	//! constant character for enemies on the map
	const char ENEMY = 'E';
	//! constant character for chests on the map
	const char CHEST = 'C';
	//! constant character that represents the door on the map
	const char DOOR = 'D';
	//! constant character that represents walls on the map
	const char WALL = 'W';
	//! constant character that represents an empty tile on the map
	const char EMPTY = 'X';
	//! constant character that represents the player on the map
	const char PLAYER = 'P';
	//! constant character that represents a friend npc on the map
	const char FRIEND = 'F';

	Map();
	Map(int x, int y);
	~Map();
	bool validatePath();
	bool findPath(int x, int y);
	void setTile(int x, int y, MapObject* object);
	void movePlayer(int x, int y, MapObject* object);
	int getMapY();
	int getMapX();
	char getTile(int x, int y);
	bool verifyNearbyCharacter(MapObject*, int, int);
	MapObject* getObjectTile(int x, int y);
	bool isOccupied(int x, int y);
	void showMap();

};

