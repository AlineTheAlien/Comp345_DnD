//! @file 
//! @brief Header file for the MapObject class  
//!
//! This class was created in order to store different types of objects in the same map.
//! Classes that inherit from this includes Character and ItemContainer. This class can also be used
//! to instantiate other objects such as a door and a wall.
#ifndef MAPOBJECT_H
#define MAPOBJECT_H

//! Class for the implementation of a superclass which consists of all objects that can be added onto the map
class MapObject {
public:
	MapObject();
	MapObject(char type);
	char getObjectType();
protected:
	char objectType;
};
#endif