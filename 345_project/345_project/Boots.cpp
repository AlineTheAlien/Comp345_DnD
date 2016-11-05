//! @file 
//! @brief Implementation file for the Boots class  
//!

#include "Boots.h"

using namespace std;

//! Default constructor
Boots::Boots()
{
	type = "BOOTS";
}

//! Constructor that calls an Item constructor
//! @param armorClassBonus : Integer representing the enhancement bonus for the stats Armor Class
//! @param dexterityBonus : Integer representing the enhancement bonus for the stats Dexterity
Boots::Boots(int armorClassBonus, int dexterityBonus) : Item("BOOTS", vector<Enhancement>())
{
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
//! It also calls an Item constructor and pass a vector of enhancements as parameter.
//! @param enhancements : Vector of enhancements
Boots::Boots(vector<Enhancement> enhancements) : Item("BOOTS", enhancements)
{
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

