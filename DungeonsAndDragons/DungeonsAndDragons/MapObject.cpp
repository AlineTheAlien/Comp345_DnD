//! @file 
//! @brief Implementation file for the MapObject class  
//!

#include "stdafx.h"
#include "MapObject.h"

//! Default constructor
MapObject::MapObject() {
}

//! Constructor
//! @param type : Type of the object on the map as a char value
MapObject::MapObject(char type) {
	this->objectType = type;
}

//! set the type of an object
//! @param type : Type of the object on the map as a char value
void MapObject::setObjectType(char type)
{
	objectType = type;
}


//! Method to obtain the type of the map object
//! @return A map object type as a char value
char MapObject::getObjectType() {
	return this->objectType;
}

//! Mutator method to set position of character
//! @param x : Position x of character on a map
//! @param y : Position y of character on a map
void MapObject::setMapPosition(int x, int y) {
	mapX = x;
	mapY = y;
}

//! Accessor method to get X position of the character on a map
//! @return an integer representing the X position
int MapObject::getMapX() {
	return mapX;
}

//! Accessor method to get X position of the character on a map
//! @return an integer representing the Y position
int MapObject::getMapY() {
	return mapY;
}