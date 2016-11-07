// DungeonsAndDragons.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ItemContainer.h"
#include "CharacterObserver.h"
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
#include <string>
using namespace std;


int main()
{
	srand(time(NULL));
	//Displaying default constructor...
	//Character fighter = Character();
	//fighter.displayCharacterInfo();

	Character* player = new Character();
	CharacterObserver *charobv = new CharacterObserver(player);

	player->displayCharacterInfo();
	player->displayEquipment();

	ItemContainer* testBackPack = player->getBackpack();
	ItemContainer* testEquipped = player->getEquippedItems();

	Enhancement str = Enhancement("ARMOR CLASS", 5);
	vector<Enhancement> enhList1 = vector<Enhancement>();
	enhList1.push_back(str);

	Shield* s1 = new Shield("Super Shild", enhList1);
	//Shield* s2 = new Shield("Super Awsom Shild", enhList1);
	//Armor* ar1 = new Armor("GREAT AMOR", 4);

	int index = testBackPack->addItem(s1);
	//testBackPack->addItem(s2);
	//testBackPack->addItem(ar1);
	player->equipItem(index);
	//player->displayEquipment();
	player->unequipItem(0); // item should be in index 0

	//player->displayEquipment();
	//testBackPack->displayItems();

	// For the purpose of creating items inside container
	MapObject* newChest = new ItemContainer("CHEST");
	int numOfItems = 1;
	cout << "How many items would you like to put inside the chest?" << endl;
	cin >> numOfItems;

	int itemNum = 1;
	string name = "";
	string empty = ""; // to consume any white-space characters
	int bonus1 = 2;
	int bonus2 = 2;
	int bonus3 = 2;
	int bonus4 = 2;
	int bonus5 = 2;

	while (numOfItems > 0) {
		cout << "Select item type: " << endl;
		cout << "[1] Armor\n[2] Belt\n[3] Boots\n[4] Helmet\n[5] Ring\n[6] Shield\n[7] Weapon" << endl;
		cin >> itemNum;
		if (itemNum == 1) {
			bool valid = false;
			Armor* armor = NULL;
			while (valid == false) {
				cout << "Name: ";
				getline(cin, empty);
				getline(cin, name);
				cout << "Armor class bonus: ";
				cin >> bonus1;
				cout << "Creating armor...." << endl;
				armor = new Armor(name, bonus1);
				valid = armor->validateItem();
				if (valid == false) {
					cout << "Invalid item. Try again." << endl;
					delete armor;
				}
			}
			static_cast<ItemContainer*>(newChest)->addItem(armor);
		}
		else if (itemNum == 2) {
			bool valid = false;
			Belt* belt = NULL;
			while (valid == false) {
				cout << "Name: ";
				getline(cin, empty);
				getline(cin, name);
				cout << "Constitution bonus: ";
				cin >> bonus1;
				cout << "Strength bonus: ";
				cin >> bonus2;
				cout << "Creating Belt...." << endl;
				belt = new Belt(name, bonus1, bonus2);
				valid = belt->validateItem();
				if (valid == false) {
					cout << "Invalid item. Try again." << endl;
					delete belt;
				}
			}
			static_cast<ItemContainer*>(newChest)->addItem(belt);
		}
		else if (itemNum == 3) {
			bool valid = false;
			Boots* boots = NULL;
			while (valid == false) {
				cout << "Name: ";
				getline(cin, empty);
				getline(cin, name);
				cout << "Armor class bonus: ";
				cin >> bonus1;
				cout << "Dexterity bonus: ";
				cin >> bonus2;
				cout << "Creating Boots...." << endl;
				boots = new Boots(name, bonus1, bonus2);
				valid = boots->validateItem();
				if (valid == false) {
					cout << "Invalid item. Try again." << endl;
					delete boots;
				}
			}
			static_cast<ItemContainer*>(newChest)->addItem(boots);
		}
		else if (itemNum == 4) {
			bool valid = false;
			Helmet* helmet = NULL;
			while (valid == false) {
				cout << "Name: ";
				getline(cin, empty);
				getline(cin, name);
				cout << "Intelligence bonus: ";
				cin >> bonus1;
				cout << "Wisdom bonus: ";
				cin >> bonus2;
				cout << "Armor class bonus: ";
				cin >> bonus3;
				cout << "Creating Helmet...." << endl;
				helmet = new Helmet(name, bonus1, bonus2, bonus3);
				valid = helmet->validateItem();
				if (valid == false) {
					cout << "Invalid item. Try again." << endl;
					delete helmet;
				}
			}
			static_cast<ItemContainer*>(newChest)->addItem(helmet);
		}
		else if (itemNum == 5) {
			bool valid = false;
			Ring* ring = NULL;
			while (valid == false) {
				cout << "Name: ";
				getline(cin, empty);
				getline(cin, name);
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
				ring = new Ring(name, bonus1, bonus2, bonus3, bonus4, bonus5);
				valid = ring->validateItem();
				if (valid == false) {
					cout << "Invalid item. Try again." << endl;
					delete ring;
				}
			}
			static_cast<ItemContainer*>(newChest)->addItem(ring);
		}
		else if (itemNum == 6) {
			bool valid = false;
			Shield* shield = NULL;
			while (valid == false) {
				cout << "Name: ";
				getline(cin, empty);
				getline(cin, name);
				cout << "Armor class bonus: ";
				cin >> bonus1;
				cout << "Creating Shield...." << endl;
				shield = new Shield(name, bonus1);
				valid = shield->validateItem();
				if (valid == false) {
					cout << "Invalid item. Try again." << endl;
					delete shield;
				}
			}
			static_cast<ItemContainer*>(newChest)->addItem(shield);
		}
		else if (itemNum == 7) {
			bool valid = false;
			Weapon* weapon = NULL;
			while (valid == false) {
				cout << "Name: ";
				getline(cin, empty);
				getline(cin, name);
				cout << "Attack value: ";
				cin >> bonus1;
				cout << "Damage value: ";
				cin >> bonus2;
				cout << "Creating Weapon...." << endl;
				weapon = new Weapon(name, bonus1, bonus2);
				valid = weapon->validateItem();
				if (valid == false) {
					cout << "Invalid item. Try again." << endl;
					delete weapon;
				}
			}
			static_cast<ItemContainer*>(newChest)->addItem(weapon);
		}
		numOfItems--;
	}
	static_cast<ItemContainer*>(newChest)->displayItems();

	system("PAUSE");
	getchar();

	delete player;
	//delete testBackPack;
	//delete testEquipped;
	delete s1;
	//delete s2;
	//delete ar1;
	delete newChest;
	return 0;
}