//! @file 
//! @brief Implementation file for the ItemContainer class  
//!

#include "stdafx.h"
#include "ItemContainer.h"
#include <iostream>

using namespace std;

//! Default constructor
ItemContainer::ItemContainer()
{
	type = "UNNAMED CONTAINER";
	items = vector<Item>();
}

//! Constructor that takes a vector of items
//! @param type : String representing the type of item
//! @param items : Vector of items
ItemContainer::ItemContainer(string type, vector<Item> items)
{
	if (type == "BACKPACK" || type == "EQUIPPED" || type == "TREASURE CHEST")
	{
		this->type = type;
		this->items = items;
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
	if (type == "BACKPACK" || type == "EQUIPPED" || type == "TREASURE CHEST")
	{
		this->type = type;
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

//! Method to get items from the container
//! @return Vector containing a list of items inside the container
vector<Item> ItemContainer::getItems()
{
	return items;
}

//! Method to get the position of an item of a specified type
//! @param itemType : Type of item
//! @return Index of item in the vector
int ItemContainer::getItemPosition(string itemType)
{
	for (unsigned int i = 0; i < items.size(); i++) {
		if (items[i].getType() == itemType)
			return i;
	}

	return -1;
}

//! Method to get an item of a specific type from the container
//! Assumption: Each container may only contain one element of a type
//! @param itemType : Type of item to extract from the container
//! @return Item of the specified kind provided in input
Item ItemContainer::getItem(string itemType)
{
	for (unsigned int i = 0; i < items.size(); i++) {
		if (items[i].getType() == itemType)
			return items[i];
	}
}

//! Method to add an item to the item container
//! @param item : Item type
void ItemContainer::addItem(Item item)
{
	cout << "***Adding " << item.getType() << " to " << type << "***\n" << endl;
	items.push_back(item);
	cout << "After adding the item, here is the content of the container: " << endl;
	this->displayItems();
}

//! Method to remove an item from the container
//! @param itemType : Type of item to be removed
//! @return Item removed
Item ItemContainer::removeItem(string itemType)
{
	cout << "***Removing " << itemType << " from " << type << "***\n" << endl;
	int pos = getItemPosition(itemType);
	Item temp = items[pos];
	items.erase(items.begin() + pos);
	cout << "After removing the item, here is the content of the container: " << endl;
	this->displayItems();
	return temp;
}

//! Method to display all items inside the container with a list of enhancements and bonus values
void ItemContainer::displayItems()
{
	cout << "---------------------------" << endl;
	cout << "Items in " << type << endl;
	cout << "---------------------------" << endl;
	if (items.size() == 0)
		cout << "Empty.\n" << endl;

	for (unsigned int i = 0; i < items.size(); i++)
	{
		cout << "Type: \t" << items[i].getType() << endl;
		items[i].displayEnhancements();
		cout << endl;
	}
}
