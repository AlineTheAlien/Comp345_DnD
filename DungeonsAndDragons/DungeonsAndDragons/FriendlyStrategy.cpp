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
	// Total number of move is 6 grids in a round
	int numOfMoves = 6;

	// Declare variables for current position of the NPC
	int i;
	int j;

	int choice = 1;
	bool done = false;

	// Verify if NPC is near player
	bool nearby;
	while (!done) {
		i = static_cast<Character*>(friendlyCharacter)->getMapY();
		j = static_cast<Character*>(friendlyCharacter)->getMapX();
		nearby = map->verifyNearbyCharacter(targetCharacter, j, i);

		// If NPC is not near the player, it will move towards him/her
		if (!nearby) {
			cout << "A friendly NPC is moving towards you." << endl;

			// If player is not nearby, it will move towards it
			while (numOfMoves > 0) {
				
				// Get current position of the NPC
				i = static_cast<Character*>(friendlyCharacter)->getMapY();
				j = static_cast<Character*>(friendlyCharacter)->getMapX();
				
				// Verify if it is in proximity of the player
				nearby = map->verifyNearbyCharacter(targetCharacter, j, i);
				if (nearby) {
					numOfMoves = 0;
					done = true;
					break;
				}
				// Call a static method from Combat class to make the NPC move towards you
				Combat::moveAlongPath(map, friendlyCharacter, targetCharacter);
				numOfMoves--;
			}
		}
	}
}
