//! @file 
//! @brief Implementation file for the AggressorStrategy class  
//!
#include "AggressorStrategy.h"
#include "Character.h"
#include "Combat.h"
#include <iostream>
#include "Dice.h"
#include "GameLogger.h"

using namespace std;

bool AggressorStrategy::logAgressor = true;

//! Method to execute the Aggressor strategy
//! @param map : Pointer to a map
//! @param enemyCharacter : Pointer to an enemy character
//! @param targetCharacter : Pointer to the character the enemy is targeting
void AggressorStrategy::execute(Map* map, MapObject* enemyCharacter, MapObject* targetCharacter) {
	string s = "";
	if (logAgressor == true) {
		cout << "*** ENEMY'S TURN ***" << endl;
		s += "*** ENEMY'S TURN *** \n";
	}
	int numOfMoves = 6;
	int numOfAttacks = static_cast<Character*>(targetCharacter)->getNumberOfAttacks();
	// Get position of the enemy character
	int i = enemyCharacter->getMapY();
	int j = enemyCharacter->getMapX();
	int mapX = map->getMapX();
	int mapY = map->getMapY();
	bool done = false;
	bool availablePath = false;
	bool nearby = map->verifyNearbyCharacter(targetCharacter, j, i);
	while (!done) {
		// If player is not nearby, it will move towards it during combat mode only.
		while (!nearby) {
			while (numOfMoves > 0 || numOfAttacks > 0) {
				i = enemyCharacter->getMapY();
				j = enemyCharacter->getMapX();
				nearby = map->verifyNearbyCharacter(targetCharacter, j, i);
				if (nearby)
					break;
				Combat::moveAlongPath(map, enemyCharacter, targetCharacter);
				numOfMoves--;
				if (numOfMoves < 0)
					numOfAttacks--;
			}
			if (numOfMoves <= 0 && numOfAttacks <= 0) {
				done = true;
				break;
			}
		}
		// If it reaches here, it is nearby. It will start attacking.
		if (numOfAttacks > 0) {
			if (logAgressor == true) {
				cout << "Enemy is attacking!" << endl;
				s += "Enemy is attacking! \n";
			}
			int attackRoll;
			int damageRoll;
			int targetArmorClass;
			int targetHP = static_cast<Character*>(targetCharacter)->getHitPoints(); // get current HPs from target
			int maxTargetHP = static_cast<Character*>(targetCharacter)->getMaxHitPoints(); // get max HPs from target


			// Attack roll
			attackRoll = Dice::roll("1d20");
			// If the d20 roll for attack is 1, the attack misses regardless of target's armor class
			if (attackRoll == 1) {
				if (logAgressor == true) {
					cout << "Rolled a " << attackRoll << "!" << endl;
					s += "Rolled a " + to_string(attackRoll) + "! \n";
					cout << "Attack automatically missed!" << endl;
					s += "Attack automatically missed! \n";
				}
			}
			// If the d20 roll for attack is 20, the attack hits regardless of target's armor class
			else if (attackRoll == 20) {
				if (logAgressor == true) {
					cout << "Rolled a " << attackRoll << "!" << endl;
					s += "Rolled a " + to_string(attackRoll) + "! \n";
					cout << "Critical Hit!" << endl;
					s += "Critical Hit! \n";
				}
				// Own implementation of the dice... Roll twice
				damageRoll = Dice::roll("2d20");
				damageRoll += static_cast<Character*>(enemyCharacter)->getDamageBonus();
				if (logAgressor == true) {
					cout << "Total damage roll: " << damageRoll << endl;
					s += "Total damage roll: " + to_string(damageRoll) + " \n";
				}
				targetHP -= damageRoll;
				if (targetHP <= 0) {
					static_cast<Character*>(targetCharacter)->setCurrentHitPoints(targetHP);
					break;
				}
				if (logAgressor == true) {
					cout << "Player's Current Hit Points: " << targetHP << "/" << maxTargetHP << endl;
					s += "Player's Current Hit Points: " + to_string(targetHP) + "/" + to_string(maxTargetHP) + "\n";
				}
				static_cast<Character*>(targetCharacter)->setCurrentHitPoints(targetHP); // remove HPs from target
			}
			else {
				attackRoll += static_cast<Character*>(enemyCharacter)->getAttackBonus();
				targetArmorClass = static_cast<Character*>(targetCharacter)->getArmorClass();
				if (attackRoll > targetArmorClass) {
					damageRoll = Dice::roll("1d20") + static_cast<Character*>(enemyCharacter)->getDamageBonus();
					if (logAgressor == true) {
						cout << "Total damage roll: " << damageRoll << endl;
						s += "Total damage roll: " + to_string(damageRoll) + "\n";
					}
					targetHP -= damageRoll;
					if (targetHP <= 0) {
						static_cast<Character*>(targetCharacter)->setCurrentHitPoints(targetHP);
						break;
					}
					if (logAgressor == true) {
						cout << "Player's Current Hit Points: " << targetHP << "/" << maxTargetHP << endl;
						s += "Player's Current Hit Points: " + to_string(targetHP) + "/" + to_string(maxTargetHP) + "\n";
					}
					static_cast<Character*>(targetCharacter)->setCurrentHitPoints(targetHP); // remove HPs from target
				}
				else
				{
					if (logAgressor == true) {
						cout << "Attack missed! Attack Roll is smaller than player's Armor Class" << endl;
						s += "Attack missed! Attack Roll is smaller than player's Armor Class \n";
					}
				}
			}
			numOfAttacks--;
		}
		else {
			done = true;
			break;
		}
	}
	if (logAgressor == true) {
		cout << "*** ENEMY FINISHED A TURN ***\n" << endl;
		s += "*** ENEMY FINISHED A TURN ***\n";
	}
	GameLogger::writeToLogFile(s);
}

void AggressorStrategy::setAgressorLog(bool value) {
	logAgressor = value;
}