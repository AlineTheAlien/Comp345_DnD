//! @file
//! @brief Header file for the Belt class
//!

//! This class represents a specific Item type. It is a subclass of Item.
#ifndef BELT_H
#define BELT_H

#include "Item.h"

using namespace std;

//! Class for the implementation of a belt
class Belt : public Item
{
public:
	// Default constructor
	Belt();
	// Constructor
	Belt(string name, int constitution, int strength);
	// Constructor
	Belt(string name, vector<Enhancement> enhancements);
	// Overrided method to validate that the armor only enhances 'CONSTITUTION' and 'STRENGTH' and verify that the bonus values are within [1..5]
	bool validateItem();
};

#endif