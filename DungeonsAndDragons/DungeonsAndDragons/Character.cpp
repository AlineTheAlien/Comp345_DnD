//! @file 
//! @brief Implementation file for the Character class 
//!  
//! Assumes that Character is of fighter type
//!

#include "stdafx.h" 
#include "Character.h"
#include "FriendlyStrategy.h"
#include "AggressorStrategy.h"
#include "HumanPlayerStrategy.h"
#include "Dice.h"
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
#include <vector>
using namespace std;
using std::string;

//! Default constructor for a fighter character
Character::Character()
{

	objectType = 'P';

	currentLevel = 0;
	currentHitPoints = 0;
	maxHitPoints = 0;
	numberofAttacks = 1;
	armorClass = 0;
	attackBonus = 0;
	damageBonus = 0;

	abilityScores[0] = 0;
	abilityScores[1] = 0;
	abilityScores[2] = 0;
	abilityScores[3] = 0;
	abilityScores[4] = 0;
	abilityScores[5] = 0;

	abilityModifiers[0] = 0;
	abilityModifiers[1] = 0;
	abilityModifiers[2] = 0;
	abilityModifiers[3] = 0;
	abilityModifiers[4] = 0;
	abilityModifiers[5] = 0;

	equipped = new ItemContainer("EQUIPPED");
	backpack = new ItemContainer("BACKPACK");
}

//! Constructor: Passes values to each ability score
//! @param str: strength score, dex: dexterity score, con: constitution score, intel: intelligence score, wis: wisdom score, cha: charisma score
Character::Character(char type, int str, int dex, int con, int intel, int wis, int cha) {

	if (type == 'F') {
		strategy = new FriendlyStrategy();
	}
	else if (type == 'E') {
		strategy = new AggressorStrategy();
	}
	else if (type == 'P') {
		strategy = new HumanPlayerStrategy();
	}

	int modifierHolder[6];

	objectType = type;
	currentLevel = 0;

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

	currentHitPoints = 10 + abilityModifiers[2];

	maxHitPoints = currentHitPoints;

	//Depending on type of armor worn, armor class differs
	//Default armor class will be 11 + dexterity modifier, as I don't have access to the Items class yet
	armorClass = 11 + abilityModifiers[1];

	//Attack bonus, is based on strength modifier, dexterity modifier, and level
	attackBonus = abilityModifiers[0] + abilityModifiers[1];

	//Damage bonus, based on strength modifier
	damageBonus = abilityModifiers[0];

	//NumOfAttacks increases by 1 every 5 levels
	numberofAttacks = 1; 

	equipped = new ItemContainer("EQUIPPED");
	backpack = new ItemContainer("BACKPACK");
}

//! Destructor
Character::~Character() {
	delete equipped;
	delete backpack;
}

//! Method to validate a newly created Character
//! @return bool value, true ff the character is valid (stats should be in the 3-18 range for a new character), false if invalid. 
bool Character::validateNewCharacter()
{
	for (int i = 0; i <= 5; i++)
		if (abilityScores[i] < 3 || abilityScores[i] > 18)
			return false;
	return true;
}

//! Method to validate a newly created character's ability modifiers
//! @return bool value, true if the character is valid (modifiers should be in the -4 to +4 range for a new character), false if invalid. 
bool Character::validateAbilityModifiers()
{
	for (int i = 0; i <= 5; i++)
		if (abilityModifiers[i] < -4 || abilityModifiers[i] > 4)
			return false;
	return true;
}

//! Accessor method for strength score attribute
//! @return int value, the value of the strength ability score
int Character::getStrengthScore()
{
	return abilityScores[0];
}

//! Accessor method for dexterity score attribute
//! @return int value, the value of the dexterity ability score
int Character::getDexterityScore()
{
	return abilityScores[1];
}

//! Accessor method for constitution score attribute
//! @return int value, the value of the constitution ability score
int Character::getConstitutionScore()
{
	return abilityScores[2];
}

//! Accessor method for charisma score attribute
//! @return int value: the value of the charisma ability score
int Character::getCharismaScore()
{
	return abilityScores[3];
}

//! Accessor method for intelligence score attribute
//! @return int value, the value of the intelligence ability score
int Character::getIntelligenceScore()
{
	return abilityScores[4];
}

