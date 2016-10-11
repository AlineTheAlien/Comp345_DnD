//! @file 
//! @brief Implementation file for the Character class  
//!

#include "stdafx.h" 
#include "Character.h"
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <functional>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <math.h>
using namespace std;


int abilityScores[6];
int abilityModifiers[6];
int currentHitPoints;
int currentLevel = 1;
long currentExperiencePoints = 0;

// default constructor
Character::Character()
{
	int abilityHolder[6];
	int modifierHolder[6];

	calculateAbilityScores(abilityHolder);

	//Sorts the ability scores in descending order
	//Higher scores will be assigned to abilities with higher priority
	std::sort(abilityHolder, abilityHolder + 6, std::greater<int>());

	//Assign the totals to abilities based on priority
	//As the game only has the fighter class, the highest score is strength
	//Second highest should be dexterity, followed by constitution, charisma, intelligence, and wisdom
	abilityScores[0] = abilityHolder[0]; //strength
	abilityScores[1] = abilityHolder[1]; //dexterity
	abilityScores[2] = abilityHolder[2]; //constitution
	abilityScores[3] = abilityHolder[3]; //charisma
	abilityScores[4] = abilityHolder[4]; //intelligence
	abilityScores[5] = abilityHolder[5]; //wisdom

	//Calculates ability modifiers based on the characters ability scores
	assignAbilityModifiers(modifierHolder);

	//Assigns the modifiers with the same priority as listed above
	abilityModifiers[0] = modifierHolder[0]; //strength
	abilityModifiers[1] = modifierHolder[1]; //dexterity
	abilityModifiers[2] = modifierHolder[2]; //constitution
	abilityModifiers[3] = modifierHolder[3]; //charisma
	abilityModifiers[4] = modifierHolder[4]; //intelligence
	abilityModifiers[5] = modifierHolder[5]; //wisdom
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
	return rand() % 6 + 1;
}

//Ability scores are calculated by rolling four 6-sided dice,
//where 3 of the highest rolls are recorded and summed up to a total.
//This is done for a total of 6 times, where each total is assigned to a character's ability
void Character::calculateAbilityScores(int holder[]) {

	for (int i = 0; i < 6; i++) {

		int diceRollHolder[4];
		int largest = 0;
		int indexOfLargest;
		int secondLargest = 0;
		int indexOfSecondLargest;
		int thirdLargest = 0;
		int indexOfThirdLargest;
		int totalOfDice;

		//This loop is the action of rolling dice 4 times, where the array diceRollHolder
		//points to the values of the dice rolls
		for (int j = 0; j < 4; j++) {
			int r = rollSixSidedDie();
			//Sleep(258); for debugging purposes
			diceRollHolder[j] = r;
		}

		//The below loops are to find the highest three dice rolls out of the four

		//This loop find the highest dice roll
		for (int k = 0; k < 4; k++)  
		{
			if (diceRollHolder[k] >= largest)
			{
				largest = diceRollHolder[k];
				indexOfLargest = k;
			}
		}

		//This loop finds the second highest dice roll
		for (int l = 0; l < 4; l++)  
		{
			if (l != indexOfLargest) //The largest roll is ignored
			{
				if (diceRollHolder[l] >= secondLargest)
				{
					secondLargest = diceRollHolder[l];
					indexOfSecondLargest = l;
				}
			}
		}

		//This loop finds the third highest dice roll
		for (int m = 0; m < 4; m++) 
		{
			if ((m != indexOfLargest) && (m != indexOfSecondLargest)) //The largest and second largest rolls are ignored
			{
				if (diceRollHolder[m] >= thirdLargest)
				{
					thirdLargest = diceRollHolder[m];
					indexOfThirdLargest = m;
				}
			}
		}

		//Calculates the total of the top 3 largest dice
		totalOfDice = largest + secondLargest + thirdLargest;
		//Assigns that value in the array that is passed as a parameter 
		holder[i] = totalOfDice;
	}
}

void Character::displayAbilityScores(Character c) {
	std::cout << "Strength is:" << c.abilityScores[0] << std::endl;
	std::cout << "Dexterity is:" << c.abilityScores[1] << std::endl;
	std::cout << "Constitution is:" << c.abilityScores[2] << std::endl;
	std::cout << "Intelligence is:" << c.abilityScores[4] << std::endl;
	std::cout << "Wisdom is:" << c.abilityScores[5] << std::endl;
	std::cout << "Charisma is:" << c.abilityScores[3] << std::endl;
}

//To get ability modifier, substract 10 from ability score, then divide by 2 (round down)
int Character::generateAbilityModifier(int score) {
	double x = ((score - 10) / 2.0);
	return floor(x);//fix this so it rounds down on the 1.5,3.5
}

//Calculates the ability modifier for each score in the array that is passed as a parameter
void Character::assignAbilityModifiers(int holder[]) {
	for (int i = 0; i < 6; i++) {
		holder[i] = generateAbilityModifier(abilityScores[i]);
	}
}

void Character::displayAbilityModifiers(Character c) {
	std::cout << "Strength modifier is:" << c.abilityModifiers[0] << std::endl;
	std::cout << "Dexterity modifier is:" << c.abilityModifiers[1] << std::endl;
	std::cout << "Constitution modifier is:" << c.abilityModifiers[2] << std::endl;
	std::cout << "Intelligence modifier is:" << c.abilityModifiers[4] << std::endl;
	std::cout << "Wisdom modifier is:" << c.abilityModifiers[5] << std::endl;
	std::cout << "Charisma modifier is:" << c.abilityModifiers[3] << std::endl;
}

