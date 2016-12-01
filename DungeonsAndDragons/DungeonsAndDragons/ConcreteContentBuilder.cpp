//! @file 
//! @brief Implementation file for a Concrete Content Builder class
//
#pragma once

#include "ConcreteContentBuilder.h"
#include "Character.h"
#include <fstream>
#include <iostream>
#include <string>
#include "HumanPlayerStrategy.h"
#include "AggressorStrategy.h"
#include "FriendlyStrategy.h"

void ConcreteContentBuilder::buildCharacter(char type, int j, int i, MapObject* character) {
	// Get all attributes of the enemy
	int level, currentHP, totalHP, str, dex, con, intel, wis, cha;
	int strModif, dexModif, conModif, intelModif, wisModif, chaModif;

	level = static_cast<Character*>(character)->getCurrentLevel();
	currentHP = static_cast<Character*>(character)->getHitPoints();
	totalHP = static_cast<Character*>(character)->getMaxHitPoints();
	str = static_cast<Character*>(character)->getStrengthScore();
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
	string dice = to_string(playerLevel) + "d6";
	sum = Dice::roll(dice);

	// After getting the ability scores bonus that must be assigned, randomly assign to one of the abilities.
	// If the player level is higher than the current enemy level, it will increase some ability scores.
	// If the player level is lower than the current enemy level, it will decrease some ability scores.
	int randIndex;
	if (playerLevel > level) {
		while (bonus != 0) {
			randIndex = rand() % 6; // There are six ability scores inside the array, randomly get an index
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

	level = static_cast<Character*>(character)->getCurrentLevel();
	currentHP = static_cast<Character*>(character)->getHitPoints();
	totalHP = static_cast<Character*>(character)->getMaxHitPoints();
	str = static_cast<Character*>(character)->getStrengthScore();
	dex = static_cast<Character*>(character)->getDexterityScore();
	con = static_cast<Character*>(character)->getConstitutionScore();
	intel = static_cast<Character*>(character)->getIntelligenceScore();
	wis = static_cast<Character*>(character)->getWisdomScore();
	cha = static_cast<Character*>(character)->getCharismaScore();

	// Set all the attributes of the character
	character->setObjectType(type);
	static_cast<Character*>(character)->setLevel(playerLevel);
	level = static_cast<Character*>(character)->getCurrentLevel();
	static_cast<Character*>(character)->setCurrentHitPoints(currentHP*0.6);
	currentHP = static_cast<Character*>(character)->getHitPoints();
	static_cast<Character*>(character)->setTotalHitPoints(totalHP*0.6);
	totalHP = static_cast<Character*>(character)->getMaxHitPoints();
	static_cast<Character*>(character)->setStrengthScore(abilityScores[0]*0.6);
	str = static_cast<Character*>(character)->getStrengthScore();
	static_cast<Character*>(character)->setDexterityScore(abilityScores[1]*0.8);
	dex = static_cast<Character*>(character)->getDexterityScore();
	static_cast<Character*>(character)->setConstitutionScore(abilityScores[2] * 0.6);
	con = static_cast<Character*>(character)->getConstitutionScore();
	static_cast<Character*>(character)->setIntelligenceScore(abilityScores[3] * 0.6);
	intel = static_cast<Character*>(character)->getIntelligenceScore();
	static_cast<Character*>(character)->setWisdomScore(abilityScores[4] * 0.6);
	wis = static_cast<Character*>(character)->getWisdomScore();
	static_cast<Character*>(character)->setCharismaScore(abilityScores[5] * 0.6);
	cha = static_cast<Character*>(character)->getCharismaScore();
	strModif = static_cast<Character*>(character)->generateAbilityModifier(str * 0.6);
	dexModif = static_cast<Character*>(character)->generateAbilityModifier(dex * 0.6);
	conModif = static_cast<Character*>(character)->generateAbilityModifier(con * 0.6);
	intelModif = static_cast<Character*>(character)->generateAbilityModifier(intel * 0.6);
	wisModif = static_cast<Character*>(character)->generateAbilityModifier(wis * 0.6);
	chaModif = static_cast<Character*>(character)->generateAbilityModifier(cha * 0.6);
	static_cast<Character*>(character)->setStrengthModifier(strModif*0.6);
	static_cast<Character*>(character)->setDexterityModifier(dexModif*0.6);
	static_cast<Character*>(character)->setConstitutionModifier(conModif*0.6);
	static_cast<Character*>(character)->setIntelligenceModifier(intelModif*0.6);
	static_cast<Character*>(character)->setWisdomModifier(wisModif*0.6);
	static_cast<Character*>(character)->setCharismaModifier(chaModif*0.6);

	if (type == 'E') {
		static_cast<Character*>(character)->setStrategy(new AggressorStrategy());
	}
	if (type == 'F')
	{
		static_cast<Character*>(character)->setStrategy(new FriendlyStrategy());
	}
	map->setTile(j, i, character);
}

//! Method to adapt a chest level to the player's level
//! @param j : Position j of the container
//! @param i : Position i of the containe
//! @param items : Reference to a vector of pointers to items
void ConcreteContentBuilder::buildContainer(int j, int i, vector<Item*> &items) {

	int currentTotalBonus = 0;
	int maxNumBonus = playerLevel + 1; // For demo purpose, we decided that max bonus number for each level is the player level + 1
	int numOfItems = items.size();
	vector<Enhancement> enh;
	// Get the total number of bonus currently inside chest
	for (int i = 0; i < numOfItems; i++) {
		enh = (items[i]->getEnhancements());
		for (int i = 0; i < enh.size(); i++) {
			currentTotalBonus += enh[i].getBonus();
		}
	}

	int scoresToAdd = maxNumBonus - currentTotalBonus;
	int randItemIndex;
	int randEnhancementIndex;
	int bonus; // Bonus of one enhancement type
	int totalBonus; // Total bonus to set to a specified enhancement types
	int numOfEnhancements;
	// If the difference is positive, there are scores to add to any of the enhancement type
	if (scoresToAdd > 0) {
		while (scoresToAdd != 0) {
			randItemIndex = rand() % numOfItems; // Get the index of a random item
			enh = items[randItemIndex]->getEnhancements(); // Store the item's enhancements in enh
			numOfEnhancements = enh.size(); // Get the number of enhancements the item has
			if (numOfEnhancements != 0) {
				randEnhancementIndex = rand() % numOfEnhancements; // Get the index of a random enhancement
				bonus = enh[randEnhancementIndex].getBonus();
				totalBonus = bonus + 1;
				if (totalBonus <= 5 && totalBonus >=0) {
					items[randItemIndex]->setEnhancementBonus(randEnhancementIndex, totalBonus);
					scoresToAdd--;
				}
			}
		}
	}
	else {
		while (scoresToAdd != 0) {
			randItemIndex = rand() % numOfItems; // Get the index of a random item
			enh = items[randItemIndex]->getEnhancements(); // Store the item's enhancements in enh
			numOfEnhancements = enh.size(); // Get the number of enhancements the item has
			if (numOfEnhancements != 0) {
				randEnhancementIndex = rand() % numOfEnhancements; // Get the index of a random enhancement
				bonus = enh[randEnhancementIndex].getBonus();
				totalBonus = bonus - 1;
				if (totalBonus >= 0 && totalBonus <= 5) {
					items[randItemIndex]->setEnhancementBonus(randEnhancementIndex, totalBonus);
					scoresToAdd++;
				}
			}
		}
	}
}