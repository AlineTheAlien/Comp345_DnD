#pragma once
#include "Map.h"
#include "MapObject.h"
#include "Dice.h"
//! Class for the implementation of a MapBuilder
class MapBuilder {
public:
	virtual void buildCharacter(char, int, int, MapObject*) = 0;
	virtual void buildContainer(int, int) = 0;

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

	void setPlayerLevel(int playerLevel) {
		this->playerLevel = playerLevel;
	}
protected:
	Map* map;
	int playerLevel; // Keeps track of the level of the player
};