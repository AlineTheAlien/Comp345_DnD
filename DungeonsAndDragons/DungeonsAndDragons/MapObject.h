//! @file 
//! @brief Header file for the MapObject class  
//!
//! This class was created in order to store different types of objects in the same map.
//! Classes that inherit from this includes Character and ItemContainer. This class can also be used
//! to instantiate other objects such as a door and a wall.
#ifndef MAPOBJECT_H
#define MAPOBJECT_H
// include headers that implement a archive in simple text format
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
//! Class for the implementation of a superclass which consists of all objects that can be added onto the map
class MapObject {
public:
	MapObject();
	MapObject(char type);
	char getObjectType();
	// Serialization
	// When the class Archive corresponds to an output archive, the
	// & operator is defined similar to <<. Likewise, when the class Archive
	// is a type of input archive the & operator is defined similar to >>.
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & objectType;
	}
protected:
	char objectType;
};
#endif