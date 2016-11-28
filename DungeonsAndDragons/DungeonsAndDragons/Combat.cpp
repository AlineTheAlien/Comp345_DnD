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
	int playerHP = static_cast<Character*>(player)->getHP();
	int otherHP = static_cast<Character*>(other)->getHP();

	// Initiative roll:
	// Roll 1d20 die and add dexterity modifier
	initiativePlayer = static_cast<Character*>(player)->roll20d() + static_cast<Character*>(player)->getDexterityModifier();
	initiativeOther = static_cast<Character*>(other)->roll20d() + static_cast<Character*>(other)->getDexterityModifier();

	// Display results
	cout << "Player's initiative roll: " << initiativePlayer << endl;
	cout << "Enemy's initiative roll: " << initiativeOther << endl;
	cout << endl;

	// If player has higher initiative roll, player will start the round, else it will be the other character
	if (initiativePlayer > initiativeOther) {
		cout << "*** PLAYER BEGINS THE ROUND ***" << endl;
		while (playerHP > 0 && otherHP > 0) {
			static_cast<Character*>(player)->executeStrategy(map, player, other); // Player uses Human Player Strategy
			otherHP = static_cast<Character*>(other)->getHP();
			if (otherHP <= 0)
				break;
			static_cast<Character*>(other)->executeStrategy(map, other, player); // Enemy uses Aggressor Strategy
			playerHP = static_cast<Character*>(player)->getHP();
			if (playerHP <= 0)
				break;
		}
	}
	else {
		cout << "*** ENEMY BEGINS THE ROUND ***" << endl;
		while (playerHP > 0 && otherHP > 0) {
			static_cast<Character*>(other)->executeStrategy(map, other, player); // Enemy uses Aggressor Strategy
			playerHP = static_cast<Character*>(player)->getHP();
			if (playerHP <= 0)
				break;
			static_cast<Character*>(player)->executeStrategy(map, player, other); // Player uses Human Player Strategy
			otherHP = static_cast<Character*>(other)->getHP();
			if (otherHP <= 0)
				break;
		}
	}
	cout << "\nCOMBAT ENDED: " << endl;
	if (playerHP <= 0) {
		cout << "Player is defeated." << endl;
		int i = static_cast<Character*>(player)->getMapY();
		int j = static_cast<Character*>(player)->getMapX();
		map->setTile(j, i, NULL);
		map->showMap();
		int done;
		cin >> done;
		exit(1);
	}
	else {
		int i = static_cast<Character*>(other)->getMapY();
		int j = static_cast<Character*>(other)->getMapX();
		cout << "Enemy is defeated.\n" << endl;
		map->setTile(j, i, NULL);
		map->showMap();
	}

}

