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
#include "Belt.h"
#include "Boots.h"
#include "Helmet.h"
#include "Ring.h"
#include "Shield.h"
#include "Weapon.h"
#include <ctime>
#include <iostream>
#include "MapObject.h"
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
	player->equipItem(index);
	player->displayEquipment();
	player->unequipItem(0); // item should be in index 0

	player->displayEquipment();
	testBackPack->displayItems();

	// For the purpose of creating items inside container
	MapObject* newChest = new ItemContainer("CHEST");
	int numOfItems = 1;
	cout << "How many items would you like to put inside the chest?" << endl;
	cin >> numOfItems;

	int itemNum = 1;
	string name = "";
	int bonus1 = 2;
	int bonus2 = 2;
	int bonus3 = 2;
	int bonus4 = 2;
	int bonus5 = 2;

	while (numOfItems !=0) {
		cout << "Select item type: " << endl;
		cout << "[1] Armor\n[2] Belt\n[3] Boots\n[4] Helmet\n[5] Ring\n[6] Shield\n[7] Weapon" << endl;
		cin >> itemNum;
		if (itemNum == 1) {
			cout << "Name: ";
			cin >> name;
			cout << "Armor class bonus: ";
			cin >> bonus1;
			cout << "Creating armor...." << endl;
			Armor* armor = new Armor(name, bonus1);
			static_cast<ItemContainer*>(newChest)->addItem(armor);
		}
		else if (itemNum == 2) {
			cout << "Name: ";
			cin >> name;
			cout << "Constitution bonus: ";
			cin >> bonus1;
			cout << "Strength bonus: ";
			cin >> bonus2;
			cout << "Creating Belt...." << endl;
			Belt* belt = new Belt(name, bonus1, bonus2);
			static_cast<ItemContainer*>(newChest)->addItem(belt);
		}
		else if (itemNum == 3) {
			cout << "Name: ";
			cin >> name;
			cout << "Armor class bonus: ";
			cin >> bonus1;
			cout << "Dexterity bonus: ";
			cin >> bonus2;
			cout << "Creating Boots...." << endl;
			Boots* boots = new Boots(name, bonus1, bonus2);
			static_cast<ItemContainer*>(newChest)->addItem(boots);
		}
		else if (itemNum == 4) {
			cout << "Name: ";
			cin >> name;
			cout << "Intelligence bonus: ";
			cin >> bonus1;
			cout << "Wisdom bonus: ";
			cin >> bonus2;
			cout << "Armor class bonus: ";
			cin >> bonus3;
			cout << "Creating Helmet...." << endl;
			Helmet* helmet = new Helmet(name, bonus1, bonus2, bonus3);
			static_cast<ItemContainer*>(newChest)->addItem(helmet);
		}
		else if (itemNum == 5) {
			cout << "Name: ";
			cin >> name;
			cout << "Armor class bonus: ";
			cin >> bonus1;
			cout << "Strength bonus: ";
			cin >> bonus2;
			cout << "Constitution bonus: ";
			cin >> bonus3;
			cout << "Wisdom bonus: ";
			cin >> bonus4;
			cout << "Charisma bonus: ";
			cin >> bonus5;
			cout << "Creating Ring...." << endl;
			Ring* ring = new Ring(name, bonus1, bonus2, bonus3, bonus4, bonus5);
			static_cast<ItemContainer*>(newChest)->addItem(ring);
		}
		else if (itemNum == 6) {
			cout << "Name: ";
			cin >> name;
			cout << "Armor class bonus: ";
			cin >> bonus1;
			cout << "Creating Shield...." << endl;
			Shield* shield = new Shield(name, bonus1);
			static_cast<ItemContainer*>(newChest)->addItem(shield);
		}
		else if (itemNum == 7) {
			cout << "Name: ";
			cin >> name;
			cout << "Attack value: ";
			cin >> bonus1;
			cout << "Damage value: ";
			cin >> bonus2;
			cout << "Creating Weapon...." << endl;
			Weapon* weapon = new Weapon(name, bonus1, bonus2);
			static_cast<ItemContainer*>(newChest)->addItem(weapon);
		}
		numOfItems--;
	}
	static_cast<ItemContainer*>(newChest)->displayItems();

	getchar();
	delete player;
	delete testBackPack;
	delete testEquipped;
	delete s1;
	delete s2;
	delete ar1;
	delete newChest;
	return 0;
}