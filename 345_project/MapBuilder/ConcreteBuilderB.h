//! @file 
//! @brief Header file for the ConcreteBuilderB class  
//!
//! This class inherits from MapBuilder.
//! It implements methods to build each part of the map, such as a wall, door, enemy, player and container as read from a file.
//! Only the enemy object is modified prior to object creation. The enemy is adapted to the player's level
//! by adjusting ability points, hit and total points and the level. The container itself has a file for each level (for the purpose
//! of this assignment, only level 3, 5 and 15 are considered). Containers of different levels contain a different number
//! of items with different enhancement bonus depending on the level of the player. The right container level is loaded into
//! the program and set into the map. As for the player, user has to choose which player he/she would like to play with
//! in the beginning of the game. Different players (currently for level 3, 5 and 15) are each stored in different files.
//! The user-chosen player is loaded into the map from the correct file.
//! Parameters usually take the position (x,y) of the object, as to set it on the map upon creation, or a string representing
//! the exact filename of the file to be read from. Only standard libraries were used, with ifstream for reading files.
#ifndef CONCRETEBUILDERB_H
#define CONCRETEBUILDERB_H

#include "MapBuilder.h"

//! Class for the implementation of a concrete builder class which can generate a map read from a file and adapted to the player's level
class ConcreteBuilderB : public MapBuilder {
public:
	void buildWall(int, int);
	void buildDoor(int, int);
	void buildEnemy(int, int, string);
	void buildPlayer(int, int);
	void buildContainer(int, int, int, string);
};
#endif