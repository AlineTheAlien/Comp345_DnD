//! @file 
//! @brief Header file for the Item class  
//!
//! This is a simplified version of the Item class implemented in assignment 1. For the purpose of this assignment, the enhancements of
//! each item are set as the item's attributes. Only 'RING', 'BOOTS' and 'WEAPON' are used.
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
	Item(string type, int ac, int str, int consti, int wisd, int chari);
	Item(string type, int ac, int dext);
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