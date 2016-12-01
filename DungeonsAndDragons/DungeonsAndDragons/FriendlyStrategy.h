//! @file 
//! @brief Header file for the FriendlyStrategy class  
//!
//! This strategy is used by friendly NPCs. The NPC will only move towards the player if the player is not
//! in combat mode with an enemy. In this strategy, the player gets to choose if he/she wants to ignore it
//! or attack it. Should the player decide to attack the NPC, the NPC will use Aggressor Strategy mode. If the player
//! decides to ignore it, nothing will happen and the NPC will stop moving towards the player.
#pragma once
#include "Strategy.h"
//! Class for the implementation of a Friendly Strategy
class FriendlyStrategy: public Strategy {
public:
	void execute(Map*, MapObject*, MapObject*);
	friend class boost::serialization::access;
	static void setFriendlyLog(bool);
private:
	static bool logFriendly;
};