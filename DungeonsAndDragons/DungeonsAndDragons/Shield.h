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
	Shield(int armorClass);
	// Constructor taking a vector of enhancements as parameter
	Shield(vector<Enhancement> enhancements);
	// Overrided method to validate that the armor only enhances 'ARMOR CLASS' and verify that the bonus values are within [1..5]
	bool validateItem();
};

#endif