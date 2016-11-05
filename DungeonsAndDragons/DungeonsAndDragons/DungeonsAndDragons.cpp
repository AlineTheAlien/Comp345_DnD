// DungeonsAndDragons.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ItemContainer.h"
#include "Item.h"
#include "Character.h"
#include "Enhancement.h"
#include <Vector>
#include "Shield.h"
#include "Armor.h"
#include <ctime>
using namespace std;


int main()
{
	srand(time(NULL));
	//Displaying default constructor...
	Character fighter = Character();
	fighter.displayCharacterInfo();


	Character* player = new Character();

	ItemContainer* testBackPack = player->getBackpack();
	ItemContainer* testEquipped = player->getEquippedItems();

	Enhancement str = Enhancement("STRENGTH", 5);
	vector<Enhancement> enhList1 = vector<Enhancement>();
	enhList1.push_back(str);

	Shield* s1 = new Shield("Super Shild", enhList1);
	Shield* s2 = new Shield("Super Awsom Shild", enhList1);
	Armor* ar1 = new Armor("GREAT AMOR", 4);

	int index = testBackPack->addItem(s1);
	testBackPack->addItem(s2);
	testBackPack->addItem(ar1);
	testBackPack->transfer(testEquipped, index);

	player->displayEquipment();
	testBackPack->displayItems();

	getchar();
	delete player;
	delete testBackPack;
	delete testEquipped;
	delete s1;
	delete s2;
	delete ar1;
	return 0;
}