//! Accessor method for wisdom score attribute
//! @return int value, the value of the wisdom ability score
int Character::getWisdomScore()
{
	return abilityScores[5];
}

//! Accessor method for strength score modifier
//! @return int value, the value of the strength modifier
int Character::getStrengthModifier()
{
	return abilityModifiers[0];
}

//! Accessor method for dexterity score modifier
//! @return int value, the value of the dexterity modifier
int Character::getDexterityModifier()
{
	return abilityModifiers[1];
}
//! Accessor method for constitution score modifier
//! @return int value, the value of the constitution modifier
int Character::getConstitutionModifier()
{
	return abilityModifiers[2];
}

//! Accessor method for charisma score modifier
//! @return int value, the value of the charisma modifier
int Character::getCharismaModifier()
{
	return abilityModifiers[3];
}

//! Accessor method for intelligence score modifier
//! @return int value, the value of the intelligence modifier
int Character::getIntelligenceModifier()
{
	return abilityModifiers[4];
}

//! Accessor method for wisdom score modifier
//! @return int value, the value of the wisdom modifier
int Character::getWisdomModifier()
{
	return abilityModifiers[5];
}

//! Accessor method for character's current level
//! @return int value, the value of the character's level
int Character::getCurrentLevel()
{
	return currentLevel;
}

//! Accessor method for character's armor class 
//! @return int value, the value of the character's armor class
int Character::getArmorClass()
{
	return armorClass;
}

//! Accessor method for attack bonus
//! @return int value: the value of the character's attack bonus
int Character::getAttackBonus()
{
	return attackBonus;
}

//! Accessor method for damage bonus
//! @return int value, the value of the character's damage bonus
int Character::getDamageBonus()
{
	return damageBonus;
}

//! Method to get the current hit points
//! @return int, value of currentHitPoints
int Character::getHitPoints()
{
	return currentHitPoints;
}

//! Method to get the maximum hit points
//! @return int, value of maxHitPoints
int Character::getMaxHitPoints()
{
	return maxHitPoints;
}

//! Method to get all equipped items
//! @return A pointer to an item container representing equipped items
ItemContainer* Character::getEquippedItems() {
	return equipped;
}

//! Method to get all items inside the backpack
//! @return A pointer to an item container representing the backpack
ItemContainer* Character::getBackpack() {
	return backpack;
}

//! Method to display the name of a specified type of equipped item
//! @param : The type of the equipment as a string value
//! return The name of the item as a string value
string Character::getWornItemName(string type) {
	vector<Item*> items = equipped->getItems();
	for (unsigned int i = 0; i < items.size(); i++) {
		if (items[i]->getType() == type)
			return items[i]->getName();
	}
	return "";
}


//! Mutator method for maxHitPoints attribute
//@param hp: value of hp to set maxHitPoints to
void Character::setMaxHitPoints(int hp) {
	maxHitPoints = hp;
}

//! Mutator method for armorClass attribute
//@param ac: value to set armorClass to
void Character::setArmorClass(int ac) {
	armorClass = ac;
}

//! Mutator method for damageBonus attribute
//@param db: value to set damageBonus to
void Character::setDamageBonus(int db) {
	damageBonus = db;
}

//! Mutator method for attackBonus attribute
//@param ab: value to set attackBonus to
void Character::setAttackBonus(int ab) {
	attackBonus = ab;
}

//! Mutator method for numberOfAttacks attribute
//@param na: value to set numberOfAttacks to
void Character::setNumberOfAttacks(int na) {
	numberofAttacks = na;
}

//! Accessor method for numberOfAttacks attribute
//! @return int value, the value of the numberOfAttacks attribute
int Character::getNumberOfAttacks()
{
	return numberofAttacks;
}

void Character::setType(char c)
{
	objectType = c;
}

