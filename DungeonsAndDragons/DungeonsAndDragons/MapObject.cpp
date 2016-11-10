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