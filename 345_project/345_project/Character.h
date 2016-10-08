//! @file 
//! @brief Header file for the Character class  
//!

#pragma once

//! Class that implements a character 
class Character
{
public:
	Character();
	Character(int, int, int, int, int, int);
	bool validateNewCharacter();
	void hit(int);
	int getHitPoints();
	int rollSixSidedDie();
	int generateAbilityModifier(int);
	void calculateAbilityScores(int[]);
	void displayAbilityScores(Character);
private:
	int abilityScores[6];
	int currentHitPoints;
	int currentLevel;
};
