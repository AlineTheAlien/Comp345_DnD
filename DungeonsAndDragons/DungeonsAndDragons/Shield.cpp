//! @file 
//! @brief Implementation file for the Shield class  
//!

#include "stdafx.h"
#include "Shield.h"


using namespace std;

//! Default constructor
Shield::Shield()
{
	type = "SHIELD";
	name = "Shield";
}

//! Constructor that calls an Item constructor
//! @param name : Name of shield item
//! @param armorClassBonus : Integer representing the enhancement bonus for the stats Armor Class
Shield::Shield(string name, int armorClassBonus) : Item("SHIELD", name, vector<Enhancement>())
{
	this->name = name;
	if (armorClassBonus > 0)
	{
		Enhancement armorClass = Enhancement("ARMOR CLASS", armorClassBonus);
		this->addEnhancement(armorClass);
	}
}

//! Constructor taking a vector of enhancements as parameter
//! @param name : Name of shield item
//! @param enhancements : Vector of enhancements
Shield::Shield(string name, vector<Enhancement> enhancements) : Item("SHIELD", name, enhancements)
{
	this->name = name;
	this->enhancements = enhancements;
}

//! Overrided method to validate that the armor only enhances 'ARMOR CLASS' and verify that the bonus values are within [1..5]
//! @return True if the enhancement list is valid according to the rules, false if not
bool Shield::validateItem() {

	bool verify;

	if (enhancements.size() != 1)
		return false;

	for (unsigned int i = 0; i < enhancements.size(); i++)
	{
		if ((enhancements[i].getType() == "ARMOR CLASS") && (enhancements[i].getBonus() >= 1 && enhancements[i].getBonus() <= 5))
		{
			verify = true;
		}
		else
		{
			verify = false;
			break;
		}
	}

	return verify;
}


