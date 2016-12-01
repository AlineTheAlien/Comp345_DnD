//! @file 
//! @brief Implementation file for UserDrivenEditor class

#include "stdafx.h"
#include "UserDrivenEditor.h"
#include "Director.h"
#include "BullyBuilder.h"
#include "NimbleBuilder.h"
#include "TankBuilder.h"
#include "MonsterBuilder.h"
#include <iostream>
#include <fstream>
using namespace std;

//! Constructor
UserDrivenEditor::UserDrivenEditor()
{


}

//! Method to create a chest
//! @return a pointer to an item container
ItemContainer* UserDrivenEditor::createChest()
{
	MapObject* newChest = new ItemContainer("CHEST");
	int numOfItems = 1;
	string chestName = "";
	string empty = "";
	cout << "Enter chest name: " << endl;
	getline(cin, chestName);
	cout << "How many items would you like to put inside the chest?" << endl;
	cin >> numOfItems;
	int itemNum = 1;
	string name = ""; // to consume any white-space characters
	int bonus1 = 2;
	int bonus2 = 2;
	int bonus3 = 2;
	int bonus4 = 2;
	int bonus5 = 2;

	while (numOfItems > 0) {
		cout << "Select item type: " << endl;
		cout << "[1] Armor\n[2] Belt\n[3] Boots\n[4] Helmet\n[5] Ring\n[6] Shield\n[7] Weapon" << endl;
		cin >> itemNum;
		getline(cin, empty);
		if (itemNum == 1) {
			bool valid = false;
			Item* armor = NULL;
			while (valid == false) {
				cout << "Name: ";
				getline(cin, name);
				cout << "Armor class bonus: ";
				cin >> bonus1;
				cout << "Creating armor...." << endl;
				armor = new Armor(name, bonus1);
				valid = armor->validateItem();
				if (valid == false) {
					cout << "Invalid item. Try again." << endl;
					delete armor;
					getline(cin, empty);
				}
			}
			// Create and open a character archive for output
			//std::ofstream ofs("Items/"+name);

			//// Save data to archive
			//{
			//	boost::archive::binary_oarchive oa(ofs);
			//	// Write class instance to archive
			//	oa << armor;
			//}
			static_cast<ItemContainer*>(newChest)->addItem(armor);
		}
		else if (itemNum == 2) {
			bool valid = false;
			Item* belt = NULL;
			while (valid == false) {
				cout << "Name: ";
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
					getline(cin, empty);
				}
			}
			//// Create and open a character archive for output
			//std::ofstream ofs("Items/" + name);

			//// Save data to archive
			//{
			//	boost::archive::binary_oarchive oa(ofs);
			//	// Write class instance to archive
			//	oa << belt;
			//}
			static_cast<ItemContainer*>(newChest)->addItem(belt);
		}
		else if (itemNum == 3) {
			bool valid = false;
			Item* boots = NULL;
			while (valid == false) {
				cout << "Name: ";
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
					getline(cin, empty);
				}
			}
			//// Create and open a character archive for output
			//std::ofstream ofs("Items/" + name);

			//// Save data to archive
			//{
			//	boost::archive::binary_oarchive oa(ofs);
			//	// Write class instance to archive
			//	oa << boots;
			//}
			static_cast<ItemContainer*>(newChest)->addItem(boots);
		}
		else if (itemNum == 4) {
			bool valid = false;
			Item* helmet = NULL;
			while (valid == false) {
				cout << "Name: ";
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
					getline(cin, empty);
				}
			}
			// Create and open a character archive for output
			//std::ofstream ofs("Items/" + name);

			//// Save data to archive
			//{
			//	boost::archive::binary_oarchive oa(ofs);
			//	// Write class instance to archive
			//	oa << helmet;
			//}
			static_cast<ItemContainer*>(newChest)->addItem(helmet);
		}
		else if (itemNum == 5) {
			bool valid = false;
			Item* ring = NULL;
			while (valid == false) {
				cout << "Name: ";
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
					getline(cin, empty);
				}
			}
			// Create and open a character archive for output
			//std::ofstream ofs("Items/" + name);

			//// Save data to archive
			//{
			//	boost::archive::binary_oarchive oa(ofs);
			//	// Write class instance to archive
			//	oa << ring;
			//}
			static_cast<ItemContainer*>(newChest)->addItem(ring);
		}
		else if (itemNum == 6) {
			bool valid = false;
			Item* shield = NULL;
			while (valid == false) {
				cout << "Name: ";
				getline(cin, name);
				cout << "Armor class bonus: ";
				cin >> bonus1;
				cout << "Creating Shield...." << endl;
				shield = new Shield(name, bonus1);
				valid = shield->validateItem();
				if (valid == false) {
					cout << "Invalid item. Try again." << endl;
					delete shield;
					getline(cin, empty);
				}
			}
			//// Create and open a character archive for output
			//std::ofstream ofs("Items/" + name);

			//// Save data to archive
			//{
			//	boost::archive::binary_oarchive oa(ofs);
			//	// Write class instance to archive
			//	oa << shield;
			//}
			static_cast<ItemContainer*>(newChest)->addItem(shield);
		}
		else if (itemNum == 7) {
			bool valid = false;
			Item* weapon = NULL;
			while (valid == false) {
				cout << "Name: ";
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
					getline(cin, empty);
				}
			}
			// Create and open a character archive for output
			//std::ofstream ofs("Items/" + name);

			//// Save data to archive
			//{
			//	boost::archive::binary_oarchive oa(ofs);
			//	// Write class instance to archive
			//	oa << weapon;
			//}
			static_cast<ItemContainer*>(newChest)->addItem(weapon);
		}
		numOfItems--;
	}
	getline(cin, empty);
	static_cast<ItemContainer*>(newChest)->displayItems();
	// Create and open a character archive for output
	//std::ofstream ofs("Chests/" + chestName);
	//// Save data to archive
	//{
	//	boost::archive::binary_oarchive oa2(ofs);
	//	// Write class instance to archive
	//	oa2 << newChest;
	//}

	return static_cast<ItemContainer*>(newChest);
}

