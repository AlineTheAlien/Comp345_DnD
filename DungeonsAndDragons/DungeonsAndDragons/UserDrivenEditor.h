//! @file 
//! @brief Header file for UserDrivenEditor class
#pragma once
#include "ItemContainer.h"
#include "CharacterObserver.h"
#include "Character.h"
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include "Shield.h"
#include "Armor.h"
#include "Belt.h"
#include "Boots.h"
#include "Helmet.h"
#include "Ring.h"
#include "Shield.h"
#include "Weapon.h"
class UserDrivenEditor
{
public:
	UserDrivenEditor();
	static ItemContainer* createChest();
	static ItemContainer* createBackpack();
	static Character* createCharacter();
	~UserDrivenEditor();
};

