#pragma once
#include "MapBuilder.h"
//! Class for the implementation of a concrete builder class which adapts contents of a map to the player's level
class ConcreteBuilderA : public MapBuilder {
public:
	void buildCharacter(char, int, int, MapObject*);
	void buildContainer(int, int, vector<Item*>&);
};