#pragma once
#include "MapBuilder.h"

//! Class for the implementation of a concrete builder class which allows user editing of contents on map
class ConcreteBuilderB : public MapBuilder {
public:
	void buildCharacter(char, int, int, MapObject*);
	void buildContainer(int, int);
};