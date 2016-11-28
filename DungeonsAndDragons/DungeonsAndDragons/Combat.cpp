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
	cout << "\nCOMBAT ENDED: " << endl;
	if (playerHP <= 0) {
		cout << "Player is defeated." << endl;
		int i = player->getMapY();
		int j = player->getMapX();
		map->setTile(j, i, NULL);
		map->showMap();
		int done;
		cin >> done;
		exit(1);
	}
	else {
		int i = other->getMapY();
		int j = other->getMapX();
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
			if (!(j > map->getMapX() || j < 0 || i - 1 > map->getMapY() || i - 1 < 0) && !(map->availableTile(j, i - 1))) {
				map->setTile(j, i - 1, character);
				map->setTile(j, i, NULL);
				i = character->getMapY();
				j = character->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}
			// move right
			if (!nearby && !(j + 1 > map->getMapX() || j + 1 < 0 || i > map->getMapY() || i < 0) && !(map->availableTile(j + 1, i))) {
				map->setTile(j + 1, i, character);
				map->setTile(j, i, NULL);
				i = character->getMapY();
				j = character->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}
		}
		else if (i > iTarget && j > jTarget) {
			// move left
			if (!nearby && !(j - 1 > map->getMapX() || j - 1 < 0 || i > map->getMapY() || i < 0) && !(map->availableTile(j - 1, i))) {
				map->setTile(j - 1, i, character);
				map->setTile(j, i, NULL);
				i = character->getMapY();
				j = character->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}
			// move up
			if (!nearby && !(j > map->getMapX() || j < 0 || i - 1 > map->getMapY() || i - 1 < 0) && !(map->availableTile(j, i - 1))) {
				map->setTile(j, i - 1, character);
				map->setTile(j, i, NULL);
				i = character->getMapY();
				j = character->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}
		}
		else if (i < iTarget && j < jTarget) {
			// move down
			if (!nearby && !(j > map->getMapX() || j < 0 || i + 1 > map->getMapY() || i + 1 < 0) && !(map->availableTile(j, i + 1))) {
				map->setTile(j, i + 1, character);
				map->setTile(j, i, NULL);
				i = character->getMapY();
				j = character->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}
			// move right
			if (!nearby && !(j + 1 > map->getMapX() || j + 1 < 0 || i > map->getMapY() || i < 0) && !(map->availableTile(j + 1, i))) {
				map->setTile(j + 1, i, character);
				map->setTile(j, i, NULL);
				i = character->getMapY();
				j = character->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}
		}
		else if (i < iTarget && j > jTarget) {
			// move down
			if (!nearby && !(j > map->getMapX() || j < 0 || i + 1 > map->getMapY() || i + 1 < 0) && !(map->availableTile(j, i + 1))) {
				map->setTile(j, i + 1, character);
				map->setTile(j, i, NULL);
				i = character->getMapY();
				j = character->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}
			// move left
			if (!nearby && !(j - 1 > map->getMapX() || j - 1 < 0 || i > map->getMapY() || i < 0) && !(map->availableTile(j - 1, i))) {
				map->setTile(j - 1, i, character);
				map->setTile(j, i, NULL);
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
			if (!nearby && !(j > map->getMapX() || j < 0 || i + 1 > map->getMapY() || i + 1 < 0) && !(map->availableTile(j, i + 1))) {
				map->setTile(j, i + 1, character);
				map->setTile(j, i, NULL);
				i = character->getMapY();
				j = character->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}
			// If blocked, move left or move right
			if (!nearby && !(j > map->getMapX() || j < 0 || i + 1 > map->getMapY() || i + 1 < 0) && (map->availableTile(j, i + 1))) {
				// move left
				if (!(j - 1 > map->getMapX() || j - 1 < 0 || i > map->getMapY() || i < 0) && !(map->availableTile(j - 1, i))) {
					map->setTile(j - 1, i, character);
					map->setTile(j, i, NULL);
					i = character->getMapY();
					j = character->getMapX();
					nearby = map->verifyNearbyCharacter(target, j, i);
					map->showMap();
				}
				else if (!nearby && !(j + 1 > map->getMapX() || j + 1 < 0 || i > map->getMapY() || i < 0) && !(map->availableTile(j + 1, i))) {
					map->setTile(j + 1, i, character);
					map->setTile(j, i, NULL);
					i = character->getMapY();
					j = character->getMapX();
					nearby = map->verifyNearbyCharacter(target, j, i);
					map->showMap();
				}
			}
		}

		if (i > iTarget) {
			// move up
			if (!nearby && !(j > map->getMapX() || j < 0 || i - 1 > map->getMapY() || i - 1 < 0) && !(map->availableTile(j, i - 1))) {
				map->setTile(j, i - 1, character);
				map->setTile(j, i, NULL);
				i = character->getMapY();
				j = character->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}

			// If blocked, move left or move right
			if (!(j > map->getMapX() || j < 0 || i - 1 > map->getMapY() || i - 1 < 0) && (map->availableTile(j, i - 1))) {
				// move left
				if (!nearby && !(j - 1 > map->getMapX() || j - 1 < 0 || i > map->getMapY() || i < 0) && !(map->availableTile(j - 1, i))) {
					map->setTile(j - 1, i, character);
					map->setTile(j, i, NULL);
					i = character->getMapY();
					j = character->getMapX();
					nearby = map->verifyNearbyCharacter(target, j, i);
					map->showMap();
				}
			}
			else {
				// move right
				if (!nearby && !(j + 1 > map->getMapX() || j + 1 < 0 || i > map->getMapY() || i < 0) && !(map->availableTile(j + 1, i))) {
					map->setTile(j + 1, i, character);
					map->setTile(j, i, NULL);
					i = character->getMapY();
					j = character->getMapX();
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
			if (!nearby && !(j + 1 > map->getMapX() || j + 1 < 0 || i > map->getMapY() || i < 0) && !(map->availableTile(j + 1, i))) {
				map->setTile(j + 1, i, character);
				map->setTile(j, i, NULL);
				i = character->getMapY();
				j = character->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}
			// If blocked, move left or move right
			if (!nearby && !(j > map->getMapX() || j < 0 || i - 1 > map->getMapY() || i - 1 < 0) && (map->availableTile(j, i - 1))) {
				// move left
				if (!(j - 1 > map->getMapX() || j - 1 < 0 || i > map->getMapY() || i < 0) && !(map->availableTile(j - 1, i))) {
					map->setTile(j - 1, i, character);
					map->setTile(j, i, NULL);
					i = character->getMapY();
					j = character->getMapX();
					map->showMap();
				}
			}
			else {
				// move right
				if (!nearby && !(j + 1 > map->getMapX() || j + 1 < 0 || i > map->getMapY() || i < 0) && !(map->availableTile(j + 1, i))) {
					map->setTile(j + 1, i, character);
					map->setTile(j, i, NULL);
					i = character->getMapY();
					j = character->getMapX();
					map->showMap();
				}
			}
		}
		if (j > jTarget) {
			// move left
			if (!(j - 1 > map->getMapX() || j - 1 < 0 || i > map->getMapY() || i < 0) && !(map->availableTile(j - 1, i))) {
				map->setTile(j - 1, i, character);
				map->setTile(j, i, NULL);
				i = character->getMapY();
				j = character->getMapX();
				nearby = map->verifyNearbyCharacter(target, j, i);
				map->showMap();
			}
			// If blocked, move left or move right
			if (!nearby && !(j > map->getMapX() || j < 0 || i - 1 > map->getMapY() || i - 1 < 0) && (map->availableTile(j, i - 1))) {
				// move left
				if (!(j - 1 > map->getMapX() || j - 1 < 0 || i > map->getMapY() || i < 0) && !(map->availableTile(j - 1, i))) {
					map->setTile(j - 1, i, character);
					map->setTile(j, i, NULL);
					i = character->getMapY();
					j = character->getMapX();
					map->showMap();
				}
			}
			else {
				// move right
				if (!nearby && !(j + 1 > map->getMapX() || j + 1 < 0 || i > map->getMapY() || i < 0) && !(map->availableTile(j + 1, i))) {
					map->setTile(j + 1, i, character);
					map->setTile(j, i, NULL);
					i = character->getMapY();
					j = character->getMapX();
					map->showMap();
				}
			}
		}
	}
}

//! Method to detect if player is near an enemy or an NPC and to start executing strategies for combat
//! @param map : Pointer to a map object
//! @param player : Poitner to a player object
void Combat::detectOthers(Map* map, MapObject* player) {
	// Get all enemies and friendly NPC on the map
	vector<MapObject*> enemies = map->findAllEnemies();
	vector<MapObject*> friends = map->findAllFriends();
	vector<MapObject*> nearbyEnemies;
	vector<MapObject*> nearbyFriends;

	// For user input
	int choice = 0;

	bool done = false;
	// To store x,y position of the player on the map
	int x;
	int y;
	// Declare pointers that will be used to points to a nearby enemy or friend
	MapObject* nearbyEnemy;
	MapObject* nearbyFriend;
	map->showMap();

	x = player->getMapX();
	y = player->getMapY();

	// Verify if there are nearby enemies
	for (int i = 0; i < enemies.size(); i++) {
		// If enemy is near the player (within one grid) push it into the vector
		if (map->verifyNearbyCharacter(enemies[i], x, y)) {
			nearbyEnemies.push_back(enemies[i]);
		}
	}

	// Verify if there are nearby friendly NPCs
	for (int i = 0; i < friends.size(); i++) {
		if (map->verifyNearbyCharacter(friends[i], x, y)) {
			nearbyFriends.push_back(friends[i]);
		}
	}

	do {
		// Start combat mode if there is an enemy nearby
		if (nearbyEnemies.size() > 0) {
			// Player can select a target from enemies that are within 1 grid
			cout << "Number of enemies nearby: " << nearbyEnemies.size() << "\nYou may select any enemy as a target. Enter the corresponding number from below.\n" << endl;
			for (int i = 0; i < nearbyEnemies.size(); i++) {
				cout << "[" << i << "]" << endl;
				static_cast<Character*>(nearbyEnemies[i])->displayCharacterInfo();
			}

			cin >> choice;
			cout << endl;
			nearbyEnemy = nearbyEnemies[choice];
			// Call a static method from Combat class
			Combat::startCombat(map, player, nearbyEnemy);
			// If player is dead, console will close.

			// If player is still alive, it will check if there are other enemies from his current position
			enemies.erase(enemies.begin() + choice);

			// Empty the vectors
			nearbyEnemies = vector<MapObject*>();
			nearbyFriends = vector<MapObject*>();

			// Get current position of the player
			int x = player->getMapX();
			int y = player->getMapY();
			// Verify if there are nearby enemies at the new position
			for (int i = 0; i < enemies.size(); i++) {
				// If enemy is near the player (within one grid) push it into the vector
				if (map->verifyNearbyCharacter(enemies[i], x, y)) {
					nearbyEnemies.push_back(enemies[i]);
				}
			}
			// Verify if there are nearby friendly NPCs at the new position
			for (int i = 0; i < friends.size(); i++) {
				if (map->verifyNearbyCharacter(friends[i], x, y)) {
					nearbyFriends.push_back(friends[i]);
				}
			}
		}
	} while (nearbyEnemies.size() > 0); // Keep looping if there are nearby enemies at the current player position

										// Check if there are nearby friends while walking
	while (nearbyFriends.size() > 0) {
		choice = 1;
		cout << "Number of friendly NPC's nearby: " << nearbyFriends.size() << "\nYou may choose to: 1. Ignore them or 2. Attack one of them." << endl;
		cin >> choice;
		cout << endl;
		// There may be more than one NPC within one grid. Player may select which one to interact with.
		if (choice == 1) {
			choice = 0;
			cout << "Select a friendly NPC to ignore from below: \n" << endl;
			for (int i = 0; i < nearbyFriends.size(); i++) {
				cout << "[" << i << "]" << endl;
				static_cast<Character*>(nearbyFriends[i])->displayCharacterInfo();
			}
			cin >> choice;
			cout << endl;
			friends.erase(friends.begin() + choice);
			nearbyFriends.erase(nearbyFriends.begin() + choice);
		}
		// Select an NPC to attack
		if (choice == 2) {
			choice = 0;
			cout << "Select a target from below: \n" << endl;
			for (int i = 0; i < nearbyFriends.size(); i++) {
				cout << "[" << i << "]" << endl;
				static_cast<Character*>(nearbyFriends[i])->displayCharacterInfo();
			}
			cin >> choice;
			cout << endl;

			nearbyFriend = nearbyFriends[choice];
			cout << "Friendly NPC became an enemy..." << endl;
			static_cast<Character*>(nearbyFriend)->setStrategy(new AggressorStrategy());
			Combat::startCombat(map, player, nearbyFriend);
			// If player is dead, console will close.

			// If player is still alive, it will check if there are other enemies from his current position
			friends.erase(friends.begin() + choice);
			nearbyFriends.erase(nearbyFriends.begin() + choice);
		}
	}
	// When the player is free, friendly NPC walks towards player
	for (int i = 0; i < friends.size(); i++) {
		static_cast<Character*>(friends[i])->executeStrategy(map, friends[i], player);
	}
}