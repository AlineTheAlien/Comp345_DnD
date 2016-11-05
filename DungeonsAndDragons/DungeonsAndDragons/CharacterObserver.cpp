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

	string armor = _subject->getArmorName();
	string shield = _subject->getShield();
	string weapon = _subject->getWeapon();
	string boots = _subject->getBoots();
	string ring = _subject->getRing();
	string helmet = _subject->getHelmet();

	cout << "\n\n Displaying your character's current stats...\n" << endl;
	cout << " Your character's current level is: " << level << endl;
	cout << " Your character's current HP is: " << hp << "/" << maxhp << endl;
	cout << "\n Your character's current strength score is: " << strength << endl;
	cout << " Your character's current dexterity score is: " << dexterity << endl;
	cout << " Your character's current constitution score is: " << constitution << endl;
	cout << " Your character's current intelligence score is: " << intelligence << endl;
	cout << " Your character's current wisdom score is: " << wisdom << endl;
	cout << " Your character's current charisma score is: " << charisma << endl;

	cout << "\n\n Displaying your character's current equipped items..." << endl;
	cout << "\n Armor worn is : " << armor << endl;
	cout << " Shield equipped is : " << shield << endl;
	cout << " Weapon equipped is : " << weapon << endl;
	cout << " Boots worn are : " << boots << endl;
	cout << " Ring equipped is : " << ring << endl;
	cout << " Helmet worn is : " << helmet << endl;
}