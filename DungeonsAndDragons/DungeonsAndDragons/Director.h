#pragma once
#include "CharacterBuilder.h"
#include "Character.h"

class Director
{
public:
	Director();
	~Director();
	void setCharacterBuilder(CharacterBuilder*);
	Character* getCharacter();
	void constructCharacter();
private:
	CharacterBuilder* mycb;
};

