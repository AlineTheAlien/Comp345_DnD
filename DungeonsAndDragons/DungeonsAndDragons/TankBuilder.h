#pragma once
#include "CharacterBuilder.h"
#include <math.h>
#include <algorithm>
#include <functional>
using namespace std;

class TankBuilder : public CharacterBuilder
{
public:
	TankBuilder();
	~TankBuilder();
	void buildAbilityScores();
};

