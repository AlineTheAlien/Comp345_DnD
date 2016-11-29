//! @file
//! @brief Header file for the Shield class
//!

//! This class represents a specific Item type. It is a subclass of Item.
#ifndef SHIELD_H
#define SHIELD_H

#include "Item.h"

using namespace std;

//! Class for the implementation of a shield
class Shield : public Item
{
public:
	// Default constructor
	Shield();
	// Constructor
	Shield(string name, int armorClass);
	// Constructor taking a vector of enhancements as parameter
	Shield(string name, vector<Enhancement> enhancements);
	// Overrided method to validate that the armor only enhances 'ARMOR CLASS' and verify that the bonus values are within [1..5]
	bool validateItem();

private:
	//! serialization
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