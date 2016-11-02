//! @file 
//! @brief Header file for the MapBuilder class  
//!
#ifndef MAPBUILDER_H
#define MAPBUILDER_H

#include "Map.h"
#include "MapObject.h"
#include "Item.h"

//! Implementation of the abstract MapBuilder class
class MapBuilder {
public:
	void createNewMap(int x, int y, int playerLevel) {
		map = new Map(x, y);
		this->playerLevel = playerLevel;
	}
	virtual void buildWall(int, int) = 0;
	virtual void buildDoor(int, int) = 0;
	virtual void buildEnemy(int, int, string) = 0;
	virtual void buildPlayer(int, int) = 0;
	virtual void buildContainer(int, int, int, string) = 0;
	Map* getMap() {
		return map;
	}
protected:
	Map* map;
	int playerLevel;
};
#endif