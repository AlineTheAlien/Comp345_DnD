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

// include headers that implement a archive in simple text format
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
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
	vector<Item*> items;
	char objectType;

public:
	ItemContainer();
	~ItemContainer();
	ItemContainer(string, vector<Item*>);
	ItemContainer(string);
	string getType();
	vector<Item*> getItems();
	int getItemPosition(string);
	Item* getItem(string);
	int addItem(Item*);
	Item* removeItem(string itemName); // remove item by name
	Item* removeItem(int index); // remove item by index
	void transfer(ItemContainer*, int);
	void displayItems();


private:
	//! Serialization
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<MapObject>(*this);
		ar & type;
		ar & items;
		ar & objectType;
	}
};

#endif