//! Method to equip an item on the character from the backpack
//! @param : The index position of the item to wear inside the vector representing a backpack
void Character::equipItem(int index) {
	vector<Item*> backpackItems = backpack->getItems();
	string itemName = backpackItems[index]->getName();
	cout << "Equipping " << itemName << endl;
	backpack->transfer(equipped, index); // transfer from 'BACKPACK' container to 'EQUIPPED'

	Item* ptr = equipped->getItem(itemName);
	vector<Enhancement> enhance;
	enhance = ptr->getEnhancements();

	for (int i = 0; i != enhance.size(); i++) {
		string enhanceType;
		int enhanceBonus;
		enhanceType = enhance[i].getType();
		enhanceBonus = enhance[i].getBonus();

		if (enhanceType == "STRENGTH") {
			abilityScores[0] += enhanceBonus;
		}
		else if (enhanceType == "DEXTERITY") {
			abilityScores[1] += enhanceBonus;
		}
		else if (enhanceType == "CONSTITUTION") {
			abilityScores[2] += enhanceBonus;
		}
		else if (enhanceType == "CHARISMA") {
			abilityScores[3] += enhanceBonus;
		}
		else if (enhanceType == "INTELLIGENCE") {
			abilityScores[4] += enhanceBonus;
		}
		else if (enhanceType == "WISDOM") {
			abilityScores[5] += enhanceBonus;
		}
		else if (enhanceType == "ARMOR CLASS") {
			armorClass += enhanceBonus;
		}
		else if (enhanceType == "ATTACK BONUS") {
			attackBonus += enhanceBonus;
		}
		else if (enhanceType == "DAMAGE BONUS") {
			damageBonus += enhanceBonus;
		}
	}
	Notify();
	cout << endl;
}

//! Method to unequip an item and put it into the backpack
//! @param : The index position of the item to be equipped inside the vector representing a list of equipped items
void Character::unequipItem(int index) {
	vector<Item*> equippedItems = equipped->getItems();
	string itemName = equippedItems[index]->getName();
	cout << "Unequipping " << itemName << endl;
	equipped->transfer(backpack, index); // transfer from 'EQUIPPED' to 'BACKPACK'

	Item* ptr = backpack->getItem(itemName);
	vector<Enhancement> enhance;
	enhance = ptr->getEnhancements();

	for (int i = 0; i != enhance.size(); i++) {
		string enhanceType;
		int enhanceBonus;
		enhanceType = enhance[i].getType();
		enhanceBonus = enhance[i].getBonus();

		if (enhanceType == "STRENGTH") {
			abilityScores[0] -= enhanceBonus;
			Notify();
		}
		else if (enhanceType == "DEXTERITY") {
			abilityScores[1] -= enhanceBonus;
			Notify();
		}
		else if (enhanceType == "CONSTITUTION") {
			abilityScores[2] -= enhanceBonus;
			Notify();
		}
		else if (enhanceType == "CHARISMA") {
			abilityScores[3] -= enhanceBonus;
			Notify();
		}
		else if (enhanceType == "INTELLIGENCE") {
			abilityScores[4] -= enhanceBonus;
			Notify();
		}
		else if (enhanceType == "WISDOM") {
			abilityScores[5] -= enhanceBonus;
			Notify();
		}
		else if (enhanceType == "ARMOR CLASS") {
			armorClass -= enhanceBonus;
			Notify();
		}
		else if (enhanceType == "ATTACK BONUS") {
			attackBonus -= enhanceBonus;
			Notify();
		}
		else if (enhanceType == "DAMAGE BONUS") {
			damageBonus -= enhanceBonus;
			Notify();
		}
	}

	cout << endl;
}

//! Method to get the damage received by the character
//! Notify message is sent in this function in order to trigger an update of the view
//! @param damage: damage sustained by the character
void Character::getDamaged(int damage)
{
	currentHitPoints = currentHitPoints - damage;
	Notify();
}

//! Method to set the level of the character
//! @param level : level to set to the character
void Character::setLevel(int level) {
	currentLevel = level;
}

//! Method to set the current hit points of the character
//! @param level : current hit points to set to the character
void Character::setCurrentHitPoints(int currentHP) {
	currentHitPoints = currentHP;
}

//! Method to set the total hit points of the character
//! @param level : total hit points to set to the character
void Character::setTotalHitPoints(int totalHP) {
	maxHitPoints = totalHP;
}

//! Mutator method for strength ability score
//! Notify message is sent in this function in order to trigger an update of the view
//! @param str: new strength score to modify previous value to it
void Character::setStrengthScore(int str) {
	abilityScores[0] = str;
	//Notify();
}

//! Mutator method for dexterity ability score
//! Notify message is sent in this function in order to trigger an update of the view
//! @param dex: new dexterity score to modify previous value to it
void Character::setDexterityScore(int dex) {
	abilityScores[1] = dex;
	//Notify();
}

