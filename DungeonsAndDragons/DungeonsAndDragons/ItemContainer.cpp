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
	setObjectType('C');
	items = vector<Item*>();
}

//! Constructor
//! @param type : String representing the type of item
//! @param items : Vector of items
ItemContainer::ItemContainer(string type, vector<Item*> items)
{
	setObjectType('C');
	if (type == "BACKPACK" || type == "EQUIPPED" || type == "CHEST")
	{
		this->type = type;
		this->items = items;
	}
	else
	{
		cout << "Invalid container type." << endl;
		exit(123);
	}

}

//! Constructor
//! @param type : String representing the type of item
ItemContainer::ItemContainer(string type)
{
	setObjectType('C');
	if (type == "BACKPACK" || type == "EQUIPPED" || type == "CHEST")
	{
		this->type = type;
		items = vector<Item*>();
	}
	else
	{
		cout << "Invalid container type." << endl;
		exit(123);
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
vector<Item*> ItemContainer::getItems()
{
	return items;
}

//! Method to get the position of an item of a specified type
//! @param name: Name of item
//! @return Index of item in the vector
int ItemContainer::getItemPosition(string itemName)
{
	for (unsigned int i = 0; i < items.size(); i++) {
		if (items[i]->getName() == itemName)
			return i;
	}

	return -1;
}

//! Method to get an item of a specific name from the container
//! @param itemName : Name of item to extract from the container
//! @return Item of the specified name provided in input
Item* ItemContainer::getItem(string itemName)
{
	for (unsigned int i = 0; i < items.size(); i++) {
		if (items[i]->getName() == itemName)
			return items[i];
	}
}

//! Method to add an item to the item container
//! @param item : Pointer to an item object
//! @return The index position of the item inside the vector
int ItemContainer::addItem(Item* item)
{
	//cout << "*** Adding " << item->getName() << " to " << type << " ***\n" << endl;
	items.push_back(item);
	int position = items.size() - 1;
	return position;
}

//! Method to remove an item from the container by its name
//! @param itemName : Name of item to be removed from the container
//! @return A pointer to the item
Item* ItemContainer::removeItem(string itemName)
{
	//cout << "*** Removing " << itemName << " from " << type << " ***\n" << endl;
	int pos = getItemPosition(itemName);
	Item* temp = items[pos];
	items.erase(items.begin() + pos);
	return temp;
}

//! Method to remove an item from the container by its index position in the vector
//! @param index : Index position of the item inside the vector
//! @return A pointer to an item object
Item* ItemContainer::removeItem(int index)
{
	vector<Item*> origin = this->getItems();
	//cout << "*** Removing " << origin[index]->getName() << " from " << type << " ***\n" << endl;
	Item* temp = items[index]; //temp points to where items[index] points to
	items.erase(items.begin() + index); //remove the pointer at the specified index from the vector
	return temp; //returns the pointer
}

//! Method to transfer an item between different two containers
//! @param destination : Pointer to the destination container
//! @param index : Index of the item inside the origin container
void ItemContainer::transfer(ItemContainer* destination, int index) {
	vector<Item*> origin = this->getItems();
	cout << "*** Transferring " << origin[index]->getName() << " from " << this->getType() << " to " << destination->getType() << " ***" << endl;
	Item* transferItem = this->removeItem(index); //Remove item
	destination->addItem(transferItem); //Add the removed item into the destination container
}

//! Method to transfer an item between different two containers without displaying output information
//! @param destination : Pointer to the destination container
//! @param index : Index of the item inside the origin container
void ItemContainer::transferNoOutput(ItemContainer* destination, int index) {
	vector<Item*> origin = this->getItems();
	Item* transferItem = this->removeItem(index); //Remove item
	destination->addItem(transferItem); //Add the removed item into the destination container
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
		cout << "[" << i << "]" << "Item: " << items[i]->getName() << endl;
		items[i]->displayEnhancements();
		cout << endl;
	}
}

//! Destructor
ItemContainer::~ItemContainer() {
	for (int i = 0; i < items.size(); i++) {
		delete items[i];
	}
}