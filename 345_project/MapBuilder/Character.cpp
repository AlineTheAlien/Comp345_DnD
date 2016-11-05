//! @file 
//! @brief Implementation file for the Character class  
//!

#include "Character.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

//! Default constructor
Character::Character()
{
	level = 1;
	objectType = 'P';
	abilityScores[0] = 12;
	abilityScores[1] = 12;
	abilityScores[2] = 12;
	abilityScores[3] = 12;
	abilityScores[4] = 12;
	abilityScores[5] = 12;

	// and set hit points to 10
	currentHitPoints = 10;
	totalHitPoints = 10;
}

//! Constructor: passes values to each ability score
//! @param type : Type of the character (Player or Enemy) as a char value
//! @param level : Level of the character as an integer value
//! @param current : Current hit points of the character as an integer value
//! @param total : Total hit points of the character as an integer value
//! @param str : Strength ability score as an integer value
//! @param dex : Dexterity ability score as an integer value
//! @param con : Constitution ability score as an integer value
//! @param intel : Intelligence ability score as an integer value
//! @param wis : Wisdom ability score as an integer value
//! @param cha : Charisma ability score  as an integer value
Character::Character(char type, int level, int current, int total, int str, int dex, int con, int intel, int wis, int cha)
{
	objectType = type;
	this->level = level;
	abilityScores[0] = str;
	abilityScores[1] = dex;
	abilityScores[2] = con;
	abilityScores[3] = intel;
	abilityScores[4] = wis;
	abilityScores[5] = cha;

	// and set hit points to 10
	currentHitPoints = current;
	totalHitPoints = total;
}

//! Method to set the current hit points of the character
//! @param hp : Current hit points as an integer value
void Character::setcurrentHP(int hp) {
	currentHitPoints = hp;
}

//! Method to set the total hit points of the character
//! @param hp : Total hit points as an integer value
void Character::settotalHP(int hp) {
	totalHitPoints = hp;
}

//! Method to display characteristics of the character
void Character::displayCharacter() {
	if (this->getObjectType() == 'E') {
		cout << "---------------------------" << endl;
		cout << "Character ENEMY" << endl;
		cout << "---------------------------" << endl;
	}
	if (this->getObjectType() == 'P') {
		cout << "---------------------------" << endl;
		cout << "Character PLAYER" << endl;
		cout << "---------------------------" << endl;
	}
	cout << "Level: " << level << endl;;
	cout << "Ability scores: " << endl;
	cout << "\tStrength: " << abilityScores[0] << endl;
	cout << "\tDexterity: " << abilityScores[1] << endl;
	cout << "\tConstitution: " << abilityScores[2] << endl;
	cout << "\tIntelligence: " << abilityScores[3] << endl;
	cout << "\tWisdom: " << abilityScores[4] << endl;
	cout << "\tCharisma: " << abilityScores[5] << endl;
	cout << "Total Hit Points: \n";
	cout << "\t" << totalHitPoints << endl;;
	cout << "Current Hit Points: \n";
	cout << "\t" << currentHitPoints << endl;;
	cout << endl;
}

//! Method to get the level of the character
//! @return Level of the character
int Character::getLevel() {
	return level;
}