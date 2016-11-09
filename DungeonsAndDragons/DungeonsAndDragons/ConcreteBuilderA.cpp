#pragma once

#include "ConcreteBuilderA.h"
#include "Character.h"
#include <fstream>
#include <iostream>
#include <string>

void ConcreteBuilderA::buildCharacter(char type, int j, int i, MapObject* character) {
	// Get all attributes of the enemy
	int level, currentHP, totalHP, str, dex, con, intel, wis, cha;

	level = static_cast<Character*>(character)->getCurrentLevel();
	currentHP = static_cast<Character*>(character)->getHitPoints();
	totalHP = static_cast<Character*>(character)->getMaxHitPoints();
	str= static_cast<Character*>(character)->getStrengthScore();
	dex = static_cast<Character*>(character)->getDexterityScore();
	con = static_cast<Character*>(character)->getConstitutionScore();
	intel = static_cast<Character*>(character)->getIntelligenceScore();
	wis = static_cast<Character*>(character)->getWisdomScore();
	cha = static_cast<Character*>(character)->getCharismaScore();

	// Every time a character levels up, we assume the character gets two ability scores to be added any of to the current ability scores
	int levelDifference = abs(playerLevel - level);
	int bonus = levelDifference * 2;
	int abilityScores[6] = { str, dex, con, intel, wis, cha };

	// Since the character is a fighter, a d10 hit dice was used
	// to get a number that will be added or removed to the total and current hit points
	int sum = 0;
	srand(static_cast<unsigned int>(time(0)));
	string dice = to_string(playerLevel) + "d10";
	sum = Dice::roll(dice);
	cout << "Sum is " << sum << endl;

	// After getting the ability scores bonus that must be assigned, randomly assign to one of the abilities.
	// If the player level is higher than the current enemy level, it will increase some ability scores.
	// If the player level is lower than the current enemy level, it will decrease some ability scores.
	int randIndex;
	if (playerLevel > level) {
		while (bonus != 0) {
			randIndex = rand() % 6;
			// Max scores for an ability is 30, if it reaches 30, it won't do anything
			if (abilityScores[randIndex] != 30) {
				abilityScores[randIndex] += 1;
				bonus--;
			}
		}
	}
	else if (playerLevel < level) {
		while (bonus != 0) {
			randIndex = rand() % 6;
			if (abilityScores[randIndex] != 30) {
				abilityScores[randIndex] -= 1;
				bonus--;
			}
		}
	}

	// Calculate the difference between old and new constitution scores to figure out how many points must be added or removed from the hit points
	int differenceInConstitution = abs(abilityScores[2] - con);

	// Adjust the current and total hit points to the player's level
	if (playerLevel > level) {
		currentHP += (differenceInConstitution + sum);
		totalHP += (differenceInConstitution + sum);
	}
	if (playerLevel < level) {
		currentHP -= (differenceInConstitution + sum);
		totalHP -= (differenceInConstitution + sum);
	}
	// Set all the attributes of the character
	character->setObjectType('E');
	static_cast<Character*>(character)->setLevel(playerLevel);
	static_cast<Character*>(character)->setCurrentHitPoints(currentHP);
	static_cast<Character*>(character)->setTotalHitPoints(totalHP);
	static_cast<Character*>(character)->setStrengthScore(abilityScores[0]);
	static_cast<Character*>(character)->setDexterityScore(abilityScores[1]);
	static_cast<Character*>(character)->setConstitutionScore(abilityScores[2]);
	static_cast<Character*>(character)->setIntelligenceScore(abilityScores[3]);
	static_cast<Character*>(character)->setWisdomScore(abilityScores[4]);
	static_cast<Character*>(character)->setCharismaScore(abilityScores[5]);
}

void ConcreteBuilderA::buildContainer(int j, int i) {

}