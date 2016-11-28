#pragma once
#include "CharacterBuilder.h"
#include <math.h>
#include <algorithm>
#include <functional>
using namespace std;

class NimbleBuilder : public CharacterBuilder
{
public:
	NimbleBuilder();
	~NimbleBuilder();
	void buildAbilityScores();
};

