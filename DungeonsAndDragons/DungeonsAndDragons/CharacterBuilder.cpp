#include "stdafx.h"
#include "CharacterBuilder.h"

//! Constructor
CharacterBuilder::CharacterBuilder()
{
}

//! Desctructor
CharacterBuilder::~CharacterBuilder()
{
}

//! Method that returns the character that was built
//! return Character*, pointer to a character that was built using the builder pattern
Character* CharacterBuilder::getCharacter() {
	return mycharacter;
}

//! Method that creates a character object
void CharacterBuilder::createNewCharacterProduct() {
	mycharacter = new Character;
}
