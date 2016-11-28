#pragma once
#include "CharacterBuilder.h"
#include <math.h>
#include <algorithm>
#include <functional>
using namespace std;

class FriendlyBuilder : public CharacterBuilder
{
public:
	FriendlyBuilder();
	~FriendlyBuilder();
	void buildAbilityScores();
};

