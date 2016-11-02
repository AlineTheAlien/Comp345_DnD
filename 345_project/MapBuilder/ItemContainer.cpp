//! @file 
//! @brief Implementation file for the ItemContainer class  
//!

#include "ItemContainer.h"
#include <iostream>

using namespace std;

//! Default constructor
ItemContainer::ItemContainer()
{
	type = "CHEST";
	objectType = 'C';
	items = vector<Item>();
}

//! Constructor that takes a vector of items
//! @param type : String representing the type of item
//! @param items : Vector of items
ItemContainer::ItemContainer(string type, vector<Item> items)
{
	if (type == "BACKPACK" || type == "EQUIPPED" || type == "CHEST")
	{
		this->type = type;
		this->items = items;
		this->objectType = 'C';
	}
	else
	{
		cout << "Invalid container type." << endl;
		exit(1);
	}
}

//! Constructor
//! @param type : String representing the type of item
ItemContainer::ItemContainer(string type)
{
	if (type == "BACKPACK" || type == "EQUIPPED" || type == "CHEST")
	{
		this->type = type;
		this->objectType = 'C';
		items = vector<Item>();
	}
	else
	{
		cout << "Invalid container type." << endl;
		exit(1);
	}
}

//! Method to get the container type
//! @return Type of item container
string ItemContainer::getType()
{
	return type;
}

//! Method to add an item to the item container
//! @param item : Item type
void ItemContainer::addItem(Item item)
{
	items.push_back(item);
}

//! Method to display all items inside the container with a list of enhancements and bonus values
void ItemContainer::displayContainer()
{
	cout << "---------------------------" << endl;
	cout << "Container " << type << endl;
	cout << "---------------------------" << endl;
	if (items.size() == 0)
		cout << "Empty.\n" << endl;

	for (unsigned int i = 0; i < items.size(); i++)
	{
		cout << "Item: \t" << items[i].getType() << endl;
		items[i].displayEnhancements();
		cout << endl;
	}
}
