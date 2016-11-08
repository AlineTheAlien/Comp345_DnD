#pragma once
#include "ItemContainer.h"
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
class ContainerEditor
{
public:
	ContainerEditor();
	static ItemContainer* createChest();
	~ContainerEditor();
};

