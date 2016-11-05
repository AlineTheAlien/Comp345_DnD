//! @file 
//! @brief Implementation file for the ConcreteBuilderA class  
//!
#include "ConcreteBuilderA.h"
#include "Character.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

//! Method to build a single wall
//! @param x : Position x on the map of the wall as an integer value
//! @param y : Position x on the map of the wall as an integer value
void ConcreteBuilderA::buildWall(int x, int y)
{
	// Create a wall object
	MapObject* wall = new MapObject('W');
	// Place object on the map
	map->setTile(x,y,wall);
}

//! Method to build a single door
//! @param x : Position x on the map of the door as an integer value
//! @param y : Position x on the map of the door as an integer value
void ConcreteBuilderA::buildDoor(int x, int y)
{
	// Create a door object
	MapObject* door = new MapObject('D');
	// Place the object on the map
	map->setTile(x,y,door);
}

//! Method to build a single enemy character
//! @param x : Position x on the map of the character as an integer value
//! @param y : Position x on the map of the character as an integer value
//! @param enemyFile : File name of the file that contains the enemy as a string value
void ConcreteBuilderA::buildEnemy(int x, int y, string enemyFile)
{
	// Open and read file containing the enemy
	ifstream myfile;
	myfile.open(enemyFile);
	int level, currentHP, totalHP, str, dex, con, intel, wis, cha;
	myfile >> level >> currentHP >> totalHP >> str >> dex >> con >> intel >> wis >> cha;

	// Create an enemy
	MapObject* enemy = new Character('E', level, currentHP, totalHP, str, dex, con, intel, wis, cha);

	// Place the object on the map
	map->setEnemy(x, y, enemy);

	myfile.close();
}

//! Method to build a single player character
//! @param x : Position x on the map of the character as an integer value
//! @param y : Position x on the map of the character as an integer value
void ConcreteBuilderA::buildPlayer(int x, int y)
{
	// Get the right path to the player's file at the right level
	string actualFile = "";
	actualFile += "Characters/playerlvl" + to_string(playerLevel);

	// Open and read file containing the player
	ifstream myfile;
	myfile.open(actualFile + ".txt");
	int level, currentHP, totalHP, str, dex, con, intel, wis, cha;
	myfile >> level >> currentHP >> totalHP >> str >> dex >> con >> intel >> wis >> cha;

	// Create player
	MapObject* currentPlayer = new Character('P', level, currentHP, totalHP, str, dex, con, intel, wis, cha);

	// Place the player on the map
	map->setPlayer(x, y, currentPlayer);

	myfile.close();
}

//! Method to build a single enemy character
//! @param x : Position x on the map of the character as an integer value
//! @param y : Position y on the map of the character as an integer value
//! @param level : Level of the map
//! @param containerFile : File name of the container as a string value
void ConcreteBuilderA::buildContainer(int x, int y, int level, string containerFile)
{
	// Get the right path to the container's file at the right level
	string actualFile = "";
	actualFile += containerFile + "lvl";
	actualFile += to_string(level); // Level of the map is needed since container files are named after the level
	ifstream myfile;
	myfile.open(actualFile + ".txt"); // Open the file for the container, which contains items

	// Read the type of the container. For the purpose of this assignment, there are only chests, but containers could be EQUIPPED or BACKPACK as well.
	string containerType;
	myfile >> containerType;

	// Create a container
	MapObject* container = new ItemContainer(containerType);

	int numOfItems;
	myfile >> numOfItems; // read the number of items

	// While there are still items left in the file, it will keep reading it and create new items. The items will be put into the chest.
	// Here, the items are limited to only RING, WEAPON and BOOTS for the purpose of the assignment.
	while (numOfItems != 0)
	{
		char itemType;
		myfile >> itemType;
		if (itemType == 'R') {
			int a, b, c, d, e;
			myfile >> a >> b >> c >> d >> e; // read all attributes to create a ring
			Item* i = new Item("RING", a, b, c, d, e);
			static_cast<ItemContainer*>(container)->addItem(*i);
			delete i;
		}
		else if (itemType == 'W') {
			int a, b;
			myfile >> a >> b;
			Item* i = new Item("WEAPON", a, b); // read all attributes to create a weapon
			static_cast<ItemContainer*>(container)->addItem(*i);
			delete i;
		}
		else if (itemType == 'B') {
			int a, b;
			myfile >> a >> b;
			Item* i = new Item("BOOTS", a, b); // read all attributes to create a boots
			static_cast<ItemContainer*>(container)->addItem(*i);
			delete i;
		}
		numOfItems--;
	}
	myfile.close();
	// Place the container on the map
	map->setChest(x, y, container);
}