//! Iterative method for making enemies or friendly character move towards the player.
//! @param map : Pointer to a map
//! @param character : Pointer to a character who will be moving
//! @param target : Pointer to a target character
void Combat::moveAlongPath(Map* map, MapObject* character, MapObject* target) {

	// Get position of the following character
	int i = static_cast<Character*>(character)->getMapY();
	int j = static_cast<Character*>(character)->getMapX();
	bool nearby = map->verifyNearbyCharacter(target, j, i);
	// Get position of the target character being followed
	int iTarget = static_cast<Character*>(target)->getMapY();
	int jTarget = static_cast<Character*>(target)->getMapX();

	// If the enemy is not aligned with the player either same row or same column, this block will run
	if (i != iTarget && j != jTarget) {
		if (i > iTarget && j < jTarget) {
			// move up
			if (!(j > map->getMapX() || j < 0 || i - 1 > map->getMapY() || i - 1 < 0) && !(map->isOccupied(j, i - 1))) {
				map->setEnemy(j, i - 1, character);
				map->setTile(j, i, NULL);
				i = static_cast<Character*>(character)->getMapY();
				j = static_cast<Character*>(character)->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}
			// move right
			if (!nearby && !(j + 1 > map->getMapX() || j + 1 < 0 || i > map->getMapY() || i < 0) && !(map->isOccupied(j + 1, i))) {
				map->setEnemy(j + 1, i, character);
				map->setTile(j, i, NULL);
				i = static_cast<Character*>(character)->getMapY();
				j = static_cast<Character*>(character)->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}
		}
		else if (i > iTarget && j > jTarget) {
			// move left
			if (!nearby && !(j - 1 > map->getMapX() || j - 1 < 0 || i > map->getMapY() || i < 0) && !(map->isOccupied(j - 1, i))) {
				map->setEnemy(j - 1, i, character);
				map->setTile(j, i, NULL);
				i = static_cast<Character*>(character)->getMapY();
				j = static_cast<Character*>(character)->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}
			// move up
			if (!nearby && !(j > map->getMapX() || j < 0 || i - 1 > map->getMapY() || i - 1 < 0) && !(map->isOccupied(j, i - 1))) {
				map->setEnemy(j, i - 1, character);
				map->setTile(j, i, NULL);
				i = static_cast<Character*>(character)->getMapY();
				j = static_cast<Character*>(character)->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}
		}
		else if (i < iTarget && j < jTarget) {
			// move down
			if (!nearby && !(j > map->getMapX() || j < 0 || i + 1 > map->getMapY() || i + 1 < 0) && !(map->isOccupied(j, i + 1))) {
				map->setEnemy(j, i + 1, character);
				map->setTile(j, i, NULL);
				i = static_cast<Character*>(character)->getMapY();
				j = static_cast<Character*>(character)->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}
			// move right
			if (!nearby && !(j + 1 > map->getMapX() || j + 1 < 0 || i > map->getMapY() || i < 0) && !(map->isOccupied(j + 1, i))) {
				map->setEnemy(j + 1, i, character);
				map->setTile(j, i, NULL);
				i = static_cast<Character*>(character)->getMapY();
				j = static_cast<Character*>(character)->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}
		}
		else if (i < iTarget && j > jTarget) {
			// move down
			if (!nearby && !(j > map->getMapX() || j < 0 || i + 1 > map->getMapY() || i + 1 < 0) && !(map->isOccupied(j, i + 1))) {
				map->setEnemy(j, i + 1, character);
				map->setTile(j, i, NULL);
				i = static_cast<Character*>(character)->getMapY();
				j = static_cast<Character*>(character)->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}
			// move left
			if (!nearby && !(j - 1 > map->getMapX() || j - 1 < 0 || i > map->getMapY() || i < 0) && !(map->isOccupied(j - 1, i))) {
				map->setEnemy(j - 1, i, character);
				map->setTile(j, i, NULL);
				i = static_cast<Character*>(character)->getMapY();
				j = static_cast<Character*>(character)->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}
		}
	}

	// If the enemy is on the same column as the player, this block will run
	else if (i != iTarget && j == jTarget) {
		if (i < iTarget) {
			// move down
			if (!nearby && !(j > map->getMapX() || j < 0 || i + 1 > map->getMapY() || i + 1 < 0) && !(map->isOccupied(j, i + 1))) {
				map->setEnemy(j, i + 1, character);
				map->setTile(j, i, NULL);
				i = static_cast<Character*>(character)->getMapY();
				j = static_cast<Character*>(character)->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}
			// If blocked, move left or move right
			if (!nearby && !(j > map->getMapX() || j < 0 || i + 1 > map->getMapY() || i + 1 < 0) && (map->isOccupied(j, i + 1))) {
				// move left
				if (!(j - 1 > map->getMapX() || j - 1 < 0 || i > map->getMapY() || i < 0) && !(map->isOccupied(j - 1, i))) {
					map->setEnemy(j - 1, i, character);
					map->setTile(j, i, NULL);
					i = static_cast<Character*>(character)->getMapY();
					j = static_cast<Character*>(character)->getMapX();
					nearby = map->verifyNearbyCharacter(target, j, i);
					map->showMap();
				}
				else if (!nearby && !(j + 1 > map->getMapX() || j + 1 < 0 || i > map->getMapY() || i < 0) && !(map->isOccupied(j + 1, i))) {
					map->setEnemy(j + 1, i, character);
					map->setTile(j, i, NULL);
					i = static_cast<Character*>(character)->getMapY();
					j = static_cast<Character*>(character)->getMapX();
					nearby = map->verifyNearbyCharacter(target, j, i);
					map->showMap();
				}
			}
		}

		if (i > iTarget) {
			// move up
			if (!nearby && !(j > map->getMapX() || j < 0 || i - 1 > map->getMapY() || i - 1 < 0) && !(map->isOccupied(j, i - 1))) {
				map->setEnemy(j, i - 1, character);
				map->setTile(j, i, NULL);
				i = static_cast<Character*>(character)->getMapY();
				j = static_cast<Character*>(character)->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}

			// If blocked, move left or move right
			if (!(j > map->getMapX() || j < 0 || i - 1 > map->getMapY() || i - 1 < 0) && (map->isOccupied(j, i - 1))) {
				// move left
				if (!nearby && !(j - 1 > map->getMapX() || j - 1 < 0 || i > map->getMapY() || i < 0) && !(map->isOccupied(j - 1, i))) {
					map->setEnemy(j - 1, i, character);
					map->setTile(j, i, NULL);
					i = static_cast<Character*>(character)->getMapY();
					j = static_cast<Character*>(character)->getMapX();
					nearby = map->verifyNearbyCharacter(target, j, i);
					map->showMap();
				}
			}
			else {
				// move right
				if (!nearby && !(j + 1 > map->getMapX() || j + 1 < 0 || i > map->getMapY() || i < 0) && !(map->isOccupied(j + 1, i))) {
					map->setEnemy(j + 1, i, character);
					map->setTile(j, i, NULL);
					i = static_cast<Character*>(character)->getMapY();
					j = static_cast<Character*>(character)->getMapX();
					nearby = map->verifyNearbyCharacter(target, j, i);
					map->showMap();
				}
			}
		}
	}

	// If the enemy is on the same row as the player, this block will run
	else if (i == iTarget && j != jTarget) {
		if (j < jTarget) {
			// move right
			if (!nearby && !(j + 1 > map->getMapX() || j + 1 < 0 || i > map->getMapY() || i < 0) && !(map->isOccupied(j + 1, i))) {
				map->setEnemy(j + 1, i, character);
				map->setTile(j, i, NULL);
				i = static_cast<Character*>(character)->getMapY();
				j = static_cast<Character*>(character)->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}
			// If blocked, move left or move right
			if (!nearby && !(j > map->getMapX() || j < 0 || i - 1 > map->getMapY() || i - 1 < 0) && (map->isOccupied(j, i - 1))) {
				// move left
				if (!(j - 1 > map->getMapX() || j - 1 < 0 || i > map->getMapY() || i < 0) && !(map->isOccupied(j - 1, i))) {
					map->setEnemy(j - 1, i, character);
					map->setTile(j, i, NULL);
					i = static_cast<Character*>(character)->getMapY();
					j = static_cast<Character*>(character)->getMapX();
					map->showMap();
				}
			}
			else {
				// move right
				if (!nearby && !(j + 1 > map->getMapX() || j + 1 < 0 || i > map->getMapY() || i < 0) && !(map->isOccupied(j + 1, i))) {
					map->setEnemy(j + 1, i, character);
					map->setTile(j, i, NULL);
					i = static_cast<Character*>(character)->getMapY();
					j = static_cast<Character*>(character)->getMapX();
					map->showMap();
				}
			}
		}
		if (j > jTarget) {
			// move left
			if (!(j - 1 > map->getMapX() || j - 1 < 0 || i > map->getMapY() || i < 0) && !(map->isOccupied(j - 1, i))) {
				map->setEnemy(j - 1, i, character);
				map->setTile(j, i, NULL);
				i = static_cast<Character*>(character)->getMapY();
				j = static_cast<Character*>(character)->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}
			// If blocked, move left or move right
			if (!nearby && !(j > map->getMapX() || j < 0 || i - 1 > map->getMapY() || i - 1 < 0) && (map->isOccupied(j, i - 1))) {
				// move left
				if (!(j - 1 > map->getMapX() || j - 1 < 0 || i > map->getMapY() || i < 0) && !(map->isOccupied(j - 1, i))) {
					map->setEnemy(j - 1, i, character);
					map->setTile(j, i, NULL);
					i = static_cast<Character*>(character)->getMapY();
					j = static_cast<Character*>(character)->getMapX();
					map->showMap();
				}
			}
			else {
				// move right
				if (!nearby && !(j + 1 > map->getMapX() || j + 1 < 0 || i > map->getMapY() || i < 0) && !(map->isOccupied(j + 1, i))) {
					map->setEnemy(j + 1, i, character);
					map->setTile(j, i, NULL);
					i = static_cast<Character*>(character)->getMapY();
					j = static_cast<Character*>(character)->getMapX();
					map->showMap();
				}
			}
		}
	}
}