//! @file 
//! @brief Implementation file for the Ring class  
//!

#include "stdafx.h"
#include "Ring.h"

using namespace std;

//! Default constructor
Ring::Ring()
{
	type = "RING";
}

//! Constructor that calls an Item constructor
//! @param armorClassBonus : Integer representing the enhancement bonus for the stats Armor Class
//! @param strengthBonus : Integer representing the enhancement bonus for the stats Strength
//! @param constitutionBonus : Integer representing the enhancement bonus for the stats Constitution
//! @param wisdomBonus : Integer representing the enhancement bonus for the stats Wisdom
//! @param charismaBonus : Integer representing the enhancement bonus for the stats Charisma
Ring::Ring(string name, int armorClassBonus, int strengthBonus, int constitutionBonus, int wisdomBonus, int charismaBonus) : Item("RING", name, vector<Enhancement>())
{
	if (armorClassBonus > 0)
	{
		Enhancement armorClass = Enhancement("ARMOR CLASS", armorClassBonus);
		this->addEnhancement(armorClass);
	}

	if (strengthBonus > 0)
	{
		Enhancement strength = Enhancement("STRENGTH", strengthBonus);
		this->addEnhancement(strength);
	}

	if (constitutionBonus > 0)
	{
		Enhancement constitution = Enhancement("CONSTITUTION", constitutionBonus);
		this->addEnhancement(constitution);
	}

	if (wisdomBonus > 0)
	{
		Enhancement wisdom = Enhancement("WISDOM", wisdomBonus);
		this->addEnhancement(wisdom);
	}

	if (charismaBonus > 0)
	{
		Enhancement charisma = Enhancement("CHARISMA", charismaBonus);
		this->addEnhancement(charisma);
	}
}

//! Constructor taking a vector of enhancements as parameter
//! It also calls an Item constructor and pass a vector of enhancements as parameter.
//! @param enhancements : Vector of enhancements
Ring::Ring(string name, vector<Enhancement> enhancements) : Item("RING", name, enhancements)
{
	this->enhancements = enhancements;
}

//! Overrided method to validate that the armor only enhances 'ARMOR CLASS', 'STRENGTH', 'CONSTITUTION',
//! 'WISDOM' and 'CHARISMA' and verify that the bonus values are within [1..5]
//! @return True if the enhancement list is valid according to the rules, false if not
bool Ring::validateItem() {

	bool verify;

	if (enhancements.size() < 1 || enhancements.size() > 5)
		return false;

	for (unsigned int i = 0; i < enhancements.size(); i++)
	{
		if ((enhancements[i].getType() == "ARMOR CLASS" || enhancements[i].getType() == "STRENGTH" || enhancements[i].getType() == "CONSTITUTION"
			|| enhancements[i].getType() == "WISDOM" || enhancements[i].getType() == "CHARISMA") && (enhancements[i].getBonus() >= 1 && enhancements[i].getBonus() <= 5))
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

