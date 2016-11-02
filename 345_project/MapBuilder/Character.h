//! @file 
//! @brief Header file for the Character class  
//!
#ifndef CHARACTER_H
#define CHARACTER_H

#include "MapObject.h"
#include "Map.h"

//! Class that implements a character
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