#include "stdafx.h"
#include "Director.h"

Director::Director()
{
}


Director::~Director()
{
}

void Director::setCharacterBuilder(CharacterBuilder* cb) {
	mycb = cb;
}

Character* Director::getCharacter() {
	return mycb->getCharacter();
}

void Director::constructCharacter() {
	mycb->createNewCharacterProduct();
	mycb->buildAbilityScores();
}
