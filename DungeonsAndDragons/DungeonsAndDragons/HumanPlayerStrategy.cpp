//! @file 
//! @brief Implementation file for the HumanPlayerStrategy class  
//!
#include "HumanPlayerStrategy.h"
#include "Character.h"
#include <iostream>
#include "Dice.h"
#include "Play.h"
#include "GameLogger.h"
using namespace std;

bool HumanPlayerStrategy::logHumanPlayer = true;

//! Method to execute the Human Player strategy
//! @param map : Pointer to a map
//! @param player: Pointer to a player character
//! @param targetCharacter : Pointer to the character the enemy is targeting
void HumanPlayerStrategy::execute(Map* map, MapObject* player, MapObject* targetCharacter) {
	// Max number of move is 6 grids. According to the rules, if game is grid-based and a fighter character has a speed of 30ft,
	// and one grid is 5ft, then the character can only move up to a maximum of 6 grids.
	int numOfMoves = 6;
	int numOfAttacks = static_cast<Character*>(targetCharacter)->getNumberOfAttacks();
	int choice = 1;
	bool done = false;
	int iNew = 0;
	int jNew = 0;
	string s = "";
	if (logHumanPlayer == true) {
		cout << "*** PLAYER'S TURN ***" << endl;
		s += "*** PLAYER'S TURN ***\n";
	}
	// While there are still actions remaining
	while (!done) {
		// Get position of player
		int i = static_cast<Character*>(player)->getMapY();
		int j = static_cast<Character*>(player)->getMapX();

		cout << "What would you like to do?\n1- Move\n2- Attack\n3- Modify Equipment\n4- Done" << endl;
		cin >> choice;
		cout << endl;
		MapObject* tile = NULL;

		if (choice == 1) {
			if (numOfMoves > 0 || numOfAttacks > 0) {
				cout << "Where would you like to move?\n1- Left\n2- Right\n3- Top\n4- Bottom" << endl;
				map->showMap();
				cin >> choice;
				cout << endl;
				MapObject* tile = NULL;

				// Move left
				if (choice == 1) {
					if (j - 1 >= 0) {
						iNew = i;
						jNew = j - 1;
						tile = map->getObjectTile(jNew, iNew);
					}
					else
					{
						cout << "Cannot move there. You will be out of the map." << endl;
					}
				}
				// Move right
				if (choice == 2) {
					if (j + 1 < map->getMapX()) {
						iNew = i;
						jNew = j + 1;
						tile = map->getObjectTile(jNew, iNew);
					}
					else
					{
						cout << "Cannot move there. You will be out of the map." << endl;
					}
				}
				// Move up
				if (choice == 3) {
					if (i - 1 >= 0) {
						iNew = i - 1;
						jNew = j;
						tile = map->getObjectTile(jNew, iNew);
					}
					else
					{
						cout << "Cannot move there. You will be out of the map." << endl;
					}
				}
				// Move down
				if (choice == 4) {
					if (i + 1 < map->getMapY()) {
						iNew = i + 1;
						jNew = j;
						tile = map->getObjectTile(jNew, iNew);
					}
					else
					{
						cout << "Cannot move there. You will be out of the map." << endl;
					}
				}

				if (tile == NULL) {
					map->movePlayer(jNew, iNew, player);
					map->showMap();
					numOfMoves--;
					// If player does not want to attack and instead want to move, it cannot attack
					if (numOfMoves <= 0 && numOfAttacks > 0) {
						numOfAttacks--;
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
			if (numOfAttacks > 0) {
				// To check if enemy is nearby
				bool nearby = false;
				// Get position of the player
				int i = static_cast<Character*>(player)->getMapY();
				int j = static_cast<Character*>(player)->getMapX();
				// Verify if the ennemy is nearby
				nearby = map->verifyNearbyCharacter(targetCharacter, j, i);

				if (nearby)
				{
					if (logHumanPlayer == true) {
						cout << "Attacking enemy!" << endl;
						s += "Attacking enemy!\n";
					}
					int attackRoll;
					int damageRoll;
					int targetArmorClass;
					int targetHP = static_cast<Character*>(targetCharacter)->getHitPoints(); // get current HPs from target
					int maxTargetHP = static_cast<Character*>(targetCharacter)->getMaxHitPoints(); // get max HPs from target

					// Attack roll : roll 1d20 die
					attackRoll = Dice::roll("1d20");
					// If the d20 roll for attack is 1, the attack misses regardless of target's armor class
					if (attackRoll == 1) {
						if (logHumanPlayer == true) {
							cout << "Rolled a " << attackRoll << "!" << endl;
							s += "Rolled a " + to_string(attackRoll) + "!\n";
							cout << "Attack automatically missed!" << endl;
							s += "Attack automatically missed!\n";
						}
					}
					// If the d20 roll for attack is 20, the attack hits regardless of target's armor class
					else if (attackRoll == 20) {
						if (logHumanPlayer == true) {
							cout << "Rolled a " << attackRoll << "!" << endl;
							s += "Rolled a " + to_string(attackRoll) + "!\n";
							cout << "Critical Hit!" << endl;
							s += "Critical Hit!\n";
						}
						// Damage roll: Since it's a critical hit, it will roll a d20 twice: roll 2d20
						damageRoll = Dice::roll("2d20");
						damageRoll += static_cast<Character*>(player)->getDamageBonus();
						if (logHumanPlayer == true) {
							cout << "Total damage roll: " << damageRoll << endl;
							s += "Total damage roll: " + to_string(damageRoll) + "\n";
						}
						targetHP -= damageRoll;
						if (targetHP <= 0) {
							static_cast<Character*>(targetCharacter)->setCurrentHitPoints(targetHP);
							done = true;
							break;
						}
						if (logHumanPlayer == true) {
							cout << "Enemy Current Hit Points: " << targetHP << "/" << maxTargetHP << endl;
							s += "Enemy Current Hit Points: " + to_string(targetHP) + "/" + to_string(maxTargetHP) + "\n";
						}
						static_cast<Character*>(targetCharacter)->setCurrentHitPoints(targetHP); // remove HPs from target
					}
					else {
						attackRoll += static_cast<Character*>(player)->getAttackBonus();
						targetArmorClass = static_cast<Character*>(targetCharacter)->getArmorClass();
						if (attackRoll > targetArmorClass) {
							damageRoll = Dice::roll("1d20") + static_cast<Character*>(player)->getDamageBonus();
							if (logHumanPlayer == true) {
								cout << "Total damage roll: " << damageRoll << endl;
								s += "Total damage roll: " + to_string(damageRoll) + "\n";
							}
							targetHP -= damageRoll;
							if (targetHP <= 0) {
								static_cast<Character*>(targetCharacter)->setCurrentHitPoints(targetHP);
								done = true;
								break;
							}
							if (logHumanPlayer == true) {
								cout << "Enemy Current Hit Points: " << targetHP << "/" << maxTargetHP << endl;
								s += "Enemy Current Hit Points: " + to_string(targetHP) + "/" + to_string(maxTargetHP) + "\n";
							}
							static_cast<Character*>(targetCharacter)->setCurrentHitPoints(targetHP); // remove HPs from target
						}
						else
						{
							cout << "Attack missed! Attack Roll is smaller than target's Armor Class" << endl;
						}
					}
					numOfAttacks--;
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
			cin >> choice;
			cout << endl;

			int itemChoice;
			int size = static_cast<Character*>(player)->getBackpack()->getItems().size();
			bool isValid = false;
			do {
				cout << "Press 1 to equip items, or press 2 to unequip your current items. Enter -1 to exit" << endl;
				cin >> choice;
				if (choice == 1 || choice == 2)
					isValid = true;
				if (choice == -1)
					return;
			} while (isValid == false);

			if (choice == 1)
			{
				do {
					static_cast<Character*>(player)->displayBackpack();
					cout << "Which index item do you want to equip? Enter -1 to exit" << endl;
					cin >> itemChoice;
					if (itemChoice == -1)
						return;
				} while (itemChoice > size || itemChoice < 0);
				static_cast<Character*>(player)->equipItem(itemChoice);
				static_cast<Character*>(player)->displayBackpack();
				static_cast<Character*>(player)->displayEquipment();
			}
			else
				if (choice == 2)
				{
					do {
						static_cast<Character*>(player)->getEquippedItems()->displayItems();
						cout << "Which index item do you want to unequip? Enter -1 to exit" << endl;
						cin >> itemChoice;
						if (itemChoice == -1)
							return;
					} while (itemChoice > static_cast<Character*>(player)->getEquippedItems()->getItems().size() || itemChoice < 0);
					static_cast<Character*>(player)->unequipItem(itemChoice);
					static_cast<Character*>(player)->displayBackpack();
					static_cast<Character*>(player)->displayEquipment();
				}
		}
		else if (choice == 4) {
			done = true;
			if (logHumanPlayer == true) {
				cout << "*** PLAYER FINISHED A TURN ***\n" << endl;
				s += "*** PLAYER FINISHED A TURN ***\n";
			}
			break;
		}
	}
	GameLogger::writeToLogFile(s);
}

//! Function that sets the combat log boolean 
//! @param value: new boolean value of logHumanPlayer
void HumanPlayerStrategy::setHumanPlayerLog(bool value) {
	logHumanPlayer = value;
}