//! @file 
//! @brief Header file for the ItemContainer class  
//!
#ifndef ITEMCONTAINER_H
#define ITEMCONTAINER_H

#include "Item.h"
#include "MapObject.h"
#include <string>
#include <vector>

using namespace std;

//! Class that implements an item container
class ItemContainer : public MapObject
{
private:
	string type;
	vector<Item> items;
public:
	// Default constructor
	ItemContainer();
	// Constructor that takes a vector of items
	ItemContainer(string type, vector<Item> items);
	// Constructor
	ItemContainer(string type);
	// Method to get the container type
	string getType();
	// Method to add an item to the item container
	void addItem(Item item);
	// Method to display all items inside the container with a list of enhancements and bonus values
	void displayContainer();
};

#endif