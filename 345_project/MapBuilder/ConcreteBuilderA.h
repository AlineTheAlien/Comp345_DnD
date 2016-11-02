//! @file 
//! @brief Header file for the MapLoader class  
//!
#ifndef CONCRETEBUILDERA_H
#define CONCRETEBUILDERA_H

#include "MapObject.h"
#include "MapBuilder.h"

//! A ConcreteBuilder class which will generate a map as read from a file
class ConcreteBuilderA : public MapBuilder {
public:
	void buildWall(int, int);
	void buildDoor(int, int);
	void buildEnemy(int, int, string);
	void buildPlayer(int, int);
	void buildContainer(int, int, int, string);
};
#endif