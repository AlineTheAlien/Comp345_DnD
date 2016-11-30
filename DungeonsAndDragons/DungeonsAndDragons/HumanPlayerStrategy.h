//! @file 
//! @brief Header file for the HumanPlayerStrategy
//!
//! This strategy is used by a player only. It allows the player to choose a target, to either attack the target,
//! move (up to 6 grids since a fighter human's speed is of 30ft, with 5ft per grid as per the rules). The player
//! may also perform other free actions, which consist of equiping/unequiping weapons, draw a weapon, etc. and this
//! can be performed as many time as the player wants. A player may have multiple attacks as per the game rules.
#pragma once
#include "Strategy.h"
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
//! Class for the implementation of a Human Player Strategy
class HumanPlayerStrategy : public Strategy {
public:
	void execute(Map*,MapObject*, MapObject*);
	static void setHumanPlayerLog(bool);
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
	}
	static bool logHumanPlayer;
};
