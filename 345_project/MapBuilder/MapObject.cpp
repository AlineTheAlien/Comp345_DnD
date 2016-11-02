//! @file 
//! @brief Implementation file for the MapObject class  
//!
#include "MapObject.h"

MapObject::MapObject() {
	this->objectType = ' ';
}

//! Constructor
//! @param type : Type of the object on the map as a char value
MapObject::MapObject(char type) {
	this->objectType = type;
}

//! Method to obtain the type of the map object
//! @return A map object type as a char value
char MapObject::getObjectType() {
	return this->objectType;
}