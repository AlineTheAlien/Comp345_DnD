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
#include <string>
using namespace std;
using std::string;



int abilityScores[6];
int abilityModifiers[6];
int currentHitPoints;
int currentLevel;
long currentExperiencePoints;
int armorClass;
//equipped items is an array that holds objects of type Item (is implementted in partner's assignment)
string equippedItems[6];//in the future, will be of type Item, not string. string only for demonstration purposes
int attackBonus;

// default constructor
//used for the first time a certain character is created
Character::Character()
{
	int abilityHolder[6];
	int modifierHolder[6];

	//Initialize level and experience points to 0
	currentLevel = 0;
	currentExperiencePoints = 0;

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

	//set hit points as 10 summed with the character's calculated  constitution modifier
	currentHitPoints = 10 + abilityModifiers[2]; 

	//Depending on type of armor worn, armor class differs
	//Default armor class will be 11 + dexterity modifier, as I don't have access to the Items class yet
	armorClass = 11 + abilityModifiers[1];

	//Attack bonus, is based on strength modifier, dexterity modifier, and level
	//In the default constructor, level is 0 therefore attack bonus is just based on strength + dexterity modifiers
	attackBonus = abilityModifiers[0] + abilityModifiers[1];

	//Damage bonus, based on strength modifier
	damageBonus = abilityModifiers[0];

	//No equipped items because a new character does not have equipped items
	equippedItems[0] = "None";
	equippedItems[1] = "None";
	equippedItems[2] = "None";
	equippedItems[3] = "None";
	equippedItems[4] = "None";
	equippedItems[5] = "None";
}

