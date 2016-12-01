#include "stdafx.h"
#include "TankBuilder.h"

//! TankBuilder constructor
TankBuilder::TankBuilder()
{
}

//! TankBuilder destructor
TankBuilder::~TankBuilder()
{
}

//! Method that prioritizes ability scores based on the score priority for Tank type of fighter characters
void TankBuilder::buildAbilityScores() {
	int temp[6];
	int modifiers[6];

	mycharacter->calculateAbilityScores(temp);

	sort(temp, temp + 6, greater<int>());

	mycharacter->setConstitutionScore(temp[0]);
	mycharacter->setDexterityScore(temp[1]);
	mycharacter->setStrengthScore(temp[2]);
	mycharacter->setIntelligenceScore(temp[3]);
	mycharacter->setCharismaScore(temp[4]);
	mycharacter->setWisdomScore(temp[5]);

	mycharacter->assignAbilityModifiers(modifiers);

	sort(modifiers, modifiers + 6, greater<int>());

	mycharacter->setConstitutionModifier(modifiers[0]);
	mycharacter->setDexterityModifier(modifiers[1]);
	mycharacter->setStrengthModifier(modifiers[2]);
	mycharacter->setIntelligenceModifier(modifiers[3]);
	mycharacter->setCharismaModifier(modifiers[4]);
	mycharacter->setWisdomModifier(modifiers[5]);

	//set hit points as 10 summed with the character's calculated  constitution modifier
	mycharacter->setCurrentHitPoints(10 + mycharacter->getConstitutionModifier());

	//Initially, as character is not hit, the maximum HP is the same as the current HP
	mycharacter->setMaxHitPoints(mycharacter->getHitPoints());

	//Depending on type of armor worn, armor class differs
	//Default armor class will be 11 + dexterity modifier, as I don't have access to the Items class yet
	mycharacter->setArmorClass(11 + mycharacter->getDexterityModifier());

	//Attack bonus, is based on strength modifier, dexterity modifier, and level
	//In the default constructor, level is 0 therefore attack bonus is just based on strength + dexterity modifiers
	mycharacter->setAttackBonus(mycharacter->getStrengthModifier() + mycharacter->getDexterityModifier());

	//Damage bonus, based on strength modifier
	mycharacter->setDamageBonus(mycharacter->getStrengthModifier());
}