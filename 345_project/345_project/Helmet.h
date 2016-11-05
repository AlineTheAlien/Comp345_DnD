//! @file
//! @brief Header file for the Helmet class
//!

//! This class represents a specific Item type. It is a subclass of Item.
#ifndef HELMET_H
#define HELMET_H

#include "Item.h"

using namespace std;

//! Class for the implementation of a helmet
class Helmet : public Item
{
public:
	// Default constructor
	Helmet();
	// Constructor
	Helmet(int intelligence, int wisdom, int armorClass);
	// Constructor
	Helmet(vector<Enhancement> enhancements);
	// Overrided method to validate that the armor only enhances 'ARMOR CLASS', 'WISDOM' and 'INTELLIGENCE' and verify that the bonus values are within [1..5]
	bool validateItem();
};

#endif