/** 
* @file 
* @brief Header file for the ItemContainer class  
*
* 1) Game rules:
*	- Item container can be either a 'BACKPACK', 'EQUIPPED' or 'TREASURE CHEST'.
*	- A container can contain any number of items.
*	- A player should be able to obtain items from a container, as well as getting information about them, such as the type.
*	- Items should be transferable between containers (e.g. from treasure chest into backpack, from backpack into equipped),
*	therefore they should be removable.

* 2) Design:
*	- The container class has three different constructors, making it easier to create a container in different ways.
*	For example, if there is an existing list of items, it can be passed as parameter to a constructor and used to initialize
*	the vector of items of the container. It is also possible to create an empty container, which has its own empty vector of
*	items. Items can then be added into the container one by one.

* 3) Libraries:
*	- A STL container (vector) was used to contain all the item objects. This allows easier manipulation of the items, such as
*	adding and removing as many items as we want.
*	- String was included to use string data types
*	- In the .cpp file, iostream was included to output strings to the stream. Enhancements and their bonus can be easily displayed to the stream.
**/
#ifndef ITEMCONTAINER_H
#define ITEMCONTAINER_H

#include "Item.h"
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
	// Method to get items from the container
	vector<Item> getItems();
	// Method to get the position of an item of a specified type
	int getItemPosition(string itemType);
	// Method to get an item of a specific type, assuming that each container may only contain one element of a type
	Item getItem(string itemType);
	// Method to add an item to the item container
	void addItem(Item item);
	// Method to remove an item from the container
	Item removeItem(string itemType);
	// Method to display all items inside the container with a list of enhancements and bonus values
	void displayItems();
};

#endif