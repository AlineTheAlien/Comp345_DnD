/**
* @file
* @brief Header file for the Item class
*
* 1) Game rules:
* - An item can only be of type 'HELMET', 'ARMOR', 'SHIELD', 'RING', 'BELT', 'BOOTS' and 'WEAPON'.
* - An item can enhance only a certain combination of character statistics as described in the instruction.
* - The player should be able to view information about each item, such as the type and the enhancements with their respective values.
* - The enhancements should be obtainable in order to apply it onto the character's statistics.

* 2) Design:
* - The Item class is a superclass of Helmet, Armor, Shield, Ring, Belt, Boots and Weapon classes.
* - Since different types of items only provide a certain combinations of valid enhancement types, it would be more efficient to implement each subclass
* with different constructors that allow easier initialization of the enhancement types. Validating an item can also be done easily by checking
* the list of stats that the item enhances against the valid enhancements that each item type can have.

* 3) Libraries:
* - A STL container (vector) was used to contain all the enhancement objects. This allows easier manipulation of the enhancements, such as adding
* an enhancement to the vector.
* - String was included to use string data types
* - In the .cpp file, iostream was included to output strings to the stream. Enhancements and their bonus can be easily displayed to the stream.
*/


#ifndef ITEM_H
#define ITEM_H

#include "Enhancement.h"
#include <string>
#include <vector>

using namespace std;

//! Class for the implementation of items wearable by a character
class Item
{
public:
	Item();
	Item(string type, string name, vector<Enhancement> enhancements);
	string getType();
	string getName();
	vector<Enhancement> getEnhancements();
	void addEnhancement(Enhancement e);
	void displayEnhancements();
	bool validateItem();
protected:
	string type;
	string name;
	vector<Enhancement> enhancements;
};

#endif