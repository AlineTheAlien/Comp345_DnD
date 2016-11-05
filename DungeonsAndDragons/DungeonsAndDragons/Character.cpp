//! @file 
//! @brief Implementation file for the Character class 
//!  
//! Assumes that Character is of fighter type
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
#include <vector>
using namespace std;
using std::string;

int abilityScores[6];
int abilityModifiers[6];
int currentHitPoints;
int maxHitPoints;
int currentLevel;
long currentExperiencePoints;
int armorClass;
//The items equipped in the future will be objects of type Item (is implemented in partner's assignment)
//in the future, will be of type Item, not string. string only for demonstration purposes
string myArmor;
string myShield;
string myWeapon;
string myBoots;
string myRing;
string myHelmet;
int attackBonus;

//! Default constructor for a fighter character
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
	sort(abilityHolder, abilityHolder + 6, greater<int>());

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

	//Initially, as character is not hit, the maximum HP is the same as the current HP
	maxHitPoints = currentHitPoints;

	//Depending on type of armor worn, armor class differs
	//Default armor class will be 11 + dexterity modifier, as I don't have access to the Items class yet
	armorClass = 11 + abilityModifiers[1];

	//Attack bonus, is based on strength modifier, dexterity modifier, and level
	//In the default constructor, level is 0 therefore attack bonus is just based on strength + dexterity modifiers
	attackBonus = abilityModifiers[0] + abilityModifiers[1];

	//Damage bonus, based on strength modifier
	damageBonus = abilityModifiers[0];

	//No equipped items because a new character does not have equipped items
	myArmor = "None";
	myShield = "None";
	myWeapon = "None";
	myBoots = "None";
	myRing = "None";
	myHelmet = "None";

	equippedItems = new ItemContainer("EQUIPPED");
	backpack = new ItemContainer("BACKPACK");
}

//! Constructor: Passes values to each ability score
//! @param str: strength score, dex: dexterity score, con: constitution score, intel: intelligence score, wis: wisdom score, cha: charisma score
Character::Character(int str, int dex, int con, int intel, int wis, int cha) {

	int modifierHolder[6];

	currentLevel = 0;
	currentExperiencePoints = 0;

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

	//For demonstration, equipped items will be initialized with strings
	myArmor = "None";
	myShield = "None";
	myWeapon = "None";
	myBoots = "None";
	myRing = "None";
	myHelmet = "None";

	equippedItems = new ItemContainer("EQUIPPED");
	backpack = new ItemContainer("BACKPACK");
}

//! Desctructor
Character::~Character() {
	delete equippedItems;
	delete backpack;
};


//! Implementation of the verification of a newly created Character
//! @return bool value, true ff the character is valid (stats should be in the 3-18 range for a new character), false if invalid. 
bool Character::validateNewCharacter()
{
	for (int i = 0; i <= 5; i++)
		if (abilityScores[i] < 3 || abilityScores[i]>18)
			return false;
	return true;
}

//! Implementation of the verification of a newly created Character's ability modifiers
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

