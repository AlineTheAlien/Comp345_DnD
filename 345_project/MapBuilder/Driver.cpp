#include <iostream>
#include <vector>
#include <string>

#include "Map.h"
#include "MapObject.h"
#include "Director.h"
#include "MapBuilder.h"
#include "ConcreteBuilderA.h"
#include "ConcreteBuilderB.h"

using std::cout;
using std::cin;
using std::endl;

//! Main function which is the 'Client' for the Builder design pattern.
int main()
{
	// Create a list of map filenames that already exist
	vector<string> playableMaps = vector<string>();
	playableMaps.push_back("map1");
	playableMaps.push_back("map2");
	playableMaps.push_back("heart");
	int playerLevel;
	int choice;

	// Allow user to select a player of either level 3, 5 or 15.
	do {
		cout << "Select a player to start." << endl;
		cout << "1- Player Level 3, 2- Player Level 5, 3- Player Level 15" << endl;
		cin >> choice;
		if (choice == 1)
			playerLevel = 3;
		else if (choice == 2)
			playerLevel = 5;
		else if (choice == 3)
			playerLevel = 15;
		else
			cout << "Only select numbers from [1-3] inclusive. Try again." << endl;
		cout << endl;
	} while (choice < 1 || choice > 3);
		
	
	Director d; // Director who controls the process
	MapBuilder* A = new ConcreteBuilderA(); // Instantiate a concrete builder
	MapBuilder* B = new ConcreteBuilderB(); // Instantiate another concrete builder

	// Prompt user to choose between loading map as saved or load a map adapted to the player's level
	cout << "What would you like to do?\n1- Load map as saved, 2- Load map adapted to player's level" << endl;
	cin >> choice;
	if (choice == 1)
	{
		d.setMapBuilder(A); // set the map builder to the one used for map editor
	}
	else if (choice == 2)
	{
		d.setMapBuilder(B); // set the map builder to the one that will adapt to player's level
	}

	string mapName;
	int numOfMaps = playableMaps.size();

	// Prompt user to choose a map. Keep asking until user enters a valid map name
	do {
		cout << "Which map would you like to load? Available maps are: " << endl;
		for (int i = 0; i < numOfMaps; i++)
		{
			cout << i+1 << "- " << playableMaps[i] << endl; // list all the available maps
		}
		cout << "Choice: ";
		cin >> choice;
		if (choice < 1 || choice > numOfMaps)
			cout << "Invalid map. Try again.\n" << endl;
	} while (choice < 1 || choice > numOfMaps);
	mapName = playableMaps[choice - 1];
	cout << endl;

	// Construct the Map from a specific file by passing the file name in the parameter and current player
	d.constructMap("Maps/"+mapName, playerLevel); 
	Map* map = d.getMap(); // Final product
	int i;
	int j;

	while (true) {
		cout << "Map loaded: " << endl;
		map->showMap(); // Display the map that was just built with builder pattern
		cout << "Enter a value for x and y to view object at position (x,y).\nEnter a negative number to quit." << endl;
		cout << "The following positions contain an object: " << endl;
		map->displayTakenPositions();
		cin >> i;
		if (i < 0)
			break;
		cin >> j;
		if (i < 0)
			break;
		map->displayObjectAtPosition(j, i);
	} 
	
	delete A;
	A = NULL;
	delete B;
	B = NULL;

	map->~Map();
	cout << "Map is deleted... " << endl;
	map->showMap();

	int z;
	cin >> z;
	return 0;
}

