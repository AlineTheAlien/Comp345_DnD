//! @file 
//! @brief Header file for the AggressorStrategy class  
//!
//! This strategy is used by enemies. If the player encounters an enemy by walking towards it, combat mode is started and
//! the enemy will either attack the player or move towards the player to stay within range of attack.
#pragma once
#include "Strategy.h"
#include "GameLogger.h"

//! Class for the implementation of a Aggressor Strategy
class AggressorStrategy : public Strategy {
public:
	void execute(Map*, MapObject*, MapObject*);
	static void setAgressorLog(bool);
private:
	static bool logAgressor;
};