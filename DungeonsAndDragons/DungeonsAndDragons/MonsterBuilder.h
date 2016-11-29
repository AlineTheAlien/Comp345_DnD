#pragma once
#include "CharacterBuilder.h"
#include <math.h>
#include <algorithm>
#include <functional>
using namespace std;

class MonsterBuilder : public CharacterBuilder
{
public:
	MonsterBuilder();
	~MonsterBuilder();
	void buildAbilityScores();
};

