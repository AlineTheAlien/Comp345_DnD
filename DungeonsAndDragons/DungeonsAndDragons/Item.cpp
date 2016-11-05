//! @file 
//! @brief Implementation file for the Item class  
//!

#include "stdafx.h"
#include "Item.h"
#include <iostream>

using namespace std;

//! Default constructor
Item::Item()
{
	enhancements = vector<Enhancement>();
	type = "UNKNOWN ITEM";
}

//! Constructor that receives an item type as a string and a vector containing the enhancements
//! @param type : String representing the type of item
//! @param enhancements : Vector containing all the enhancements
Item::Item(string type, vector<Enhancement> enhancements)
{
	if (type == "HELMET" || type == "ARMOR" || type == "SHIELD" || type == "RING" || type == "BELT" ||
		type == "BOOTS" || type == "WEAPON")
	{
		this->type = type;
		this->enhancements = enhancements;
	}
	else
	{
		cout << "Item created is invalid." << endl;
		cout << "(For demo purpose, no error occurs when instantiating an invalid item)" << endl;
	}
}

//! Method to get the type of the item
//! @return Type of the item
string Item::getType()
{
	return type;
}

//! Method to get the enhancements of the item
//! @return Vector containing a list of stats that the item enhances
vector<Enhancement> Item::getEnhancements()
{
	return enhancements;
}

//! Method to add an enhancement to the vector enhancements
//! @param e : Enhancement object
void Item::addEnhancement(Enhancement e)
{
	enhancements.push_back(e);
}

//! Method to display all the enhancements in the vector along with their respective bonus values
void Item::displayEnhancements()
{
	if (enhancements.size() == 0)
		cout << "Enhancements:\tNo enhancements." << endl;
	else {
		cout << "Enhancements:" << endl;
		for (unsigned int i = 0; i < enhancements.size(); i++)
		{
			cout << "\t" << enhancements[i].getType() << " + " << enhancements[i].getBonus() << endl;
		}
	}
}

//! Method to validate an item, e.g. verify that an item of a certain type only enhances a character statistic valid for this item type
//! This method is overridden in the implementation of the subclasses for checking against
//! the specific types of valid enhancement types. In the base class, it will only check that
//! the bonus values are within [1..5].
//! @return True if the enhancement list is valid according to the rules, false if not
bool Item::validateItem() {
	bool verify = false;
	for (unsigned int i = 0; i < enhancements.size(); i++)
	{
		if (enhancements[i].getBonus() >= 1 && enhancements[i].getBonus() <= 5)
			verify = true;
		else
		{
			verify = false;
			break;
		}
	}
	return verify;
}
