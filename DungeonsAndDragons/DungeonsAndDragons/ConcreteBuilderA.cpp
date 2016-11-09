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

	// For the purpose of the assignment, the character is a fighter and thus a d10 hit dice was used
	// to get a number that will be added or removed to the total and current hit points
	int sum = 0;
	for (int i = 0; i < playerLevel; i++) {
		sum += (rand() % 10 + 1);
	}

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

	// Create enemy object
	MapObject* newCharacter = new Character(type, playerLevel, currentHP, totalHP, abilityScores[0], abilityScores[1], abilityScores[2], abilityScores[3], abilityScores[4], abilityScores[5]);

	// Place the enemy on the map
	map->setTile(j, i, newCharacter);
}

void ConcreteBuilderA::buildContainer(int j, int i) {

}