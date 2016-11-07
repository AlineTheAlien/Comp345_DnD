//! @file 
//! @brief Header file for the Campaign
//! The following class implements the campaign class according to the requirements.
//! A vector of strings was used to identify the maps linked in the campaign
//! The vector allows to load maps in order according to their specified path
//! Vectors are dynamic and allow to add elements to it without knowning its size previously
//! The library used to serialization of class is Boost.Serialization
//! It was used because of its efficiency and portability. With Boost, it is possible
//! to serialize and export a class into a binary data file

#pragma once
#include "Map.h"
#include <boost/serialization/serialization.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>

using namespace std;

class Campaign
{
private:
	//!Name of the campaign
	string campaignName;
	//!List of the name of the maps in the campaign
	vector<string> mapPathList;

	//!Boost serialization
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		//Attributes to serialize
		ar & campaignName;
		ar & mapPathList;
	}
public:
	Campaign();
	void addMap(string mapName);
	void removeMap();
	string getName();
	void setName(string name);
	int getMapListSize();
	string getMap(int index);
	~Campaign();
};