//! Mutator method for constitution ability score
//! Notify message is sent in this function in order to trigger an update of the view
//! @param con: new constitution score to modify previous value to it
void Character::setConstitutionScore(int con) {
	abilityScores[2] = con;
	//Notify();
}

//! Mutator method for charisma ability score
//! Notify message is sent in this function in order to trigger an update of the view
//! @param cha: new charisma score to modify previous value to it
void Character::setCharismaScore(int cha) {
	abilityScores[3] = cha;
	//Notify();
}

//! Mutator method for intelligence ablity score
//! Notify message is sent in this function in order to trigger an update of the view
//! @param intel: new intelligence score to modify previous value to it
void Character::setIntelligenceScore(int intel) {
	abilityScores[4] = intel;
	//Notify();
}

//! Mutator method for wisdom ability score
//! Notify message is sent in this function in order to trigger an update of the view
//! @param wis: new wisdom score to modify previous value to it
void Character::setWisdomScore(int wis) {
	abilityScores[5] = wis;
	//Notify();
}

//! Mutator method for strength modifier
//! @param str : new strength modifier score 
void Character::setStrengthModifier(int str) {
	abilityModifiers[0] = str;
}

//! Mutator method for dexterity modifier
//! @param dex : new dexterity modifier score 
void Character::setDexterityModifier(int dex) {
	abilityModifiers[1] = dex;
}

//! Mutator method for constitution modifier
//! @param con : new constitution modifier score 
void Character::setConstitutionModifier(int con) {
	abilityModifiers[2] = con;
}

//! Mutator method for charisma modifier
//! @param cha : new charisma modifier score 
void Character::setCharismaModifier(int cha) {
	abilityModifiers[3] = cha;
}

//! Mutator method for intelligence modifier
//! @param intel : new intelligence modifier score 
void Character::setIntelligenceModifier(int intel) {
	abilityModifiers[4] = intel;
}

//! Mutator method for wisdom modifier
//! @param wis : new wisdom modifier score 
void Character::setWisdomModifier(int wis) {
	abilityModifiers[5] = wis;
}

void Character::chooseScoresOnLevelUp() {
	int chooseLevelOption = 1;
	int chooseAbility = 1;
	int ctr = 1;
	bool validLevelOption = false;
	bool validAbility = false;

	cout << "\n Congratulations! Your character gained a level!" << endl;
	//Sleep(3000);
	cout << "\n You are now allowed to modify your ability scores." << endl;
	cout << "\n You can either raise one attribute by 2 points, or raise 2 attributes by one point each." << endl;
	cout << "\n Please enter 1 for choice 1, or 2 for choice 2. Enter anything else to exit." << endl;
	//Sleep(400);
	do {
		cout << "\n 1- I want to raise one attribute by 2 points!" << endl;
		cout << "\n 2- I want to raise two attributes by 1 point each!" << endl;
		cin >> chooseLevelOption;
		if (chooseLevelOption == 1 || chooseLevelOption == 2) {
			validLevelOption = true;
		}
	} while (validLevelOption == false);

	if (chooseLevelOption == 1) {
		do {
			cout << "\n Which attribute score would you like to raise by two points? (Press any other key to exit)\n" << endl;
			Sleep(400);
			cout << " 1 - Strength" << endl;
			cout << " 2 - Dexterity" << endl;
			cout << " 3 - Constitution" << endl;
			cout << " 4 - Intelligence" << endl;
			cout << " 5 - Wisdom" << endl;
			cout << " 6 - Charisma" << endl;

			cin >> chooseAbility;

			if (chooseAbility >= 1 && chooseAbility <= 6) {
				validAbility = true;
			}
		} while (validAbility == false);

		if (chooseAbility == 1) {
			abilityScores[0] = abilityScores[0] + 2;
		}
		else if (chooseAbility == 2) {
			abilityScores[1] = abilityScores[1] + 2;
		}
		else if (chooseAbility == 3) {
			abilityScores[2] = abilityScores[2] + 2;
		}
		else if (chooseAbility == 4) {
			abilityScores[3] = abilityScores[3] + 2;
		}
		else if (chooseAbility == 5) {
			abilityScores[4] = abilityScores[4] + 2;
		}
		else if (chooseAbility == 6) {
			abilityScores[5] = abilityScores[5] + 2;
		}
		else {
			cout << "error" << endl;
		}

	}
	else if (chooseLevelOption == 2) {
		//Sleep(400);
		for (int i = 0; i < 2; i++) {

			if (ctr == 1) {
				cout << "\n What is the first attribute score you would like to raise by 1 point? (Press any other key to exit)\n" << endl;
			}
			else if (ctr == 2) {
				cout << "\n What is the second attribute score you would like to raise by 1 point? (Press any other key to exit)\n" << endl;
			}
			else {
				cout << "error" << endl;
			}
			cout << " 1 - Strength" << endl;
			cout << " 2 - Dexterity" << endl;
			cout << " 3 - Constitution" << endl;
			cout << " 4 - Intelligence" << endl;
			cout << " 5 - Wisdom" << endl;
			cout << " 6 - Charisma" << endl;

			cin >> chooseAbility;

			if (chooseAbility == 1) {
				abilityScores[0] = abilityScores[0] + 1;
			}
			else if (chooseAbility == 2) {
				abilityScores[1] = abilityScores[1] + 1;
			}
			else if (chooseAbility == 3) {
				abilityScores[2] = abilityScores[2] + 1;
			}
			else if (chooseAbility == 4) {
				abilityScores[3] = abilityScores[3] + 1;
			}
			else if (chooseAbility == 5) {
				abilityScores[4] = abilityScores[4] + 1;
			}
			else if (chooseAbility == 6) {
				abilityScores[5] = abilityScores[5] + 1;
			}
			ctr++;
		}
		cout << "\n Your ability scores have now been modified. :)\n" << endl;
	}
}

