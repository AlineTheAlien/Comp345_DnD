//! @file 
//! @brief Implementation file for the Helmet class  
//!

#include "stdafx.h"
#include "Helmet.h"

using namespace std;

//! Default constructor
Helmet::Helmet()
{
	type = "HELMET";
}

//! Constructor that calls an Item constructor
//! @param intelligenceBonus : Integer representing the enhancement bonus for the stats Intelligence
//! @param wisdomBonus : Integer representing the enhancement bonus for the stats Wisdom
//! @param armorClassBonus : Integer representing the enhancement bonus for the stats Armor Class
Helmet::Helmet(int intelligenceBonus, int wisdomBonus, int armorClassBonus) : Item("HELMET", vector<Enhancement>())
{
	if (intelligenceBonus > 0)
	{
		Enhancement intelligence = Enhancement("INTELLIGENCE", intelligenceBonus);
		this->addEnhancement(intelligence);
	}

	if (wisdomBonus > 0)
	{
		Enhancement wisdom = Enhancement("WISDOM", wisdomBonus);
		this->addEnhancement(wisdom);
	}

	if (armorClassBonus > 0)
	{
		Enhancement armorClass = Enhancement("ARMOR CLASS", armorClassBonus);
		this->addEnhancement(armorClass);
	}
}

//! Constructor taking a vector of enhancements as parameter
//! It also calls an Item constructor and pass a vector of enhancements as parameter.
//! @param enhancements : Vector of enhancements
Helmet::Helmet(vector<Enhancement> enhancements) : Item("HELMET", enhancements)
{
}

//! Overrided method to validate that the armor only enhances 'ARMOR CLASS', 'WISDOM' and 'INTELLIGENCE' and verify that the bonus values are within [1..5]
//! @return True if the enhancement list is valid according to the rules, false if not
bool Helmet::validateItem() {

	bool verify;

	if (enhancements.size() < 1 || enhancements.size() > 3)
		return false;

	for (unsigned int i = 0; i < enhancements.size(); i++)
	{
		if ((enhancements[i].getType() == "INTELLIGENCE" || enhancements[i].getType() == "WISDOM" || enhancements[i].getType() == "ARMOR CLASS") && (enhancements[i].getBonus() >= 1 && enhancements[i].getBonus() <= 5))
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
