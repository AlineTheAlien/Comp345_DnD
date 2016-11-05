// DungeonsAndDragons.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ItemContainer.h"
#include "Item.h"
#include "Character.h"
#include "Enhancement.h"
#include <Vector>
#include "Shield.h"
using namespace std;


int main()
{
	Character* player = new Character();

	ItemContainer* testBackPack = player->getBackpack();
	ItemContainer* testEquipped = player->getEquippedItems();

	Enhancement str = Enhancement("STRENGTH", 5);
	vector<Enhancement> enhList1 = vector<Enhancement>();
	enhList1.push_back(str);

	Shield s = Shield("Super Shild", enhList1);
	testEquipped->addItem(s);

	testEquipped->transfer(testBackPack, s.getName());

	getchar();
	//wassap
	// :D pull me pull meeeeeeee!!!!!!!! :D i want da super shild!
	return 0;
}