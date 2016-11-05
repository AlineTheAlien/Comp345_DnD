//! @file 
//! @brief Implementation file for the Weapon class  
//!
#include "stdafx.h"
#include "Weapon.h"

using namespace std;

//! Default constructor
Weapon::Weapon()
{
	type = "WEAPON";
}

//! Constructor that calls an Item constructor
//! @param attackValue : Integer representing the enhancement bonus for the stats Attack bonus
//! @param damageValue : Integer representing the enhancement bonus for the stats Damage bonus
Weapon::Weapon(string name, int attackValue, int damageValue) : Item("WEAPON", name, vector<Enhancement>())
{
	if (attackValue > 0)
	{
		Enhancement attackBonus = Enhancement("ATTACK BONUS", attackValue);
		this->addEnhancement(attackBonus);
	}

	if (damageValue > 0)
	{
		Enhancement damageBonus = Enhancement("DAMAGE BONUS", damageValue);
		this->addEnhancement(damageBonus);
	}

}

//! Constructor taking a vector of enhancements as parameter
//! It also calls an Item constructor and pass a vector of enhancements as parameter.
//! @param enhancements : Vector of enhancements
Weapon::Weapon(string name, vector<Enhancement> enhancements) : Item("WEAPON", name, enhancements)
{
}

//! Overrided method to validate that the armor only enhances 'ATTACK BONUS' and 'DAMAGE BONUS'and verify that the bonus values are within [1..5]
//! @return True if the enhancement list is valid according to the rules, false if not
bool Weapon::validateItem() {

	bool verify;

	if (enhancements.size() < 1 || enhancements.size() > 2)
		return false;

	for (unsigned int i = 0; i < enhancements.size(); i++)
	{
		if ((enhancements[i].getType() == "ATTACK BONUS" || enhancements[i].getType() == "DAMAGE BONUS") && (enhancements[i].getBonus() >= 1 && enhancements[i].getBonus() <= 5))
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