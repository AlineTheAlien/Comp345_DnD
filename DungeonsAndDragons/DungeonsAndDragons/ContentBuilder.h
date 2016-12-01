//! @file 
//! Builder design pattern for building a map's content
#pragma once
#include "Map.h"
#include "MapObject.h"
#include "Dice.h"
#include "Item.h"
#include "Enhancement.h"

//! Class for the implementation of a ContentBuilder
class ContentBuilder {
public:
	virtual void buildCharacter(char, int, int, MapObject*) = 0;
	virtual void buildContainer(int, int, vector<Item*>&) = 0;

	//! Method to get map product
	//! return A pointer to a map
	Map* getMap() {
		return map;
	}
	
	//! Method to set a map
	//! @param m : Pointer to a map
	void setMap(Map* m) {
		map = m;
	}

	//! Method to set the level of a player 
	//! @param playerLevel : level of player
	void setPlayerLevel(int playerLevel) {
		this->playerLevel = playerLevel;
	}
protected:
	Map* map;
	int playerLevel; // Keeps track of the level of the player
};