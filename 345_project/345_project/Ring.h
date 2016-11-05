//! @file
//! @brief Header file for the Ring class
//!

//! This class represents a specific Item type. It is a subclass of Item.
#ifndef RING_H
#define RING_H

#include "Item.h"

using namespace std;

//! Class for the implementation of a ring
class Ring : public Item
{
public:
	// Default constructor
	Ring();
	// Constructor
	Ring(int armorClass, int strength, int constitution, int wisdom, int charisma);
	// Constructor taking a vector of enhancements as parameter
	Ring(vector<Enhancement> enhancements);
	// Overrided method to validate that the armor only enhances 'ARMOR CLASS', 'STRENGTH', 'CONSTITUTION',
	// 'WISDOM' and 'CHARISMA' and verify that the bonus values are within [1..5]
	bool validateItem();
};

#endif