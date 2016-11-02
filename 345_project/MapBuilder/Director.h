//! @file 
//! @brief Header file for the Director class  
//!
#ifndef DIRECTOR_H
#define DIRECTOR_H

#include "MapBuilder.h"
#include "Map.h"
#include "MapObject.h"

//! Implementation of the 'Director' class, which is used to construct a map using the Builder Design Pattern
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