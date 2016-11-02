//! @file 
//! @brief Header file for the MapObject class  
//!
#ifndef MAPOBJECT_H
#define MAPOBJECT_H

//! Implementation of a superclass which consists of all objects that can be added onto the map
class MapObject {
public:
	MapObject();
	MapObject(char type);
	char getObjectType();
protected:
	char objectType;
};
#endif