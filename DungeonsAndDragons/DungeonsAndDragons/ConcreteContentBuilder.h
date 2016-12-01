//! @file 
//! @brief Header file for the Concrete Content Builder class
//!
#pragma once
#include "ContentBuilder.h"

//! Class for the implementation of a concrete content builder class which adapts contents of a map to the player's level, such as
//! NPCs and containers (including items possessed by NPCs).
class ConcreteContentBuilder : public ContentBuilder {
public:
	void buildCharacter(char, int, int, MapObject*);
	void buildContainer(int, int, vector<Item*>&);
};