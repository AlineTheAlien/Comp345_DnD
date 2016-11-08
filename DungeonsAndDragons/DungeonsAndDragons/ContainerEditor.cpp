#include "stdafx.h"
#include "ContainerEditor.h"
#include <iostream>
#include <fstream>
using namespace std;

ContainerEditor::ContainerEditor()
{

}

MapObject* ContainerEditor::createChest()
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
			Armor* armor = NULL;
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
			std::ofstream ofs("Items/"+name);

			// Save data to archive
			{
				boost::archive::binary_oarchive oa(ofs);
				// Write class instance to archive
				oa << armor;
			}
			static_cast<ItemContainer*>(newChest)->addItem(armor);
		}
		else if (itemNum == 2) {
			bool valid = false;
			Belt* belt = NULL;
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
			// Create and open a character archive for output
			std::ofstream ofs("Items/" + name);

			// Save data to archive
			{
				boost::archive::binary_oarchive oa(ofs);
				// Write class instance to archive
				oa << belt;
			}
			static_cast<ItemContainer*>(newChest)->addItem(belt);
		}
		else if (itemNum == 3) {
			bool valid = false;
			Boots* boots = NULL;
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
			// Create and open a character archive for output
			std::ofstream ofs("Items/" + name);

			// Save data to archive
			{
				boost::archive::binary_oarchive oa(ofs);
				// Write class instance to archive
				oa << boots;
			}
			static_cast<ItemContainer*>(newChest)->addItem(boots);
		}
		else if (itemNum == 4) {
			bool valid = false;
			Helmet* helmet = NULL;
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
			std::ofstream ofs("Items/" + name);

			// Save data to archive
			{
				boost::archive::binary_oarchive oa(ofs);
				// Write class instance to archive
				oa << helmet;
			}
			static_cast<ItemContainer*>(newChest)->addItem(helmet);
		}
		else if (itemNum == 5) {
			bool valid = false;
			Ring* ring = NULL;
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
			std::ofstream ofs("Items/" + name);

			// Save data to archive
			{
				boost::archive::binary_oarchive oa(ofs);
				// Write class instance to archive
				oa << ring;
			}
			static_cast<ItemContainer*>(newChest)->addItem(ring);
		}
		else if (itemNum == 6) {
			bool valid = false;
			Shield* shield = NULL;
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
			// Create and open a character archive for output
			std::ofstream ofs("Items/" + name);

			// Save data to archive
			{
				boost::archive::binary_oarchive oa(ofs);
				// Write class instance to archive
				oa << shield;
			}
			static_cast<ItemContainer*>(newChest)->addItem(shield);
		}
		else if (itemNum == 7) {
			bool valid = false;
			Weapon* weapon = NULL;
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
			std::ofstream ofs("Items/" + name);

			// Save data to archive
			{
				boost::archive::binary_oarchive oa(ofs);
				// Write class instance to archive
				oa << weapon;
			}
			static_cast<ItemContainer*>(newChest)->addItem(weapon);
		}
		numOfItems--;
	}
	getline(cin, empty);
	static_cast<ItemContainer*>(newChest)->displayItems();
	// Create and open a character archive for output
	std::ofstream ofs("Chests/" + chestName);
	// Save data to archive
	{
		boost::archive::binary_oarchive oa(ofs);
		// Write class instance to archive
		oa << newChest;
	}
	return newChest;
}

ContainerEditor::~ContainerEditor()
{
}
