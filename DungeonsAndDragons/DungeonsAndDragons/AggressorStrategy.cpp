//! @file 
//! @brief Implementation file for the AggressorStrategy class  
//!
#include "AggressorStrategy.h"
#include "Character.h"
#include "Combat.h"
#include <iostream>
#include "Dice.h"

using namespace std;

//! Method to execute the Aggressor strategy
//! @param map : Pointer to a map
//! @param enemyCharacter : Pointer to an enemy character
//! @param targetCharacter : Pointer to the character the enemy is targeting
void AggressorStrategy::execute(Map* map, MapObject* enemyCharacter, MapObject* targetCharacter) {
	cout << "*** ENEMY'S TURN ***" << endl;
	int numOfAttack = 1;
	int numOfMoves = 6;
	// Get position of the enemy character
	int i = static_cast<Character*>(enemyCharacter)->getMapY();
	int j = static_cast<Character*>(enemyCharacter)->getMapX();
	int mapX = map->getMapX();
	int mapY = map->getMapY();
	bool done = false;
	bool availablePath = false;
	bool nearby = nearby = map->verifyNearbyCharacter(targetCharacter, j, i);
	while (!done) {
		// If player is not nearby, it will move towards it during combat mode only.
		while (!nearby) {
			while (numOfMoves > 0 || numOfAttack > 0) {
				i = enemyCharacter->getMapY();
				j = enemyCharacter->getMapX();
				nearby = map->verifyNearbyCharacter(targetCharacter, j, i);
				if (nearby)
					break;
				//Combat::moveAlongPath(map, enemyCharacter, targetCharacter);
				numOfMoves--;
				if (numOfMoves < 0)
					numOfAttack--;
			}
			if (numOfMoves <= 0 && numOfAttack <= 0) {
				done = true;
				break;
			}
		}
		if (numOfAttack > 0) {
			cout << "Enemy is attacking!" << endl;
			int attackRoll;
			int damageRoll;
			int targetArmorClass;
			int targetHP = static_cast<Character*>(targetCharacter)->getHitPoints(); // get current HPs from target

			// Attack roll
			attackRoll = Dice::roll("1d20");
			// If the d20 roll for attack is 1, the attack misses regardless of target's armor class
			if (attackRoll == 1) {
				cout << "Rolled a " << attackRoll << "!" << endl;
				cout << "Attack automatically missed!" << endl;
			}
			// If the d20 roll for attack is 20, the attack hits regardless of target's armor class
			else if (attackRoll == 20) {
				cout << "Rolled a " << attackRoll << "!" << endl;
				cout << "Critical Hit!" << endl;
				// Own implementation of the dice... Roll twice
				damageRoll = Dice::roll("2d20");
				damageRoll += static_cast<Character*>(enemyCharacter)->getDamageBonus();
				cout << "Total damage roll: " << damageRoll << endl;
				targetHP -= damageRoll;
				if (targetHP <= 0) {
					static_cast<Character*>(targetCharacter)->setCurrentHitPoints(targetHP);
					break;
				}
				cout << "Player's Current Hit Point: " << targetHP << endl;
				static_cast<Character*>(targetCharacter)->setCurrentHitPoints(targetHP); // remove HPs from target
			}
			else {
				attackRoll += static_cast<Character*>(enemyCharacter)->getAttackBonus();
				targetArmorClass = static_cast<Character*>(targetCharacter)->getArmorClass();
				if (attackRoll > targetArmorClass) {
					damageRoll = Dice::roll("1d20") + static_cast<Character*>(enemyCharacter)->getDamageBonus();
					cout << "Total damage roll: " << damageRoll << endl;
					targetHP -= damageRoll;
					if (targetHP <= 0) {
						static_cast<Character*>(targetCharacter)->setCurrentHitPoints(targetHP);
						break;
					}
					cout << "Player's Current Hit Point: " << targetHP << endl;
					static_cast<Character*>(targetCharacter)->setCurrentHitPoints(targetHP); // remove HPs from target
				}
				else
				{
					cout << "Attack missed! Attack Roll is smaller than player's Armor Class" << endl;
				}
			}
			numOfAttack--;
		}
		else {
			done = true;
			break;
		}
	}
	cout << "*** ENEMY FINISHED A TURN ***\n" << endl;
}