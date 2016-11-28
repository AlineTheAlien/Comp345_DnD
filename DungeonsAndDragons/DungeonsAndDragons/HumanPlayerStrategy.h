//! @file 
//! @brief Header file for the HumanPlayerStrategy
//!
//! This strategy is used by a player only. It allows the player to choose a target, to either attack the target,
//! move (up to 6 grids since a fighter human's speed is of 30ft, with 5ft per grid as per the rules). The player
//! may also perform other free actions, which consist of equiping/unequiping weapons, draw a weapon, etc. and this
//! can be performed as many time as the player wants. A player may have multiple attacks as per the game rules.
#pragma once
#include "Strategy.h"

//! Class for the implementation of a Human Player Strategy
class HumanPlayerStrategy : public Strategy {
public:
	void execute(Map*,MapObject*, MapObject*);
};
