//! @file 
//! @brief Implementation file for the FriendlyStrategy class  
//!
#include "FriendlyStrategy.h"
#include "Character.h"
#include "AggressorStrategy.h"
#include "Combat.h"
#include <iostream>

using namespace std;

//! Method to execute the Friendly strategy
//! @param map : Pointer to a map object
//! @param friendlyCharacter : Pointer to a friendly character
//! @param targetCharacter : Pointer to a character targeted by the friendly character
void FriendlyStrategy::execute(Map* map, MapObject* friendlyCharacter, MapObject* targetCharacter) {
	// Declare variables for current position of the NPC
	int i = friendlyCharacter->getMapY();
	int j = friendlyCharacter->getMapX();

	int choice = 1;
	bool done = false;
	bool nearby = map->verifyNearbyCharacter(targetCharacter, j, i);
	while (!nearby) {
		cout << "A friendly NPC is moving towards you." << endl;
		i = friendlyCharacter->getMapY();
		j = friendlyCharacter->getMapX();
		nearby = map->verifyNearbyCharacter(targetCharacter, j, i);

		// Call a static method from Combat class to make the NPC move towards you
		Combat::moveAlongPath(map, friendlyCharacter, targetCharacter);
	}
	//cout << "A friendly NPC is next to you.\nYou may choose to: 1. Ignore or 2. Attack" << endl;
	//cin >> choice;
	//cout << endl;
	//if (choice == 1) {
	//	cout << "You decided to ignore." << endl;
	//}
	//if (choice == 2) {
	//	cout << "Friendly NPC became an enemy..." << endl;
	//	static_cast<Character*>(friendlyCharacter)->setStrategy(new AggressorStrategy());
	//	Combat::startCombat(map, targetCharacter, friendlyCharacter);
	//}
}