//! @file 
//! @brief Header file for the Item class  
//!

#ifndef ITEM_H
#define ITEM_H

#include <string>

using namespace std;

//! Class for the implementation of items wearable by a character
class Item
{
public:
	// Default constructor
	Item();
	// Constructor that receives an item type as a string
	Item(string type, int ac, int str, int consti, int wisd, int chari);
	// Constructor that receives an item type as a string
	Item(string type, int ac, int dext);
	// Method to get the type of the item
	string getType();
	void displayEnhancements();
protected:
	string type;
	int armorClass;
	int strength;
	int constitution;
	int wisdom;
	int charisma;
	int dexterity;
	int attackBonus;
	int damageBonus;
};

#endif