//! Method to create a backpack container. To be added to enemies/npcs during map editing.
//! @return A pointer to an item container
ItemContainer* UserDrivenEditor::createBackpack()
{
	MapObject* newChest = new ItemContainer("BACKPACK");
	int numOfItems = 1;
	string chestName = "";
	string empty = "";
	cout << "How many items would you like to put on this character?" << endl;
	cin >> numOfItems;
	int itemNum = 1;
	string name = ""; // to consume any white-space characters
	int bonus1 = 2;
	int bonus2 = 2;
	int bonus3 = 2;
	int bonus4 = 2;
	int bonus5 = 2;

	while (numOfItems > 0) {
		cout << "Select item type: " << endl;
		cout << "[1] Armor\n[2] Belt\n[3] Boots\n[4] Helmet\n[5] Ring\n[6] Shield\n[7] Weapon" << endl;
		cin >> itemNum;
		getline(cin, empty);
		if (itemNum == 1) {
			bool valid = false;
			Item* armor = NULL;
			while (valid == false) {
				cout << "Name: ";
				getline(cin, name);
				cout << "Armor class bonus: ";
				cin >> bonus1;
				cout << "Creating armor...." << endl;
				armor = new Armor(name, bonus1);
				valid = armor->validateItem();
				if (valid == false) {
					cout << "Invalid item. Try again." << endl;
					delete armor;
					getline(cin, empty);
				}
			}
			// Create and open a character archive for output
			//std::ofstream ofs("Items/"+name);

			//// Save data to archive
			//{
			//	boost::archive::binary_oarchive oa(ofs);
			//	// Write class instance to archive
			//	oa << armor;
			//}
			static_cast<ItemContainer*>(newChest)->addItem(armor);
		}
		else if (itemNum == 2) {
			bool valid = false;
			Item* belt = NULL;
			while (valid == false) {
				cout << "Name: ";
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
					getline(cin, empty);
				}
			}
			//// Create and open a character archive for output
			//std::ofstream ofs("Items/" + name);

			//// Save data to archive
			//{
			//	boost::archive::binary_oarchive oa(ofs);
			//	// Write class instance to archive
			//	oa << belt;
			//}
			static_cast<ItemContainer*>(newChest)->addItem(belt);
		}
		else if (itemNum == 3) {
			bool valid = false;
			Item* boots = NULL;
			while (valid == false) {
				cout << "Name: ";
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
					getline(cin, empty);
				}
			}
			//// Create and open a character archive for output
			//std::ofstream ofs("Items/" + name);

			//// Save data to archive
			//{
			//	boost::archive::binary_oarchive oa(ofs);
			//	// Write class instance to archive
			//	oa << boots;
			//}
			static_cast<ItemContainer*>(newChest)->addItem(boots);
		}
		else if (itemNum == 4) {
			bool valid = false;
			Item* helmet = NULL;
			while (valid == false) {
				cout << "Name: ";
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
					getline(cin, empty);
				}
			}
			// Create and open a character archive for output
			//std::ofstream ofs("Items/" + name);

			//// Save data to archive
			//{
			//	boost::archive::binary_oarchive oa(ofs);
			//	// Write class instance to archive
			//	oa << helmet;
			//}
			static_cast<ItemContainer*>(newChest)->addItem(helmet);
		}
		else if (itemNum == 5) {
			bool valid = false;
			Item* ring = NULL;
			while (valid == false) {
				cout << "Name: ";
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
					getline(cin, empty);
				}
			}
			// Create and open a character archive for output
			//std::ofstream ofs("Items/" + name);

			//// Save data to archive
			//{
			//	boost::archive::binary_oarchive oa(ofs);
			//	// Write class instance to archive
			//	oa << ring;
			//}
			static_cast<ItemContainer*>(newChest)->addItem(ring);
		}
		else if (itemNum == 6) {
			bool valid = false;
			Item* shield = NULL;
			while (valid == false) {
				cout << "Name: ";
				getline(cin, name);
				cout << "Armor class bonus: ";
				cin >> bonus1;
				cout << "Creating Shield...." << endl;
				shield = new Shield(name, bonus1);
				valid = shield->validateItem();
				if (valid == false) {
					cout << "Invalid item. Try again." << endl;
					delete shield;
					getline(cin, empty);
				}
			}
			//// Create and open a character archive for output
			//std::ofstream ofs("Items/" + name);

			//// Save data to archive
			//{
			//	boost::archive::binary_oarchive oa(ofs);
			//	// Write class instance to archive
			//	oa << shield;
			//}
			static_cast<ItemContainer*>(newChest)->addItem(shield);
		}
		else if (itemNum == 7) {
			bool valid = false;
			Item* weapon = NULL;
			while (valid == false) {
				cout << "Name: ";
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
					getline(cin, empty);
				}
			}
			// Create and open a character archive for output
			//std::ofstream ofs("Items/" + name);

			//// Save data to archive
			//{
			//	boost::archive::binary_oarchive oa(ofs);
			//	// Write class instance to archive
			//	oa << weapon;
			//}
			static_cast<ItemContainer*>(newChest)->addItem(weapon);
		}
		numOfItems--;
	}
	getline(cin, empty);
	static_cast<ItemContainer*>(newChest)->displayItems();
	// Create and open a character archive for output
	//std::ofstream ofs("Chests/" + chestName);
	//// Save data to archive
	//{
	//	boost::archive::binary_oarchive oa2(ofs);
	//	// Write class instance to archive
	//	oa2 << newChest;
	//}

	return static_cast<ItemContainer*>(newChest);
}


