//! @file 
//! @brief Header file for the MapObject class  
//!
//! This class was created in order to store different types of objects in the same map.
//! Classes that inherit from this includes Character and ItemContainer. This class can also be used
//! to instantiate other objects such as a door and a wall.
#ifndef MAPOBJECT_H
#define MAPOBJECT_H

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

//! Class for the implementation of a superclass which consists of all objects that can be added onto the map
class MapObject {
public:
	MapObject();
	MapObject(char type);
	virtual ~MapObject() {}
	char getObjectType();
	void setObjectType(char type);
	void setMapPosition(int, int);
	int getMapX();
	int getMapY();
private:
	//! Serialization
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & objectType;
		ar & mapX;
		ar & mapY;
	}
protected:
	char objectType;
	int mapX;
	int mapY;
};
#endif