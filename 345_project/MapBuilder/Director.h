//! @file 
//! @brief Header file for the Director class  
//!
//! The Director class is used to direct map construction. A ConcreteMapBuilder can be chosen and set,
//! allowing the map to be constructed differently. It will either load the map as saved (via ConcreteBuilderA)
//! or load the map adapted to the player's level (via ConcreteBuilderB). It is also able to get the
//! final Map product after it has been successfully constructed. Upon constructing the map, this class will read
//! the map file directly and calls methods from concrete map builders to build each parts (wall, door, player, enemy, container)
//! It redirects chest and enemy files to the right methods of the concrete map builder to build each of these parts
//! separately. Only standard libraries were used, with ifstream for reading files.
#ifndef DIRECTOR_H
#define DIRECTOR_H

#include "MapBuilder.h"
#include "Map.h"

//! Class for the implementation of a director, which is used direct construction a map using the Builder Design Pattern
class Director
{
public:
	void constructMap(string,int);
	void setMapBuilder(MapBuilder*);
	Map* getMap();
private:
	MapBuilder* mbuilder;
};

#endif