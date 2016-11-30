//! @file 
//! @brief Implementation file for the Combat class  
//!
#include "Combat.h"
#include "Character.h"
#include "Map.h"
#include "MapObject.h"
#include "Strategy.h"
#include "HumanPlayerStrategy.h"
#include "AggressorStrategy.h"
#include "FriendlyStrategy.h"
#include "Dice.h"
#include <iostream>
#include <ctime>

using namespace std;

//! @param player : Pointer to a player character
//! @param other : Pointer to the target character (Enemy or NPC)
//! Static class used to start the combat mechanism
void Combat::startCombat(Map* map, MapObject* player, MapObject* other) {
	cout << "Combat starting.. rolling initiative..." << endl;
	int initiativePlayer;
	int initiativeOther;
	int playerHP = static_cast<Character*>(player)->getHitPoints();
	int otherHP = static_cast<Character*>(other)->getHitPoints();

	// Initiative roll:
	// Roll 1d20 die and add dexterity modifier
	initiativePlayer = Dice::roll("1d20") + static_cast<Character*>(player)->getDexterityModifier();
	initiativeOther = Dice::roll("1d20") + static_cast<Character*>(other)->getDexterityModifier();

	// Display results
	cout << "Player's initiative roll: " << initiativePlayer << endl;
	cout << "Enemy's initiative roll: " << initiativeOther << endl;
	cout << endl;

	// If player has higher initiative roll, player will start the round, else it will be the other character
	if (initiativePlayer > initiativeOther) {
		cout << "*** PLAYER BEGINS THE ROUND ***" << endl;
		while (playerHP > 0 && otherHP > 0) {
			static_cast<Character*>(player)->executeStrategy(map, player, other); // Player uses Human Player Strategy
			otherHP = static_cast<Character*>(other)->getHitPoints();
			if (otherHP <= 0)
				break;
			static_cast<Character*>(other)->executeStrategy(map, other, player); // Enemy uses Aggressor Strategy
			playerHP = static_cast<Character*>(player)->getHitPoints();
			if (playerHP <= 0)
				break;
		}
	}
	else {
		cout << "*** ENEMY BEGINS THE ROUND ***" << endl;
		while (playerHP > 0 && otherHP > 0) {
			static_cast<Character*>(other)->executeStrategy(map, other, player); // Enemy uses Aggressor Strategy
			playerHP = static_cast<Character*>(player)->getHitPoints();
			if (playerHP <= 0)
				break;
			static_cast<Character*>(player)->executeStrategy(map, player, other); // Player uses Human Player Strategy
			otherHP = static_cast<Character*>(other)->getHitPoints();
			if (otherHP <= 0)
				break;
		}
	}
	cout << "\nCOMBAT ENDED" << endl;
}

