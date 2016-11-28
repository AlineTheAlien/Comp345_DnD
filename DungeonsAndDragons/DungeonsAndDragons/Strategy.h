//! @file 
//! @brief Header file for the abstract Strategy class  
//!
//! Strategy pattern was used in the implementation of a character's behaviour. This class is an abstract super type of
//! AggressorStrategy, FriendlyStrategy and HumanPlayerStategy classes. Each of the execute methods are implemented
//! in the respective subclasses. No other libraries were used except the standard libraries.
#pragma once
#include "Map.h"

//! Class for the implementation of an abstract super class Strategy
class Strategy {
public:
	virtual void execute(Map*,MapObject*, MapObject*) = 0;
};