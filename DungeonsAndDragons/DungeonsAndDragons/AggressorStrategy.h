//! @file 
//! @brief Header file for the AggressorStrategy class  
//!
//! This strategy is used by enemies. If the player is within a range of 1 grid of the enemy, combat mode is started and
//! the enemy will either attack the player or move towards the player to stay within range of attack.
#pragma once
#include "Strategy.h"
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>

//! Class for the implementation of a Aggressor Strategy
class AggressorStrategy : public Strategy {
public:
	void execute(Map*, MapObject*, MapObject*);
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
	}

};