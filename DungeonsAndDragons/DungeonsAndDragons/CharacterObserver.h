//! @file 
//! @brief Header file for CharacterObserver class  

#pragma once
#include "Observer.h"
#include "Character.h"

//! Class that inherits from Observer and that implements CharacterObserver
class CharacterObserver : public Observer
{
public:
	CharacterObserver();
	CharacterObserver(Character* c);
	~CharacterObserver();
	void Update();
	void UpdateGUI();
	void display();
private: 
	Character *_subject;
};

