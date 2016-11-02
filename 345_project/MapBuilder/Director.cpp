#include "Director.h"
#include <fstream>
#include <iostream>
#include <string>

//! Method to construct a map
//! @param fileName : File name of the map to load as a string value
//! @param playerLevel : Level of the current player
void Director::constructMap(string fileName, int playerLevel){
	// Declare variable to store map level
	int mapLevel;

	// Declare variables for map size
	int mapX;
	int mapY;

	// Declare variables for positions (i,j) in map
	int i;
	int j;

	// Declare variable to keep track of number of a part before creation
	int num;

	// Open and read file containing the map
	ifstream mapfile;
	mapfile.open(fileName + ".txt");
	// Read the first integer to get the map level
	mapfile >> mapLevel;
	// Read the next two integers to create a map
	mapfile >> mapX >> mapY;
	mbuilder->createNewMap(mapX, mapY, playerLevel); // build an empty map

	// Read the initial position of the player inside the map
	mapfile >> i >> j;
	mbuilder->buildPlayer(j, i); // build a player using a concrete builder

	// Read the next four integers in the file to create the entrance and exit doors
	mapfile >> i >> j;
	mbuilder->buildDoor(j, i); // build a door using a concrete builder

	// Read the number of walls
	mapfile >> num;

	while (num != 0) {
		mapfile >> i >> j;
		mbuilder->buildWall(j, i); // build all walls one by one using a concrete builder
		num--;
	}
	
	// Read the number of enemies
	mapfile >> num;
	string enemyFile;
	while (num != 0) {
		mapfile >> i >> j;
		mapfile >> enemyFile;
		mbuilder->buildEnemy(j, i, enemyFile);
		num--;
	}

	// Read the number of containers
	mapfile >> num;

	// While there are still containers left to read in the file, it will read the x,y position and build a container.
	// Each chest is stored in a different file, with different numbers of items depending on level. The filename will be read
	// and items can then be accessed from the file and added into the chest.
	while (num != 0) {
		mapfile >> i >> j; // read x,y position of the container
		string chest;
		mapfile >> chest; // read the filename of the chest
		mbuilder->buildContainer(j, i, mapLevel, chest); // build the container
		num--;
	}
	mapfile.close();
}

//! Method to set the map builder for the director
//! @param mb : A pointer to one of the two concrete builders
void Director::setMapBuilder(MapBuilder* mb) {
	mbuilder = mb;
}

//! Method to get the final map product
//! @return A pointer to final map product
Map* Director::getMap() {
	return mbuilder->getMap();
}