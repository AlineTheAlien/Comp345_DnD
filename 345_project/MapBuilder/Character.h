//! @file 
//! @brief Header file for the Character class  
//!
//! This is a simplified class for a character, used to create a player or an enemy object.
//! Either of these characters should have a level, ability scores, current hit points and
//! total hit point. There should be a method to obtain the level of the characters as it will
//! be used to adapt a map to a player's level. It also inherits from 'MapObject', allowing it
//! to be placed in a map of pointers to 'MapObject' objects.
#ifndef CHARACTER_H
#define CHARACTER_H

#include "MapObject.h"
#include "Map.h"

//! Class for the implementation of a character
class Character : public MapObject
{
public:
	Character();
	Character(char type, int level, int current, int total, int str, int dex, int con, int intel, int wis, int cha);
	void setcurrentHP(int hp);
	void settotalHP(int hp);
	void displayCharacter();
	int getLevel();
private:
	int abilityScores[6];
	int currentHitPoints;
	int totalHitPoints;
	int level;
};
#endif