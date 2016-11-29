//! @file 
//! @brief Header file for the Character class  
//!
//! Game rules explained:
//! - To calculate character's ability scores, 4 six-sided dice are rolled, where the highest 3 are kept and summed.
//! - This is repeated 5 more times to have a total of 6 scores. They are distributed in the character's ability scores based on the priorities for fighter class. 
//! - The priority is: Strength, Dexterity, Constitution, Charisma, Intelligence and Wisdom.
//! - Then, to calculate the ability modifiers, we add 10 to the ability scores, divide by 2, and round down.
//!	- Initial hit points are found by having 10 summed with the character's calculated constitution modifier.
//!	- At later levels, hit points are found by adding a d10 dice roll and the character's constitution modifier to the previous hp.
//!	- Armor class depends on the type of armor worn, but for the constructor it is 11 + dexterity modifier.
//! - Attack bonus depends on level, but for the constructor, attack bonus is just strength + dexterity modifiers.
//! - Damage bonus is also dependant on level, but initially is is simply the strength modifier.
//!
//! Design of assignment:
//! - The design of this program is that it is constituted of a Character header file.
//! - It also has the Character cpp file which is the class definition of the Character class. 
//! - Character objects will be initialized by default to be of the fighter class, for the sake of the project.
//! - There are also 2 test files, the CharacterTest header, and the corresponding CharacterTest cpp file.
//! - They are the unit tests which validate major test cases of the functionalities of the program using CPPUnit framework.
//! - Finally, there is the main function which runs either the test cases, or the driver to demonstrate the program.
//! - (By default I have commented out the unit tests main() function, simply uncomment them and comment the driver to view the unit tests).
//! - Character and Subject classes have been added for assignment 2, which are the abstract classes that make up the observer design pattern.
//! - As Character is the subject for this assignment, it inherits from the Subject class, while CharacterObserver, the observer class created, inherits from Observer class.
//! 
//! Libraries used:
//! - I have used many libraries to boost the performance and functionality of the program.
//! - The iostream library is used to allow output to the console for viewing purposes.
//! - The ctime and windows.h libraries were used to access the machine real time for the randomizer functions optimization.
//! - math.h was used for the simple mathematics functions to avoid unecessary coding, such as the floor() function to round down a double.
//! - string was included because objects of type string were used in the program to display the equipped items of the character.
//! - And finally, for the driver, some CPPUnit libraries were included to perform and run the test cases

#pragma once
#include "Subject.h"
#include "MapObject.h"
#include "ItemContainer.h"
#include "Strategy.h"
#include <string>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
//! Class that implements a character 
class Character : public Subject, public MapObject
{
public:
	Character();
	Character(char, int, int, int, int, int, int);
	~Character();
	bool validateNewCharacter();
	void getDamaged(int);
	int getHitPoints();
	int getMaxHitPoints();
	int rollSixSidedDie();
	int rollTenSidedDie();
	int generateAbilityModifier(int);
	void calculateAbilityScores(int[]);
	void assignAbilityModifiers(int[]);
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
	int getArmorClass();
	int getAttackBonus();
	int getDamageBonus();
	string getWornItemName(string);
	void setLevel(int);
	void setCurrentHitPoints(int);
	void setTotalHitPoints(int);
	void setStrengthScore(int);
	void setDexterityScore(int);
	void setConstitutionScore(int);
	void setCharismaScore(int);
	void setIntelligenceScore(int);
	void setWisdomScore(int);
	void setStrengthModifier(int);
	void setDexterityModifier(int);
	void setConstitutionModifier(int);
	void setCharismaModifier(int);
	void setIntelligenceModifier(int);
	void setWisdomModifier(int);
	int getNumberOfAttacks();
	void setArmorClass(int);
	void setAttackBonus(int);
	void setDamageBonus(int);
	void setNumberOfAttacks(int);
	void setMaxHitPoints(int);
	void levelUp();
	void displayEquipment();
	void displayBackpack();
	bool validateAbilityModifiers();
	void setType(char);
	void setCharacterName(string);
	void equipItem(int);
	void unequipItem(int);
	int levelHitPoints();
	void chooseScoresOnLevelUp();
	void userChoiceLevelUp();
	string getCharacterName();
	ItemContainer* getEquippedItems();
	ItemContainer* getBackpack();
	void setStrategy(Strategy* strategy);
	void executeStrategy(Map* map, MapObject* first, MapObject* second);
private:
	int abilityScores[6];
	int abilityModifiers[6];
	int abilityHolder[6];
	int modifierHolder[6];
	int currentHitPoints;
	int maxHitPoints;
	int currentLevel;
	int armorClass;
	int attackBonus;
	int damageBonus;
	int numberofAttacks;
	string characterName = "";
	ItemContainer* equipped;
	ItemContainer* backpack;
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<MapObject>(*this);
		ar & abilityScores;
		ar & objectType;
		ar & equipped;
		ar & backpack;
		ar & currentLevel;
		ar & characterName;
		ar & maxHitPoints;
	}
};

