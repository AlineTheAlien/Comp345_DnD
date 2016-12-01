#include "stdafx.h"
#include "Director.h"

//! Constructor for Director
Director::Director()
{
}

//! Destructor for Director
Director::~Director()
{
}

//! Attaches a concrete builder in order to create the fighter with type that we choose
//! @param cb: the concrete builder of choice to create with the Director
void Director::setCharacterBuilder(CharacterBuilder* cb) {
	mycb = cb;
}

//! Returns the constructed Character
//! return Character*, a pointer to the character constructed by the Director
Character* Director::getCharacter() {
	return mycb->getCharacter();
}

//! Function that uses the CharacterBuilder to create a product of type Character
void Director::constructCharacter() {
	mycb->createNewCharacterProduct();
	mycb->buildAbilityScores();
}