//! Iterative method for making enemies or friendly character move towards the player.
//! @param map : Pointer to a map
//! @param character : Pointer to a character who will be moving
//! @param target : Pointer to a target character
void Combat::moveAlongPath(Map* map, MapObject* character, MapObject* target) {

	// Get position of the following character
	int i = character->getMapY();
	int j = character->getMapX();
	bool nearby = map->verifyNearbyCharacter(target, j, i);
	// Get position of the target character being followed
	int iTarget = target->getMapY();
	int jTarget = target->getMapX();

	// If the enemy is not aligned with the player either same row or same column, this block will run
	if (i != iTarget && j != jTarget) {
		if (i > iTarget && j < jTarget) {
			// move up
			if (!nearby && !(j > map->getMapX() || j < 0 || i - 1 > map->getMapY() || i - 1 < 0) && !(map->unavailableTile(j, i - 1))) {
				map->moveCharacter(j, i - 1, character);
				i = character->getMapY();
				j = character->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}
			// move right
			if (!nearby && !(j + 1 > map->getMapX() || j + 1 < 0 || i > map->getMapY() || i < 0) && !(map->unavailableTile(j + 1, i))) {
				map->moveCharacter(j + 1, i, character);
				i = character->getMapY();
				j = character->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}
		}
		else if (i > iTarget && j > jTarget) {
			// move left
			if (!nearby && !(j - 1 > map->getMapX() || j - 1 < 0 || i > map->getMapY() || i < 0) && !(map->unavailableTile(j - 1, i))) {
				map->moveCharacter(j - 1, i, character);
				i = character->getMapY();
				j = character->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}
			// move up
			if (!nearby && !(j > map->getMapX() || j < 0 || i - 1 > map->getMapY() || i - 1 < 0) && !(map->unavailableTile(j, i - 1))) {
				map->moveCharacter(j, i - 1, character);
				i = character->getMapY();
				j = character->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}
		}
		else if (i < iTarget && j < jTarget) {
			// move down
			if (!nearby && !(j > map->getMapX() || j < 0 || i + 1 > map->getMapY() || i + 1 < 0) && !(map->unavailableTile(j, i + 1))) {
				map->moveCharacter(j, i + 1, character);
				i = character->getMapY();
				j = character->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}
			// move right
			if (!nearby && !(j + 1 > map->getMapX() || j + 1 < 0 || i > map->getMapY() || i < 0) && !(map->unavailableTile(j + 1, i))) {
				map->moveCharacter(j + 1, i, character);
				i = character->getMapY();
				j = character->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}
		}
		else if (i < iTarget && j > jTarget) {
			// move down
			if (!nearby && !(j > map->getMapX() || j < 0 || i + 1 > map->getMapY() || i + 1 < 0) && !(map->unavailableTile(j, i + 1))) {
				map->moveCharacter(j, i + 1, character);
				i = character->getMapY();
				j = character->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}
			// move left
			if (!nearby && !(j - 1 > map->getMapX() || j - 1 < 0 || i > map->getMapY() || i < 0) && !(map->unavailableTile(j - 1, i))) {
				map->moveCharacter(j - 1, i, character);
				i = character->getMapY();
				j = character->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}
		}
	}

	// If the enemy is on the same column as the player, this block will run
	else if (i != iTarget && j == jTarget) {
		if (i < iTarget) {
			// move down
			if (!nearby && !(j > map->getMapX() || j < 0 || i + 1 > map->getMapY() || i + 1 < 0) && !(map->unavailableTile(j, i + 1))) {
				map->moveCharacter(j, i + 1, character);
				i = character->getMapY();
				j = character->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}
			// If blocked, move left or move right
			if (!nearby && !(j > map->getMapX() || j < 0 || i + 1 > map->getMapY() || i + 1 < 0) && (map->unavailableTile(j, i + 1))) {
				// move left
				if (!(j - 1 > map->getMapX() || j - 1 < 0 || i > map->getMapY() || i < 0) && !(map->unavailableTile(j - 1, i))) {
					map->moveCharacter(j - 1, i, character);
					i = character->getMapY();
					j = character->getMapX();
					nearby = map->verifyNearbyCharacter(target, j, i);
					map->showMap();
				}
				else if (!nearby && !(j + 1 > map->getMapX() || j + 1 < 0 || i > map->getMapY() || i < 0) && !(map->unavailableTile(j + 1, i))) {
					map->moveCharacter(j + 1, i, character);
					i = character->getMapY();
					j = character->getMapX();
					nearby = map->verifyNearbyCharacter(target, j, i);
					map->showMap();
				}
			}
		}

		if (i > iTarget) {
			// move up
			if (!nearby && !(j > map->getMapX() || j < 0 || i - 1 > map->getMapY() || i - 1 < 0) && !(map->unavailableTile(j, i - 1))) {
				map->moveCharacter(j, i - 1, character);
				i = character->getMapY();
				j = character->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}

			// If blocked, move left or move right
			if (!nearby && !(j > map->getMapX() || j < 0 || i - 1 > map->getMapY() || i - 1 < 0) && (map->unavailableTile(j, i - 1))) {
				// move left
				if (!nearby && !(j - 1 > map->getMapX() || j - 1 < 0 || i > map->getMapY() || i < 0) && !(map->unavailableTile(j - 1, i))) {
					map->moveCharacter(j - 1, i, character);
					i = character->getMapY();
					j = character->getMapX();
					nearby = map->verifyNearbyCharacter(target, j, i);
					map->showMap();
				}
				else {
					// move right
					if (!nearby && !(j + 1 > map->getMapX() || j + 1 < 0 || i > map->getMapY() || i < 0) && !(map->unavailableTile(j + 1, i))) {
						map->moveCharacter(j + 1, i, character);
						i = character->getMapY();
						j = character->getMapX();
						nearby = map->verifyNearbyCharacter(target, j, i);
						map->showMap();
					}
				}
			}
		}
	}

	// If the enemy is on the same row as the player, this block will run
	else if (i == iTarget && j != jTarget) {
		if (j < jTarget) {
			// move right
			if (!nearby && !(j + 1 > map->getMapX() || j + 1 < 0 || i > map->getMapY() || i < 0) && !(map->unavailableTile(j + 1, i))) {
				map->moveCharacter(j + 1, i, character);
				i = character->getMapY();
				j = character->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}
			// If blocked, move left or move up
			if (!nearby && !(j > map->getMapX() || j < 0 || i - 1 > map->getMapY() || i - 1 < 0) && (map->unavailableTile(j + 1, i))) {
				// move left
				if (!(j - 1 > map->getMapX() || j - 1 < 0 || i > map->getMapY() || i < 0) && !(map->unavailableTile(j - 1, i))) {
					map->moveCharacter(j - 1, i, character);
					i = character->getMapY();
					j = character->getMapX();
					nearby = map->verifyNearbyCharacter(target, j, i);
					map->showMap();
				}
				else {
					// move up
					if (!nearby && !(j > map->getMapX() || j < 0 || i - 1 > map->getMapY() || i - 1 < 0) && !(map->unavailableTile(j, i - 1))) {
						map->moveCharacter(j, i - 1, character);
						i = character->getMapY();
						j = character->getMapX();
						nearby = map->verifyNearbyCharacter(target, j, i);
						map->showMap();
					}
				}
			}
		}
		if (j > jTarget) {
			// move left
			if (!nearby && !(j - 1 > map->getMapX() || j - 1 < 0 || i > map->getMapY() || i < 0) && !(map->unavailableTile(j - 1, i))) {
				map->moveCharacter(j - 1, i, character);
				i = character->getMapY();
				j = character->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}
			// If blocked, move up
			else if (!nearby && !(j - 1 > map->getMapX() || j - 1 < 0 || i > map->getMapY() || i < 0) && (map->unavailableTile(j - 1, i))) {
				// move up
				if (!nearby && !(j > map->getMapX() || j < 0 || i - 1 > map->getMapY() || i - 1 < 0) && !(map->unavailableTile(j, i - 1))) {
					map->moveCharacter(j, i - 1, character);
					i = character->getMapY();
					j = character->getMapX();
					nearby = map->verifyNearbyCharacter(target, j, i);
					map->showMap();
				}
				else {
					// move down
					if (!nearby && !(j > map->getMapX() || j < 0 || i+1 > map->getMapY() || i+1 < 0) && !(map->unavailableTile(j, i + 1))) {
						map->moveCharacter(j, i+1, character);
						i = character->getMapY();
						j = character->getMapX();
						nearby = map->verifyNearbyCharacter(target, j, i);
						map->showMap();
					}
				}
			}
		}
	}
}

