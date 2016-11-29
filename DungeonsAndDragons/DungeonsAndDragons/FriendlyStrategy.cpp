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

	bool nearby = map->verifyNearbyCharacter(targetCharacter, j, i);
	while (!nearby) {
		cout << "A friendly NPC is moving towards you." << endl;
		i = friendlyCharacter->getMapY();
		j = friendlyCharacter->getMapX();
		nearby = map->verifyNearbyCharacter(targetCharacter, j, i);
		nearby = true; //test
		// Call a static method from Combat class to make the NPC move towards you
		Combat::moveAlongPath(map, friendlyCharacter, targetCharacter);
	}
}