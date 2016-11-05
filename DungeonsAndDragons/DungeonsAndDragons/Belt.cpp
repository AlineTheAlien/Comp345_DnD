//! @file 
//! @brief Implementation file for the Armor class  
//!

#include "stdafx.h"
#include "Belt.h"

using namespace std;

//! Default constructor
Belt::Belt()
{
	type = "BELT";
}

//! Constructor that calls an Item constructor
//! @param constitutionBonus : Integer representing the enhancement bonus for the stats Constitution
//! @param strengthBonus : Integer representing the enhancement bonus for the stats Strength
Belt::Belt(string name, int constitutionBonus, int strengthBonus) : Item("BELT", name, vector<Enhancement>())
{
	if (constitutionBonus > 0)
	{
		Enhancement constitution = Enhancement("CONSTITUTION", constitutionBonus);
		this->addEnhancement(constitution);
	}

	if (strengthBonus > 0)
	{
		Enhancement strength = Enhancement("STRENGTH", strengthBonus);
		this->addEnhancement(strength);
	}
}

//! Constructor taking a vector of enhancements as parameter
//! It also calls an Item constructor and pass a vector of enhancements as parameter.
//! @param enhancements : Vector of enhancements
Belt::Belt(string name, vector<Enhancement> enhancements) : Item("BELT", name, enhancements)
{
}

//! Overrided method to validate that the armor only enhances 'CONSTITUTION' and 'STRENGTH' and verify that the bonus values are within [1..5]
//! @return True if the enhancement list is valid according to the rules, false if not
bool Belt::validateItem() {

	bool verify;

	if (enhancements.size() < 1 || enhancements.size() > 2)
		return false;

	for (unsigned int i = 0; i < enhancements.size(); i++)
	{
		if ((enhancements[i].getType() == "CONSTITUTION" || enhancements[i].getType() == "STRENGTH") && (enhancements[i].getBonus() >= 1 && enhancements[i].getBonus() <= 5))
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
