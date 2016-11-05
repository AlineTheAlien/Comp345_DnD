//! @file 
//! @brief Header file for the MapBuilder class  
//!
//! This is an abstract class used for the Builder Design Pattern. It is responsible for actually creating a Map product,
//! by delegating the construction of each map's parts to a concrete builder.
//! This class is a superclass of ConcreteMapBuilderA, which can load a map from a file as it was save,d as well
//! as ConcreteMapBuilderB, which can load a map adapted to the level of the player's level. It
//! contains virtual methods that are not implemented in this class, but in its subclasses as some of
//! these methods have different behaviors (load map as is vs load a map adapted to a level).
//! Following the rules of a Dungeon&Dragon game, the parts of a map can be a wall, door, enemy, player or container.
//! Each container contain a certain number of items with different enhancement bonus depending on the player's level
//! and each character has ability scores and a level, which can be different depending on the ConcreteBuilder used.
//! No external libraries were used aside from the standard libraries.
#ifndef MAPBUILDER_H
#define MAPBUILDER_H

#include "Map.h"
#include "MapObject.h"
#include "Item.h"

//! Class for the implementation of a MapBuilder
class MapBuilder {
public:
	//! Method to create a new map
	//! @param x : Width of the map as an integer value
	//! @param y : Length of the map as an integer value
	//! @param playerLevel : Current player's level as an integer value
	void createNewMap(int x, int y, int playerLevel) {
		map = new Map(x, y);
		this->playerLevel = playerLevel;
	}
	virtual void buildWall(int, int) = 0;
	virtual void buildDoor(int, int) = 0;
	virtual void buildEnemy(int, int, string) = 0;
	virtual void buildPlayer(int, int) = 0;
	virtual void buildContainer(int, int, int, string) = 0;

	//! Method to get map
	//! return A pointer to a map
	Map* getMap() {
		return map;
	}

	//! Method to set a map
	//! @param m : Pointer to a map
	void setMap(Map* m) {
		map = m;
	}
protected:
	Map* map;
	int playerLevel; // Keeps track of the level of the player
};
#endif