//! @file 
//! @brief Header file for the ConcreteBuilderA class  
//!
//! This class inherits from MapBuilder.
//! It implements methods to build each part of the map, such as a wall, door, enemy, player and container as read from a file.
//! Parameters usually take the position (x,y) of the object, as to set it on the map upon creation, or a string representing
//! the exact filename of the file to be read from. Only standard libraries were used, with ifstream for reading files.
#ifndef CONCRETEBUILDERA_H
#define CONCRETEBUILDERA_H

#include "MapBuilder.h"

//! Class for the implementation of a concrete builder class which can generate a map as read from a file
class ConcreteBuilderA : public MapBuilder {
public:
	void buildWall(int, int);
	void buildDoor(int, int);
	void buildEnemy(int, int, string);
	void buildPlayer(int, int);
	void buildContainer(int, int, int, string);
};
#endif