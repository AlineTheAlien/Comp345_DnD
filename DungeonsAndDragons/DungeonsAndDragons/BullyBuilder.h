#pragma once
#include "stdafx.h"
#include "CharacterBuilder.h"
#include <math.h>
#include <algorithm>
#include <functional>
using namespace std;

class BullyBuilder : public CharacterBuilder
{
public:
	BullyBuilder();
	~BullyBuilder();
	void buildAbilityScores();
};

