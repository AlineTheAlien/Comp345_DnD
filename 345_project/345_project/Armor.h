//! @file
//! \brief Header file for the Armor class
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
	Armor(int armorClass);
	// Constructor taking a vector of enhancements as parameter
	Armor(vector<Enhancement> enhancements);
	// Overrided method to validate that the armor only enhances 'ARMOR CLASS' and verify that the bonus values are within [1..5]
	bool validateItem();
};

#endif