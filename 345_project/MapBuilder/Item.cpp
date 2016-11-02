//! @file 
//! @brief Implementation file for the Item class  
//!
//! For the purpose of the assignment, only three types of items are considered: 'RING', 'BOOTS', 'WEAPON'.

#include "Item.h"
#include <iostream>

using namespace std;

//! Default constructor
Item::Item()
{
	type = "RING";
	armorClass = 0;
	strength = 0;
	constitution = 0;
	wisdom = 0;
	charisma = 0;
}

//! Constructor to create a 'RING' item
//! @param type : String representing the type of item
//! @param ac : Enhancement bonus for Armor Class as an integer value
//! @param str : Enhancement bonus for Strength as an integer value
//! @param consti : Enhancement bonus for Constitution as an integer value
//! @param wisd : Enhancement bonus for Wisdom as an integer value
//! @param chari : Enhancement bonus for Charisma as an integer value
Item::Item(string type, int ac, int str, int consti, int wisd, int chari)
{
	if (type == "RING")
	{
		this->type = type;
		armorClass = ac;
		strength = str;
		constitution = consti;
		wisdom = wisd;
		charisma = chari;
	}
}

//! Constructor to create either a 'BOOTS' or 'WEAPON' item
//! @param a : Enhancement bonus for either Armor Class or Attack Bonus as an integer value
//! @param b : Enhancement bonus for either Dexterity or Damange Bonus as an integer value
Item::Item(string type, int a, int b)
{
	if (type == "BOOTS")
	{
		this->type = type;
		armorClass = a;
		dexterity = b;
	}
	if (type == "WEAPON")
	{
		this->type = type;
		attackBonus = a;
		damageBonus = b;
	}
}
//! Method to get the type of the item
//! @return Type of the item
string Item::getType()
{
	return type;
}

//! Method to display all the enhancements in the vector along with their respective bonus values
void Item::displayEnhancements()
{
	if (type == "RING") {
		cout << "Enhancements: " << endl;
		if (armorClass != 0)
			cout << "\tArmor Class: +" << armorClass << endl;
		if (strength != 0)
			cout << "\tStrength +" << strength << endl;
		if (constitution != 0)
			cout << "\tConstitution +" << constitution << endl;
		if (wisdom != 0)
			cout << "\tWisdom +" << wisdom << endl;
		if (charisma != 0)
			cout << "\tCharisma +" << charisma << endl;
	}
	else if (type == "BOOTS") {
		cout << "Enhancements: " << endl;
		if (armorClass != 0)
			cout << "\tArmor Class: +" << armorClass << endl;
		if (dexterity != 0)
			cout << "\tDexterity +" << dexterity << endl;
	}
	else if (type == "WEAPON") {
		cout << "Enhancements: " << endl;
		if (attackBonus != 0)
			cout << "\tAttack Bonus: +" << attackBonus << endl;
		if (damageBonus != 0)
			cout << "\tDamageBonus +" << damageBonus << endl;
	}
}
