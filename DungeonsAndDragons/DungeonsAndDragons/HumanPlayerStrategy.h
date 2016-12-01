//! @file 
//! @brief Header file for the HumanPlayerStrategy
//!
//! This strategy is used by a player only. It allows the player to choose a target, to either attack the target,
//! move (up to 6 grids since a fighter human's speed is of 30ft, with 5ft per grid as per the rules). The player
//! may also perform other free actions, in a bigger D&D game, this would include using items other than equipment (such as a potion),
//! but for the sake of simplicity, our game allows equipment modification during combat. This can be performed as many time
//! as the player wants. A player may have multiple attacks as per the game rules.
#pragma once
#include "Strategy.h"

//! Class for the implementation of a Human Player Strategy
class HumanPlayerStrategy : public Strategy {
public:
	void execute(Map*,MapObject*, MapObject*);
	static void setHumanPlayerLog(bool);
private:
	static bool logHumanPlayer;
};