//! Method that increments the level by one to show that the character has leveled up
void Character::levelUp() {

	if (currentLevel != 0 && currentLevel % 5 == 0) {
		numberofAttacks++; //number of attacks/round increases every 5 levels 
	}

	currentLevel++;

	maxHitPoints = maxHitPoints + levelHitPoints();
	currentHitPoints = maxHitPoints; //For now, HP refills back to full on level up

	chooseScoresOnLevelUp(); //Ability scores to modify are chosen by the user

	for (int i = 0; i <= 5; i++ ) {
		abilityModifiers[i] = generateAbilityModifier(abilityScores[i]);
		//modify new ability modifiers
	}

	attackBonus++; //attack bonus goes up by one

	Notify(); //Notify observers that level has been increased
}

void Character::userChoiceLevelUp() {

	if (currentLevel % 5 == 0) {
		numberofAttacks++; //number of attacks/round increases every 5 levels 
	}

	currentLevel++;

	maxHitPoints = maxHitPoints + levelHitPoints();
	currentHitPoints = maxHitPoints; //For now, HP refills back to full on level up

	attackBonus++; //attack bonus goes up by one

	Notify(); //Notify observers that level has been increased
}

void Character::setCharacterName(string name) {
	characterName = name;
}

string Character::getCharacterName() {
	return characterName;
}

//! Randomizer function that simulates a dice roll of values between 1 and 6
//! @return int value, the value of the random dice roll between 1 and 6
int Character::rollSixSidedDie() {
	return rand() % 6 + 1;
}

//! Randomizer function that simulates a dice roll of values between 1 and 10
//! @return int value, the value of the random dice roll between 1 and 10
int Character::rollTenSidedDie() {
	return rand() % 10 + 1;
}

//Ability scores are calculated by rolling four 6-sided dice, where 3 of the highest rolls are summed up to a total
//This is done for a total of 6 times, where each total is assigned to a character's ability
//! Implementation of ability score calculator
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
			int r = Dice::roll("1d6");
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

//! Implementation for an ability modifier calculator
//! @param score: ability score for the certain attribute
//! @return int value, the value of the corresponding ability modifier
int Character::generateAbilityModifier(int score) {
	double x = ((score - 10) / 2.0);
	return floor(x);
}

//! Method to assign ability modifiers to the modifiers array
//! @param holder: array that will be passed in this function
void Character::assignAbilityModifiers(int holder[]) {
	for (int i = 0; i < 6; i++) {
		holder[i] = generateAbilityModifier(abilityScores[i]);
	}
}

