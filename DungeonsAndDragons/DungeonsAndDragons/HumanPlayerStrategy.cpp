//! @file 
//! @brief Implementation file for the HumanPlayerStrategy class  
//!
#include "HumanPlayerStrategy.h"
#include "Character.h"
#include <iostream>

using namespace std;
//! Method to execute the Human Player strategy
//! @param map : Pointer to a map
//! @param player: Pointer to a player character
//! @param targetCharacter : Pointer to the character the enemy is targeting
void HumanPlayerStrategy::execute(Map* map, MapObject* player, MapObject* targetCharacter) {
	// Max number of move is 6 grids. According to the rules, if game is grid-based and a fighter character has a speed of 30ft,
	// and one grid is 5ft, then the character can only move up to a maximum of 6 grids.
	int numOfMoves = 6;

	// Player can only attack once and do other moves until boolean done is true
	int numOfAttack = 1;
	int choice = 1;
	bool done = false;
	int iNew = 0;
	int jNew = 0;
	cout << "*** PLAYER'S TURN ***" << endl;
	// While there are still actions remaining
	while (!done) {
		// Get position of player
		int i = static_cast<Character*>(player)->getMapY();
		int j = static_cast<Character*>(player)->getMapX();
		cout << "What would you like to do?\n1- Move\n2- Attack\n3- Other (Free actions)\n4- Done" << endl;
		cin >> choice;
		cout << endl;
		MapObject* taken = NULL;
		if (choice == 1) {
			if (numOfMoves > 0 || numOfAttack > 0) {
				cout << "Where would you like to move?\n1- Left\n2- Right\n3- Top\n4- Bottom" << endl;
				map->showMap();
				cin >> choice;
				cout << endl;
				// Move left
				if (choice == 1) {
					iNew = i;
					jNew = j - 1;
				}
				// Move right
				if (choice == 2) {
					iNew = i;
					jNew = j + 1;
				}
				// Move up
				if (choice == 3) {
					iNew = i - 1;
					jNew = j;
				}
				// Move down
				if (choice == 4) {
					iNew = i + 1;
					jNew = j;
				}
				taken = map->getTile(jNew, iNew);
				// If the position is not taken
				if (taken == NULL) {
					map->setPlayer(jNew, iNew, player);
					map->showMap();
					numOfMoves--;
					// If player does not want to attack and instead want to move, it cannot attack
					if (numOfMoves <= 0 && numOfAttack > 0) {
						numOfAttack--;
					}
				}
				else
					cout << "You cannot move to this position as it is occupied." << endl;
			}
			else
			{
				cout << "You have reached the maximum number of moves. You may only perform free actions or complete the turn." << endl;
			}
			
		}
		else if (choice == 2) {
			if (numOfAttack > 0) {
				// To check if enemy is nearby
				bool nearby = false;
				// Get position of the player
				int i = static_cast<Character*>(player)->getMapY();
				int j = static_cast<Character*>(player)->getMapX();
				// Verify if the ennemy is nearby
				nearby = map->verifyNearbyCharacter(targetCharacter, j, i);

				if (nearby)
				{
					cout << "Attacking enemy!" << endl;
					int attackRoll;
					int damageRoll;
					int targetArmorClass;
					int targetHP = static_cast<Character*>(targetCharacter)->getHP(); // get current HPs from target

					// Attack roll
					attackRoll = static_cast<Character*>(player)->roll20d();
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
						damageRoll = static_cast<Character*>(player)->roll20d();
						damageRoll += static_cast<Character*>(player)->roll20d() + static_cast<Character*>(player)->getDamageBonus();
						cout << "Total damage roll: " << damageRoll << endl;
						targetHP -= damageRoll;
						if (targetHP <= 0) {
							static_cast<Character*>(targetCharacter)->setCurrentHP(targetHP);
							done = true;
							break;
						}
						cout << "Enemy Current Hit Point: " << targetHP << endl;
						static_cast<Character*>(targetCharacter)->setCurrentHP(targetHP); // remove HPs from target
					}
					else {
						attackRoll += static_cast<Character*>(player)->getAttackBonus();
						targetArmorClass = static_cast<Character*>(targetCharacter)->getArmorClass();
						if (attackRoll > targetArmorClass) {
							damageRoll = static_cast<Character*>(player)->roll20d() + static_cast<Character*>(player)->getDamageBonus();
							cout << "Total damage roll: " << damageRoll << endl;
							targetHP -= damageRoll;
							if (targetHP <= 0) {
								static_cast<Character*>(targetCharacter)->setCurrentHP(targetHP);
								done = true;
								break;
							}
							cout << "Enemy Current Hit Point: " << targetHP << endl;
							static_cast<Character*>(targetCharacter)->setCurrentHP(targetHP); // remove HPs from target
						}
						else
						{
							cout << "Attack missed! Attack Roll is smaller than target's Armor Class" << endl;
						}
					}
					numOfAttack--;
				}
				else {
					cout << "Enemy is not within range. Try something else." << endl;
				}

			}
			else {
				cout << "You cannot perform an attack. (Either you have used up all actions in movement, or you already attacked once). Use another action." << endl;
			}
		}
		else if (choice == 3) {
			cout << "Performing free actions... (equip items, take a potion, etc.) Can be done as many time as player wants." << endl;
		}
		else if (choice == 4) {
			done = true;
			cout << "*** PLAYER FINISHED A TURN ***\n" << endl;
			break;
		}
	}
}