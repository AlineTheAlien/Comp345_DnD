#include "stdafx.h"
#include "FriendlyBuilder.h"


FriendlyBuilder::FriendlyBuilder()
{
}


FriendlyBuilder::~FriendlyBuilder()
{
}

//! Method that prioritizes ability scores based on the score priority for friendly NPC characters
void FriendlyBuilder::buildAbilityScores() {
	//for the sake of this project, friendly NPCs are created with highest ability score
	//being strength, followed by dexterity, constitution, charisma, intelligence, and wisdom.
	int temp[6];
	int modifiers[6];

	mycharacter->setCharacterName("Friendly NPC");

	mycharacter->setType('F'); //Enemy type character

	mycharacter->calculateAbilityScores(temp);

	sort(temp, temp + 6, greater<int>());

	mycharacter->setStrengthScore(temp[0]);
	mycharacter->setDexterityScore(temp[1]);
	mycharacter->setConstitutionScore(temp[2]);
	mycharacter->setCharismaScore(temp[3]);
	mycharacter->setIntelligenceScore(temp[4]);
	mycharacter->setWisdomScore(temp[5]);

	mycharacter->assignAbilityModifiers(modifiers);

	sort(modifiers, modifiers + 6, greater<int>());

	mycharacter->setStrengthModifier(modifiers[0]);
	mycharacter->setDexterityModifier(modifiers[1]);
	mycharacter->setConstitutionModifier(modifiers[2]);
	mycharacter->setCharismaModifier(modifiers[3]);
	mycharacter->setIntelligenceModifier(modifiers[4]);
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