//! Accessor method for experience points 
//! @return int value, the value of character's current experience points
int Character::getCurrentExperiencePoints()
{
	return currentExperiencePoints;
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

//! Implementation of a getter method for currentHitPoints
//! @return int, value of currentHitPoints
int Character::getHitPoints()
{
	return currentHitPoints;
}

//! Implementation of a getter method for maxHitPoints
//! @return int, value of maxHitPoints
int Character::getMaxHitPoints()
{
	return maxHitPoints;
}

ItemContainer* Character::getEquippedItems() {
	return equippedItems;
}

ItemContainer* Character::getBackpack() {
	return backpack;
}

//! Accessor method for armor, note that this will be modified when items will be implemented
//! @return string value, the value of the character's equipped armor
string Character::getWornItemName(string type) {
	vector<Item> items = equippedItems->getItems();
	for (unsigned int i = 0; i < items.size(); i++) {
		if (items[i].getType() == type)
			return items[i].getName();
	}
}

//! Mutator method for held armor attribute, note that this will be modified when items will be implemented
//! Notify message is sent in this function in order to trigger an update of the view
//! @param a: string name of the armor equipped
void Character::setArmor(string a) {
	myArmor = a;
	Notify();
}

//! Mutator method for held shield attribute, note that this will be modified when items will be implemented
//! Notify message is sent in this function in order to trigger an update of the view
//! @param s: string name of the shield equipped
void Character::setShield(string s) {
	myShield = s;
	Notify();
}

//! Mutator method for held weapon attribute, note that this will be modified when items will be implemented
//! Notify message is sent in this function in order to trigger an update of the view
//! @param w: string name of the weapon equipped
void Character::setWeapon(string w) {
	myWeapon = w;
	Notify();
}

//! Mutator method for held boots attribute, note that this will be modified when items will be implemented
//! Notify message is sent in this function in order to trigger an update of the view
//! @param b: string name of the boots equipped
void Character::setBoots(string b) {
	myBoots = b;
	Notify();
}

//! Mutator method for held ring attribute, note that this will be modified when items will be implemented
//! Notify message is sent in this function in order to trigger an update of the view
//! @param r: string name of the ring equipped
void Character::setRing(string r) {
	myRing = r;
	Notify();
}

//! Mutator method for held helmet attribute, note that this will be modified when items will be implemented
//! Notify message is sent in this function in order to trigger an update of the view
//! @param h: string name of the helmet equipped
void Character::setHelmet(string h) {
	myHelmet = h;
	Notify();
}


void equipItem()
//! Damage recieved by character
//! Notify message is sent in this function in order to trigger an update of the view
//! @param damage: damage sustained by the character
void Character::getDamaged(int damage)
{
	currentHitPoints = currentHitPoints - damage;
	Notify(); 
}

//! Mutator method for strength ability score
//! Notify message is sent in this function in order to trigger an update of the view
//! @param str: new strength score to modify previous value to it
void Character::setStrengthScore(int str) {
	abilityScores[0] = str;
	Notify();
}

//! Mutator method for dexterity ability score
//! Notify message is sent in this function in order to trigger an update of the view
//! @param dex: new dexterity score to modify previous value to it
void Character::setDexterityScore(int dex) {
	abilityScores[1] = dex;
	Notify();
}

//! Mutator method for constitution ability score
//! Notify message is sent in this function in order to trigger an update of the view
//! @param con: new constitution score to modify previous value to it
void Character::setConstitutionScore(int con) {
	abilityScores[2] = con;
	Notify();
}

//! Mutator method for charisma ability score
//! Notify message is sent in this function in order to trigger an update of the view
//! @param cha: new charisma score to modify previous value to it
void Character::setCharismaScore(int cha) {
	abilityScores[3] = cha;
	Notify();
}

//! Mutator method for intelligence ablity score
//! Notify message is sent in this function in order to trigger an update of the view
//! @param intel: new intelligence score to modify previous value to it
void Character::setIntelligenceScore(int intel) {
	abilityScores[4] = intel;
	Notify();
}

//! Mutator method for wisdom ability score
//! Notify message is sent in this function in order to trigger an update of the view
//! @param wis: new wisdom score to modify previous value to it
void Character::setWisdomScore(int wis) {
	abilityScores[5] = wis;
	Notify();
}

//! Implementation that incrememnts level by one to show that character has leveled up
void Character::levelUp() {
	currentLevel++;

	maxHitPoints = maxHitPoints + levelHitPoints();
	currentHitPoints = maxHitPoints; //For now, HP refills back to full on level up

	Notify(); //Notify observers that level has been increased
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

//! Implementation for an ability modifier calculator
//! @param score: ability score for the certain attribute
//! @return int value, the value of the corresponding ability modifier
int Character::generateAbilityModifier(int score) {
	double x = ((score - 10) / 2.0);
	return floor(x);
}

//! Implementation to assign ability modifiers to the modifiers array
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
	int y = rollTenSidedDie();
		if (x == -4) {
			while (y <= 4) { //to avoid the HP staying the same or decreasing on level-up
				y = rollTenSidedDie();
			}
		}
		else if (x == -3) {
			while (y <= 3) { //to avoid the HP staying the same or decreasing on level-up
				y = rollTenSidedDie();
			}
		}
		else if (x == -2) {
			while (y <= 2) { //to avoid the HP staying the same or decreasing on level-up
				y = rollTenSidedDie();
			}
		}
		else if (x == -1) {
			while (y <= 1) { //to avoid the HP staying the same or decreasing on level-up
				y = rollTenSidedDie();
			}
		}
	return (x + y);
}

//! Function to display character information
void Character::displayCharacterInfo() {
	cout << "************CHARACTER INFO!************\n\n" << std::endl;

	cout << "Strength Score is: " << getStrengthScore() << endl;
	cout << "Dexterity Score is: " << getDexterityScore() << endl;
	cout << "Constitution Score is: " << getConstitutionScore() << endl;
	cout << "Intelligence Score is: " << getIntelligenceScore() << endl;
	cout << "Wisdom Score is: " << getWisdomScore() << endl;
	cout << "Charisma Score is: " << getCharismaScore() << endl;

	cout << "\nStrength Modifier is: " << getStrengthModifier() << endl;
	cout << "Dexterity Modifier is: " << getDexterityModifier() << endl;
	cout << "Constitution Modifier is: " << getConstitutionModifier() << endl;
	cout << "Intelligence Modifier is: " << getIntelligenceModifier() << endl;
	cout << "Wisdom Modifier is: " << getWisdomModifier() << endl;
	cout << "Charisma Modifier is: " << getCharismaModifier() << endl;

	cout << "\nCurrent Level is:  " << getCurrentLevel() << endl;
	cout << "\nCurrent HP is: " << getHitPoints() << endl;
	cout << "\nCurrent EXP is: " << getCurrentExperiencePoints() << endl;
	cout << "\nCurrent Armor Class is: " << getArmorClass() << endl;
	cout << "\nCurrent Attack Bonus is: " << getAttackBonus() << endl;
	cout << "\nCurrent Damage Bonus is: " << getDamageBonus() << endl;
}

//! Function that displays character's current equipment
void Character::displayEquipment() {
	cout << "\nArmor worn is : " << getWornItemName("ARMOR") << endl;
	cout << "Shield equipped is : " << getWornItemName("SHIELD") << endl;
	cout << "Weapon equipped is : " << getWornItemName("WEAPON") << endl;
	cout << "Boots worn are : " << getWornItemName("BOOTS") << endl;
	cout << "Ring equipped is : " << getWornItemName("RING") << endl;
	cout << "Helmet worn is : " << getWornItemName("HELMET") << endl;
	cout << "Belt worn is : " << getWornItemName("BELT") << endl;
}