//! Method that calculates amount that HP will increase after character levels up
//! @return int value, the value added to max hit points after gaining a level
int Character::levelHitPoints() {
	int x = getConstitutionModifier();
	int y = Dice::roll("1d10");
	if (x == -4) {
		while (y <= 4) { //to avoid the HP staying the same or decreasing on level-up
			y = Dice::roll("1d10");
		}
	}
	else if (x == -3) {
		while (y <= 3) { //to avoid the HP staying the same or decreasing on level-up
			y = Dice::roll("1d10");
		}
	}
	else if (x == -2) {
		while (y <= 2) { //to avoid the HP staying the same or decreasing on level-up
			y = Dice::roll("1d10");
		}
	}
	else if (x == -1) {
		while (y <= 1) { //to avoid the HP staying the same or decreasing on level-up
			y = Dice::roll("1d10");
		}
	}
	return (x + y);
}

//! Method to display character information
void Character::displayCharacterInfo() {

	cout << "\n\n Displaying your character's current stats...\n" << endl;
	cout << "\n\n Your character's name is: " << characterName << endl;
	cout << " \nYour character's current Level is: " << currentLevel << endl;
	cout << " Your character's current HP is: " << currentHitPoints << "/" << maxHitPoints << endl;

	cout << " Your character's current Strength Score is: " << abilityScores[0] << endl;
	cout << " Your character's current Dexterity Score is: " << abilityScores[1] << endl;
	cout << " Your character's current Constitution Score is: " << abilityScores[2] << endl;
	cout << " Your character's current Intelligence Score is: " << abilityScores[4] << endl;
	cout << " Your character's current Wisdom Score is: " << abilityScores[5] << endl;
	cout << " Your character's current Charisma Score is: " << abilityScores[3] << endl;

	cout << "\n Your character's current Strength Modifier is: " << abilityModifiers[0] << endl;
	cout << " Your character's current Dexterity Modifier is: " << abilityModifiers[1] << endl;
	cout << " Your character's current Constitution Modifier is: " << abilityModifiers[2] << endl;
	cout << " Your character's current Intelligence Modifier is: " << abilityModifiers[4] << endl;
	cout << " Your character's current Wisdom Modifier is: " << abilityModifiers[5] << endl;
	cout << " Your character's current Charisma Modifier is: " << abilityModifiers[3] << endl;

	cout << "\n Your character's current current Armor Class is: " << getArmorClass() << endl;
	cout << " Your character's current current Attack Bonus is: " << getAttackBonus() << endl;
	cout << " Your character's current current Damage Bonus is: " << getDamageBonus() << endl;
	cout << "\nCurrent Number of Attacks/round is:  " << getNumberOfAttacks() << endl;
	cout << endl;
}

//! Method that displays character's current equipment
void Character::displayEquipment() {
	string armor = this->getWornItemName("ARMOR");
	string shield = this->getWornItemName("SHIELD");
	string weapon = this->getWornItemName("WEAPON");
	string boots = this->getWornItemName("BOOTS");
	string ring = this->getWornItemName("RING");
	string helmet = this->getWornItemName("HELMET");
	string belt = this->getWornItemName("BELT");

	cout << "\n\n Displaying your character's current equipped items..." << endl;
	cout << "\n Armor worn is : " << armor << endl;
	cout << " Shield equipped is : " << shield << endl;
	cout << " Weapon equipped is : " << weapon << endl;
	cout << " Boots worn are : " << boots << endl;
	cout << " Ring equipped is : " << ring << endl;
	cout << " Helmet worn is : " << helmet << endl;
	cout << " Belt worn is : " << helmet << endl;
	cout << endl;
}

//! Method that displays character's inventory pane
void Character::displayBackpack() {
	cout << "---------------------------" << endl;
	cout << "Inventory Pane" << endl;
	cout << "---------------------------" << endl;
	vector<Item*> items = backpack->getItems();
	for (unsigned int i = 0; i < items.size(); i++) {
	cout << "[" << i << "]" << items[i]->getType() << ": " << items[i]->getName() << endl;
	items[i]->displayEnhancements();
	cout << endl;
	}
	cout << endl;
}

//! Method to set the strategy of the character
//! @param strategy : A concrete strategy object
void Character::setStrategy(Strategy* strategy) {
	this->strategy = strategy;
}
//! Method to execute the strategy of the character
//! @param map : Map in which characters are placed in
//! @param i : Position i of the player
//! @param j : Position j of the player
void Character::executeStrategy(Map* map, MapObject* firstCharacter, MapObject* secondCharacter) {
	strategy->execute(map, firstCharacter, secondCharacter);
}