Character* UserDrivenEditor::createCharacter() {
	string charName;
	bool valid = false;
	int charCreate = 1;
	Director director;
	Character* fighter = new Character();
	CharacterObserver *charobserver;

	do {
		cout << "So you want to create a new character?" << endl;
		cout << "Press 1 to enter ability scores manually, or press 2 to generate by rolling dice." << endl;
		cin >> charCreate;
	} while (charCreate != 1 && charCreate != 2);

	if (charCreate == 2) {

		int characterchoice = 0;
		int levelchoice = 0;

		do {
			cout << "Which type of fighter character would you like to create?" << endl;
			cout << "[0] - Bully Fighter" << endl;
			cout << "[1] - Nimble Fighter" << endl;
			cout << "[2] - Tank Fighter" << endl;

			cin >> characterchoice;

		} while (characterchoice < 0 || characterchoice > 2);

		switch (characterchoice) {
		case 0: {
			CharacterBuilder* bullyBuilder = new BullyBuilder;
			director.setCharacterBuilder(bullyBuilder);
			director.constructCharacter();
			delete fighter;
			fighter = NULL;
			fighter = director.getCharacter();
			break;
		}
		case 1: {
			CharacterBuilder* nimbleBuilder = new NimbleBuilder;
			director.setCharacterBuilder(nimbleBuilder);
			director.constructCharacter();
			delete fighter;
			fighter = NULL;
			fighter = director.getCharacter();
			break;
		}
		case 2: {
			CharacterBuilder* tankBuilder = new TankBuilder;
			director.setCharacterBuilder(tankBuilder);
			director.constructCharacter();
			delete fighter;
			fighter = NULL;
			fighter = director.getCharacter();
			break;
		}
		default: {
			delete fighter;
			fighter = NULL;
			fighter = new Character;
		}
		}

		cout << "\nWhat is the level of your character? Enter 0 to start from the lowest level." << endl;

		cin >> levelchoice;

		for (int i = 0; i < levelchoice; i++) {
			fighter->userChoiceLevelUp();
		}

		while (valid == false) {
			charobserver = new CharacterObserver(fighter);
			valid = fighter->validateNewCharacter();
			if (valid == false) {
				delete fighter;
				fighter = NULL;
				delete charobserver;
				charobserver = NULL;
			}
			else {
				cout << "What is your character's name?" << endl;
				cin >> charName;
				fighter->setCharacterName(charName);

				fighter->displayCharacterInfo();
				fighter->displayEquipment();
			}
		}
		cout << "Character with name " << fighter->getCharacterName() << " has been created!" << endl;
	}

	else if (charCreate == 1) {
		while (valid == false) {
			int str = 0;
			int dex = 0;
			int con = 0;
			int intel = 0;
			int wis = 0;
			int cha = 0;
			while (str < 3 || str > 18) {
				cout << "What would you like to have as the Strength Score of your character?" << endl;
				cout << "Strength Score must be at least 3, and at most 18." << endl;
				cin >> str;
			}
			while (dex < 3 || dex > 18) {
				cout << "What would you like to have as the Dexterity Score of your character?" << endl;
				cout << "Dexterity Score must be at least 3, and at most 18." << endl;
				cin >> dex;
			}
			while (con < 3 || con > 18) {
				cout << "What would you like to have as the Constitution Score of your character?" << endl;
				cout << "Constitution Score must be at least 3, and at most 18." << endl;
				cin >> con;
			}
			while (intel < 3 || intel > 18) {
				cout << "What would you like to have as the Intelligence Score of your character?" << endl;
				cout << "Intelligence Score must be at least 3, and at most 18." << endl;
				cin >> intel;
			}
			while (wis < 3 || wis > 18) {
				cout << "What would you like to have as the Wisdom Score of your character?" << endl;
				cout << "Wisdom Score must be at least 3, and at most 18." << endl;
				cin >> wis;
			}
			while (cha < 3 || cha > 18) {
				cout << "What would you like to have as the Charisma Score of your character?" << endl;
				cout << "Charisma Score must be at least 3, and at most 18." << endl;
				cin >> cha;
			}
			//delete fighter;
			fighter = NULL;
			fighter = new Character('P', str, dex, con, intel, wis, cha);
			charobserver = new CharacterObserver(fighter);
			valid = fighter->validateNewCharacter();
			if (valid == false) {
				delete fighter;
				delete charobserver;
			}
			else {
				cout << "What is your character's name?" << endl;
				cin >> charName;
				fighter->setCharacterName(charName);

				fighter->displayCharacterInfo();
				fighter->displayEquipment();
			}
		}
		cout << "Character with name " << fighter->getCharacterName() << " has been created!" << endl;
	}
	return fighter;
}

UserDrivenEditor::~UserDrivenEditor()
{
}
