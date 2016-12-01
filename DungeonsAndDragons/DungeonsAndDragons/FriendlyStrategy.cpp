//! @file 
//! @brief Implementation file for the FriendlyStrategy class  
//!
#include "FriendlyStrategy.h"
#include "Character.h"
#include "AggressorStrategy.h"
#include "Combat.h"
#include <iostream>
#include "GameLogger.h"

using namespace std;

bool FriendlyStrategy::logFriendly = true;

//! Method to execute the Friendly strategy
//! @param map : Pointer to a map object
//! @param friendlyCharacter : Pointer to a friendly character
//! @param targetCharacter : Pointer to a character targeted by the friendly character
void FriendlyStrategy::execute(Map* map, MapObject* friendlyCharacter, MapObject* targetCharacter) {
	int iPos = friendlyCharacter->getMapY();
	int jPos = friendlyCharacter->getMapX();

	bool nearby = map->verifyNearbyCharacter(targetCharacter, jPos, iPos);
	while (!nearby) {
		// Call a static method from Combat class to make the NPC move towards you
		Combat::moveAlongPath(map, friendlyCharacter, targetCharacter);
		iPos = friendlyCharacter->getMapY();
		jPos = friendlyCharacter->getMapX();
		nearby = map->verifyNearbyCharacter(targetCharacter, jPos, iPos);
	}

	string s = "";
	int choice;
	cout << "You encountered a friend.\nYou may choose to: 1. Ignore or 2. Attack" << endl;
	cin >> choice;
	cout << endl;
	if (choice == 1) {
		if (logFriendly == true) {
			cout << "You decided to ignore." << endl;
			s += "You decided to ignore. \n";
		}
	}
	if (choice == 2) {
		if (logFriendly == true) {
			cout << "Friendly NPC became an enemy..." << endl;
			s += "Friendly NPC became an enemy...\n";
		}
		static_cast<Character*>(friendlyCharacter)->setStrategy(new AggressorStrategy());
		Combat::startCombat(map, targetCharacter, friendlyCharacter);
	}
	GameLogger::writeToLogFile(s);
}

//! Function that sets the combat log boolean 
//! @param value: new boolean value of logFriendly
void FriendlyStrategy::setFriendlyLog(bool value) {
	logFriendly = value;
}