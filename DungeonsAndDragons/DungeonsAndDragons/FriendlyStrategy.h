//! @file 
//! @brief Header file for the FriendlyStrategy class  
//!
//! This strategy is used by friendly NPC. The NPC will only move towards the player if the player is not
//! in combat mode with an enemy. In this strategy, the player gets to choose if he/she wants to ignore it
//! or attack it. Should the player decide to attack the NPC, the NPC will use Aggressor Strategy mode. If the user
//! decide to ignore it, nothing will happen and the NPC will stop moving towards the player.
#pragma once
#include "Strategy.h"
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>

//! Class for the implementation of a Friendly Strategy
class FriendlyStrategy: public Strategy {
public:
	void execute(Map*, MapObject*, MapObject*);
	friend class boost::serialization::access;
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
	}
};