//! Method that will make NPCs in the map to execute friendly strategy and move towards the player
//! @param map : Pointer to a map object
//! @param player : Poitner to a player object
void Combat::activateNPC(Map* map, MapObject* player) {
	// Get all friendly NPCs
	vector<MapObject*> friends = map->findAllFriends();
	vector<MapObject*> enemies = map->findAllEnemies();

	// To store x,y position of the player on the map
	int x = player->getMapX();
	int y = player->getMapY();

	// When the player is free, friendly NPC walks towards player
	for (int i = 0; i < friends.size(); i++) {
		int iPos = friends[i]->getMapY();
		int jPos = friends[i]->getMapX();

		bool nearby = map->verifyNearbyCharacter(player, jPos, iPos);
		if (!nearby) {
			// Call a static method from Combat class to make the NPC move towards you
			Combat::moveAlongPath(map, friends[i], player);
			iPos = friends[i]->getMapY();
			jPos = friends[i]->getMapX();
			nearby = map->verifyNearbyCharacter(player, jPos, iPos);
		}
	}

	// When the player is free, enemies walk towards player
	for (int i = 0; i < enemies.size(); i++) {
		int iPos = enemies[i]->getMapY();
		int jPos = enemies[i]->getMapX();
		bool nearby = map->verifyNearbyCharacter(player, jPos, iPos);
		if (!nearby) {
			// Call a static method from Combat class to make the NPC move towards you
			Combat::moveAlongPath(map, enemies[i], player);
			iPos = enemies[i]->getMapY();
			jPos = enemies[i]->getMapX();
			nearby = map->verifyNearbyCharacter(player, jPos, iPos);
		}
	}
}