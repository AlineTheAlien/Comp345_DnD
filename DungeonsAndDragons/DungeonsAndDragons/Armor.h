//! @file
//! @brief Header file for the Armor class
//!
//! This class represents a specific Item type. It is a subclass of Item.
#ifndef ARMOR_H
#define ARMOR_H

#include "Item.h"
using namespace std;

//! Class for the implementation of an armor
class Armor : public Item
{
public:
	// Default constructor
	Armor();
	// Constructor
	Armor(string name, int armorClass);
	// Constructor taking a vector of enhancements as parameter
	Armor(string name, vector<Enhancement> enhancements);
	// Overrided method to validate that the armor only enhances 'ARMOR CLASS' and verify that the bonus values are within [1..5]
	bool validateItem();

private:
	// For serialization
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