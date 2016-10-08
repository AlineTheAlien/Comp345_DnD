//! @file 
//! @brief Implementation file for the Character class  
//!

#include "stdafx.h" 
#include "Character.h"
#include <stdlib.h>
#include <cstdlib>
#include <ctime>


int abilityScores[6];
int currentHitPoints;
int currentLevel = 1;

// default constructor
Character::Character(int str, int dex, int con, int intel, int wis, int cha)
{
	int abilityHolder[6];
	int diceRollHolder[4];

	for (int i = 0; i < 6; i++) {

		for (int j = 0; j < 4; j++) {
			int r = rollSixSidedDie();
			diceRollHolder[j] = r;
		}

		int largest = 0;
		int indexOfLargest;
		int secondLargest = 0;
		int indexOfSecondLargest;
		int thirdLargest = 0;
		int indexOfThirdLargest;
		int totalOfDice;

		for (int k = 0; k < 4; k++)  // find the largest 3 dice
		{
			if (diceRollHolder[k] >= largest)
			{
				largest = diceRollHolder[k];
				indexOfLargest = k;
			}
		}

		for (int l = 0; l < 4; l++)  // find the second largest
		{
			if (l != indexOfLargest) // skip over the largest one
			{
				if (diceRollHolder[l] >= secondLargest)
				{
					secondLargest = diceRollHolder[l];
					indexOfSecondLargest = l;
				}
			}
		}

		for (int m = 0; m < 4; m++)  // find the third largest
		{
			if ((m != indexOfLargest) || (m != indexOfSecondLargest)) // skip over the largest and second largest
			{
				if (diceRollHolder[m] >= thirdLargest)
				{
					thirdLargest = diceRollHolder[m];
					indexOfThirdLargest = m;
				}
			}
		}


	}

}

	//constructor: passes values to each ability score and set hit points to 10
	Character::Character(int str, int dex, int con, int intel, int wis, int cha) {
		abilityScores[0] = str;
		abilityScores[1] = dex;
		abilityScores[2] = con;
		abilityScores[3] = intel;
		abilityScores[4] = wis;
		abilityScores[5] = cha;

		// and set hit points to 10
		currentHitPoints = 10;
	}


	//! Implementation of the verification of a newly created Character
	//! @return bool value, true of the character is valid (stats should be in the 3-18 range for a new character), false if invalid. 
	bool Character::validateNewCharacter()
	{
		for (int i = 0; i <= 5; i++)
			if (abilityScores[i] < 3 || abilityScores[i]>18)
				return false;
		return true;
	}

	//! Implementation of fill cell, set any cell to anything it might eventually contain
	//! @param damage: damage sustained by the character
	void Character::hit(int damage)
	{
		currentHitPoints = currentHitPoints - damage;
	}

	//! Implementation of a getter method for currentHitPoints
	//! @return int: value of currentHitPoints
	int Character::getHitPoints()
	{
		return currentHitPoints;
	}

	int Character::rollSixSidedDie() {
		srand(static_cast<unsigned int>(time(0)));
		return rand() % 6 + 1;
	}

	int Character::generateAbilityModifier(int score) {
		// to get ability modifier, substract 10 from ability score, then divide by 2 (round down)
		return ((score - 10) / 2);
	}