//constructor: passes values to level and to each ability score
//Used when a character needs to be recreated for a new map
//In the future, prevequip will be an array or vector holding the characters Item equipment (objects), if any
//In this case, I am using string array for demonstration purposes only
Character::Character(string prevequip[], int lvl, long exp,  int str, int dex, int con, int intel, int wis, int cha) {
	
	int modifierHolder[6];

	currentLevel = lvl;
	currentExperiencePoints = exp;

	abilityScores[0] = str; //strength
	abilityScores[1] = dex; //dexterity
	abilityScores[2] = con; //constitution
	abilityScores[3] = cha; //charisma
	abilityScores[4] = intel; //intelligence
	abilityScores[5] = wis; //wisdom

	assignAbilityModifiers(modifierHolder);

	abilityModifiers[0] = modifierHolder[0]; //strength
	abilityModifiers[1] = modifierHolder[1]; //dexterity
	abilityModifiers[2] = modifierHolder[2]; //constitution
	abilityModifiers[3] = modifierHolder[3]; //charisma
	abilityModifiers[4] = modifierHolder[4]; //intelligence
	abilityModifiers[5] = modifierHolder[5]; //wisdom

	//set hit points as a 1d10 dice roll summed with the character's calculated  constitution modifier
	//1d10 according to the d20 rules
	currentHitPoints = (rollTenSidedDie() * currentLevel) + abilityModifiers[2];

	//Depending on type of armor worn, armor class differs
	//Default armor class will be 11 + dexterity modifier, as I don't have access to the Items class yet
	armorClass = 11 + abilityModifiers[1];

	//Attack bonus, is based on strength modifier, dexterity modifier, and level
	attackBonus = (abilityModifiers[0] * currentLevel) + abilityModifiers[1];

	//Damage bonus, based on strength modifier
	damageBonus = abilityModifiers[0];

	//For demonstration, equipped items will be initialized with strings
	equippedItems[0] = prevequip[0];
	equippedItems[1] = prevequip[1];
	equippedItems[2] = prevequip[2];
	equippedItems[3] = prevequip[3];
	equippedItems[4] = prevequip[4];
	equippedItems[5] = prevequip[5];

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

//All character attributes accessors
int Character::getStrengthScore()
{
	return abilityScores[0];
}

int Character::getDexterityScore()
{
	return abilityScores[1];
}

int Character::getConstitutionScore()
{
	return abilityScores[2];
}

int Character::getCharismaScore()
{
	return abilityScores[3];
}

int Character::getIntelligenceScore()
{
	return abilityScores[4];
}

int Character::getWisdomScore()
{
	return abilityScores[5];
}

int Character::getStrengthModifier()
{
	return abilityModifiers[0];
}

int Character::getDexterityModifier()
{
	return abilityModifiers[1];
}

int Character::getConstitutionModifier()
{
	return abilityModifiers[2];
}

int Character::getCharismaModifier()
{
	return abilityModifiers[3];
}

int Character::getIntelligenceModifier()
{
	return abilityModifiers[4];
}

int Character::getWisdomModifier()
{
	return abilityModifiers[5];
}

int Character::getCurrentLevel()
{
	return currentLevel;
}

int Character::getCurrentExperiencePoints()
{
	return currentExperiencePoints;
}

int Character::getArmorClass()
{
	return armorClass;
}

int Character::getAttackBonus()
{
	return attackBonus;
}

int Character::getDamageBonus()
{
	return damageBonus;
}

//! Implementation of a getter method for currentHitPoints
//! @return int: value of currentHitPoints
int Character::getHitPoints()
{
	return currentHitPoints;
}

string Character::getArmor() {
	return equippedItems[0];
}

string Character::getShield() {
	return equippedItems[1];
}

string Character::getWeapon() {
	return equippedItems[2];
}

string Character::getBoots() {
	return equippedItems[3];
}

string Character::getRing() {
	return equippedItems[4];
}

string Character::getHelmet() {
	return equippedItems[5];
}

//! Damage recieved by character
//! @param damage: damage sustained by the character
void Character::getDamaged(int damage)
{
	currentHitPoints = currentHitPoints - damage;
}

void Character::levelUp() {
	currentLevel = currentLevel++;
}

//In the future, roll dice functions of the Dice class will be used
int Character::rollSixSidedDie() {
	return rand() % 6 + 1;
}

int Character::rollTenSidedDie() {
	return rand() % 10 + 1;
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


void Character::displayCharacterInfo() {
	std::cout << "************CHARACTER INFO!************\n\n"  << std::endl;

	std::cout << "Strength Score is: " << getStrengthScore() << std::endl;
	std::cout << "Dexterity Score is: " << getDexterityScore() << std::endl;
	std::cout << "Constitution Score is: " << getConstitutionScore() << std::endl;
	std::cout << "Intelligence Score is: " << getIntelligenceScore() << std::endl;
	std::cout << "Wisdom Score is: " << getWisdomScore() << std::endl;
	std::cout << "Charisma Score is: " << getCharismaScore() << std::endl;

	std::cout << "\nStrength Modifier is: " << getStrengthModifier() << std::endl;
	std::cout << "Dexterity Modifier is: " << getDexterityModifier() << std::endl;
	std::cout << "Constitution Modifier is: " << getConstitutionModifier() << std::endl;
	std::cout << "Intelligence Modifier is: " << getIntelligenceModifier() << std::endl;
	std::cout << "Wisdom Modifier is: " << getWisdomModifier() << std::endl;
	std::cout << "Charisma Modifier is: " << getCharismaModifier() << std::endl;

	std::cout << "\nCurrent Level is:  " << getCurrentLevel() << std::endl;
	std::cout << "\nCurrent HP is: " << getHitPoints() << std::endl;
	std::cout << "\nCurrent EXP is: " << getCurrentExperiencePoints() << std::endl;
	std::cout << "\nCurrent Armor Class is: " << getArmorClass() << std::endl;
	std::cout << "\nCurrent Attack Bonus is: " << getAttackBonus() << std::endl;
	std::cout << "\nCurrent Damage Bonus is: " << getDamageBonus() << std::endl;
}

void Character::displayEquipment() {
	std::cout << "\nArmor worn is : " << getArmor() << std::endl;
	std::cout << "Shield equipped is : " << getShield() << std::endl;
	std::cout << "Weapon equipped is : " << getWeapon() << std::endl;
	std::cout << "Boots worn are : " << getBoots() << std::endl;
	std::cout << "Ring equipped is : " << getRing() << std::endl;
	std::cout << "Helmet worn is : " << getHelmet() << std::endl;
}
