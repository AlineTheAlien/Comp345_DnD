//! @file 
//! @brief Header file for the MapLoader class  
//!
#ifndef CONCRETEBUILDERB_H
#define CONCRETEBUILDERB_H

#include "MapObject.h"
#include "MapBuilder.h"

//! A ConcreteBuilder class which will generate a map read from the file and adapts to the player's current level
class ConcreteBuilderB : public MapBuilder {
public:
	void buildWall(int, int);
	void buildDoor(int, int);
	void buildEnemy(int, int, string);
	void buildPlayer(int, int);
	void buildContainer(int, int, int, string);
};
#endif