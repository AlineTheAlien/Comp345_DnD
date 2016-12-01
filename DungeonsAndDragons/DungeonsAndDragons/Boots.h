//! @file
//! @brief Header file for the Boots class
//!

//! This class represents a specific Item type. It is a subclass of Item.
#ifndef BOOTS_H
#define BOOTS_H

#include "Item.h"

using namespace std;

//! Class for the implementation of a boot
class Boots : public Item
{
public:
	// Default constructor
	Boots();
	// Constructor
	Boots(string name, int armorClass, int dexterity);
	// Constructor taking a vector of enhancements as parameter
	Boots(string name, vector<Enhancement> enhancements);
	// Overrided method to validate that the armor only enhances 'ARMOR CLASS' and 'DEXTERITY' and verify that the bonus values are within [1..5]
	bool validateItem();

private:
	// Serialization
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Item>(*this);
		ar & type;
		ar & name;
		ar & enhancements;
	}
};

#endif