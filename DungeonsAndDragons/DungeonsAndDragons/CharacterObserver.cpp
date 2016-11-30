//! @file 
//! @brief Cpp file for CharacterObserver class

#include "stdafx.h"
#include "CharacterObserver.h"
#include "Observer.h"
#include <iostream>
#include <string>
using namespace std;
using std::string;

//! CharacterObserver default constructor
CharacterObserver::CharacterObserver()
{
};

//! Character observer parameterized constructor
//! Upon instantiation, the CharacterObserver instantiates itself to a character
//! @param c: Pointer to an object of type Character
CharacterObserver::CharacterObserver(Character* c) {
	_subject = c;
	_subject->Attach(this);
}

//! Destructor that detaches the CharacterObserver from the subject (Character)
CharacterObserver::~CharacterObserver() {
	_subject->Detach(this);
}

//! Function that is called by Notify() when the state of the underlying subject object changes
void CharacterObserver::Update() {
	display();
}

//! Function that displays the character's attributes to the console window to demonstrate changes to subject
void CharacterObserver::display() {
	int level = _subject->getCurrentLevel();
	int hp = _subject->getHitPoints();
	int maxhp = _subject->getMaxHitPoints();
	int strength = _subject->getStrengthScore();
	int dexterity = _subject->getDexterityScore();
	int constitution = _subject->getConstitutionScore();
	int intelligence = _subject->getIntelligenceScore();
	int wisdom = _subject->getWisdomScore();
	int charisma = _subject->getCharismaScore();
	int strmodif = _subject->getStrengthModifier();
	int dexmodif = _subject->getDexterityModifier();
	int constmodif = _subject->getConstitutionModifier();
	int charmodif = _subject->getCharismaModifier();
	int intmodif = _subject->getIntelligenceModifier();
	int wismodif = _subject->getWisdomModifier();
	int armorclass = _subject->getArmorClass();
	int attackbonus = _subject->getAttackBonus();
	int damagebonus = _subject->getDamageBonus();
	int numofattacks = _subject->getNumberOfAttacks();

	string characterName = _subject->getCharacterName();
	string armor = _subject->getWornItemName("ARMOR");
	string shield = _subject->getWornItemName("SHIELD");
	string weapon = _subject->getWornItemName("WEAPON");
	string boots = _subject->getWornItemName("BOOTS");
	string ring = _subject->getWornItemName("RING");
	string helmet = _subject->getWornItemName("HELMET");
	string belt = _subject->getWornItemName("BELT");

	cout << "\n\n Displaying your character's current stats...\n" << endl;
	cout << "\n\n Your character's name is: " << characterName << endl;
	cout << " \nYour character's current level is: " << level << endl;
	cout << " Your character's current HP is: " << hp << "/" << maxhp << endl;

	cout << "\n Your character's current Strength score is: " << strength << endl;
	cout << " Your character's current Dexterity score is: " << dexterity << endl;
	cout << " Your character's current Constitution score is: " << constitution << endl;
	cout << " Your character's current Intelligence score is: " << intelligence << endl;
	cout << " Your character's current Wisdom score is: " << wisdom << endl;
	cout << " Your character's current Charisma score is: " << charisma << endl;

	cout << "\n Your character's current Strength Modifier is: " << strmodif << endl;
	cout << " Your character's current Dexterity Modifier is: " << dexmodif << endl;
	cout << " Your character's current Constitution Modifier is: " << constmodif << endl;
	cout << " Your character's current Intelligence Modifier is: " << intmodif << endl;
	cout << " Your character's current Wisdom Modifier is: " << wismodif << endl;
	cout << " Your character's current Charisma Modifier is: " << charmodif << endl;

	cout << "\n Your character's current current current Armor Class is: " << armorclass << endl;
	cout << " Your character's current current current Attack Bonus is: " << attackbonus << endl;
	cout << " Your character's current current current Damage Bonus is: " << damagebonus << endl;
	cout << "\nCurrent Number of Attacks/round is:  " << numofattacks << endl;

	cout << "\n\n Displaying your character's current equipped items..." << endl;
	cout << "\n Armor worn is : " << armor << endl;
	cout << " Shield equipped is : " << shield << endl;
	cout << " Weapon equipped is : " << weapon << endl;
	cout << " Boots worn are : " << boots << endl;
	cout << " Ring equipped is : " << ring << endl;
	cout << " Helmet worn is : " << helmet << endl;
	cout << " Belt worn is : " << belt << endl;
	cout << endl;
}

void CharacterObserver::UpdateGUI() {

}