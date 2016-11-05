//! @file 
//! @brief Header file for the ItemContainer class  
//!
//! This is a simplified version of the ItemContainer class implemented in assignment 1.
//! It inherits from 'MapObject' as it has to be placed in an array of pointers to a MapObject.
#ifndef ITEMCONTAINER_H
#define ITEMCONTAINER_H

#include "Item.h"
#include "MapObject.h"
#include <string>
#include <vector>

using namespace std;

//! Class for the implementation of an item container
class ItemContainer : public MapObject
{
private:
	string type;
	vector<Item> items; // Each container has a list of items
public:
	ItemContainer();
	ItemContainer(string type, vector<Item> items);
	ItemContainer(string type);
	string getType();
	void addItem(Item item);
	void displayContainer();
};

#endif