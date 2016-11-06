//! @file 
//! @brief Implementation file for the Boots class  
//!

#include "stdafx.h"
#include "Boots.h"

using namespace std;

//! Default constructor
Boots::Boots()
{
	type = "BOOTS";
	name = "Boots";
	enhancements = vector<Enhancement>();
}

//! Constructor that calls an Item constructor
//! @param name : Name of the boots item
//! @param armorClassBonus : Integer representing the enhancement bonus for the stats Armor Class
//! @param dexterityBonus : Integer representing the enhancement bonus for the stats Dexterity
Boots::Boots(string name, int armorClassBonus, int dexterityBonus) : Item("BOOTS", name, vector<Enhancement>())
{
	this->name = name;

	if (armorClassBonus > 0)
	{
		Enhancement armorClass = Enhancement("ARMOR CLASS", armorClassBonus);
		this->addEnhancement(armorClass);
	}

	if (dexterityBonus > 0)
	{
		Enhancement dexterity = Enhancement("DEXTERITY", dexterityBonus);
		this->addEnhancement(dexterity);
	}
}

//! Constructor taking a vector of enhancements as parameter
//! @param name : Name of the boots item
//! @param enhancements : Vector of enhancements
Boots::Boots(string name, vector<Enhancement> enhancements) : Item("BOOTS", name, enhancements)
{
	this->name = name;
	this->enhancements = enhancements;
}

//! Overrided method to validate that the armor only enhances 'ARMOR CLASS' and 'DEXTERITY' and verify that the bonus values are within [1..5]
//! @return True if the enhancement list is valid according to the rules, false if not
bool Boots::validateItem() {

	bool verify;

	if (enhancements.size() < 1 || enhancements.size() > 2)
		return false;

	for (unsigned int i = 0; i < enhancements.size(); i++)
	{
		if ((enhancements[i].getType() == "ARMOR CLASS" || enhancements[i].getType() == "DEXTERITY") && (enhancements[i].getBonus() >= 1 && enhancements[i].getBonus() <= 5))
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

