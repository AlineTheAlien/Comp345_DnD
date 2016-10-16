//! @file 
//! @brief Header file for the Character class  
//!

#pragma once
#include <string>

//! Class that implements a character 
class Character
{
public:
	Character();
	Character(std::string[], int, long, int, int, int, int, int, int);
	bool validateNewCharacter();
	void getDamaged(int);
	int getHitPoints();
	int rollSixSidedDie();
	int generateAbilityModifier(int);
	void calculateAbilityScores(int[]);
	void assignAbilityModifiers(int[]);
	int rollTenSidedDie();
	void displayCharacterInfo();
	int getStrengthScore();
	int getDexterityScore();
	int getConstitutionScore();
	int getCharismaScore();
	int getIntelligenceScore();
	int getWisdomScore();
	int getStrengthModifier();
	int getDexterityModifier();
	int getConstitutionModifier();
	int getCharismaModifier();
	int getIntelligenceModifier();
	int getWisdomModifier();
	int getCurrentLevel();
	int getCurrentExperiencePoints();
	int getArmorClass();
	int getAttackBonus();
	int getDamageBonus();
	void levelUp();
	void displayEquipment();
	std::string getArmor();
	std::string getShield();
	std::string getWeapon();
	std::string getBoots();
	std::string getRing();
	std::string getHelmet();


private:
	int abilityScores[6];
	int abilityModifiers[6];
	int currentHitPoints;
	int currentLevel;
	long currentExperiencePoints;
	int armorClass;
	std::string equippedItems[6];
	int attackBonus;
	int damageBonus;
};

