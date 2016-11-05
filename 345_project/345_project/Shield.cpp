//! @file 
//! @brief Implementation file for the Shield class  
//!

#include "Shield.h"

using namespace std;

//! Default constructor
Shield::Shield()
{
	type = "SHIELD";
}

//! Constructor that calls an Item constructor
//! @param armorClassBonus : Integer representing the enhancement bonus for the stats Armor Class
Shield::Shield(int armorClassBonus) : Item("SHIELD", vector<Enhancement>())
{
	if (armorClassBonus > 0)
	{
		Enhancement armorClass = Enhancement("ARMOR CLASS", armorClassBonus);
		this->addEnhancement(armorClass);
	}
}

//! Constructor taking a vector of enhancements as parameter
//! It also calls an Item constructor and pass a vector of enhancements as parameter.
//! @param enhancements : Vector of enhancements
Shield::Shield(vector<Enhancement> enhancements) : Item("SHIELD", enhancements)
{
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


