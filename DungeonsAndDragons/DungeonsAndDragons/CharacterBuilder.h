#pragma once
#include "Character.h";
#include <windows.h>
#include <math.h>

class CharacterBuilder
{
public:
	CharacterBuilder();
	~CharacterBuilder();
	Character* getCharacter();
	void createNewCharacterProduct();
	virtual void buildAbilityScores() = 0;
protected:
	Character* mycharacter;
};

