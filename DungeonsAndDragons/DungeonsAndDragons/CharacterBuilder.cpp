#include "stdafx.h"
#include "CharacterBuilder.h"


CharacterBuilder::CharacterBuilder()
{
}


CharacterBuilder::~CharacterBuilder()
{
}

Character* CharacterBuilder::getCharacter() {
	return mycharacter;
}

void CharacterBuilder::createNewCharacterProduct() {
	mycharacter = new Character;
}
