//! @file 
//! @brief Driver file to create and execute the test suite 
//!
//! Brief instruction on how to set CppUnit:
//! from: http ://www.comp.nus.edu.sg/~cs3215/tools/cppunitAll.html
//!
//!	First, to install cppUnit :
//!
//!	 1. Unpack the CppUnit archive (https://sourceforge.net/projects/cppunit/files/cppunit/1.12.1/) to a directory of your choice, in this example I assume it is D:\. 
//!  2. Go to D:/cppunit-1.12.1/src and open the CppUnitLibraries.dsw in Visual Studio.
//!  3. Select the cppunit project in the Solution Explorer and go to 'Project > Properties > Configuration Properties > Librarian > General. Put "Debug\cppunit.lib" in the ‘Output File’ textbox. 
//!  4. Right-click on the cppunit project in the Solution Explorer pane and choose Build.
//!  5. After successful compilation, D:/cppunit-1.12.1/lib/cppunit.lib is produced which you then need to setup the Visual Studio Linker with (see below).

//!
//! To setup a project from scratch for Compilation / Linking:
//!
//!	  1. Activate 'Project > Properties > C/C++ >  Code Generation > Runtime Library > Multi - threaded Debug DLL'
//!	  2. Go to 'Project > Properties > C/C++ > General'. Put "D:\cppunit-1.12.1\include" in the 'Additional Include Directories' text box.
//!	  3. Go to 'Project > Properties > Linker > Input'. Put "D:\cppunit-1.12.1\lib\cppunit.lib" in the 'Additional Dependences' text box.
//!	  4. Go to 'Project > Properties > Build Events > Post-Build Event'. Put '"$(TargetPath)"' in the 'Command Line' textbox.Put 'Unit Tests...' in the 'Description' textbox.

#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <iostream>
#include <vector>
#include <string>

#include "Map.h"
#include "MapObject.h"
#include "Director.h"
#include "MapBuilder.h"
#include "ConcreteBuilderA.h"
#include "ConcreteBuilderB.h"

using namespace std;
using std::cin;
//! main() function. Entry point of the program
//! It does the following: 
//! 1. Create a test suite object from the registry as populated by the code in the Test Classes
//! 2. Create a test runner that will execute all the tests in the registry
//! 3. (optionally) sets an outputter that will output the results
//! 4. Run the test cases. 
//! Aside from the test cases, it also contains the driver code to be run for the user to view what the program can do.
int main(int argc, char* argv[])
{
	//// Get the top level suite from the registry
	//CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

	//// Adds the test to the list of test to run
	//CppUnit::TextUi::TestRunner runner;
	//runner.addTest(suite);

	//// Change the default outputter to a compiler error format outputter
	//runner.setOutputter(new CppUnit::CompilerOutputter(&runner.result(),
	//	std::cerr));
	//// Run the tests.
	//bool wasSuccessful = runner.run();

	//getchar();

	//// Return error code 1 if one of the tests failed.
	//return wasSuccessful ? 0 : 1;

	//To run CppUnitTest, uncomment the parts above ^^^^ and comment the parts below


	// My implementation of the Driver class is everything below this comment.

	// Create a list of map filenames that already exist
	vector<string> playableMaps = vector<string>();
	playableMaps.push_back("map1");
	playableMaps.push_back("map2");
	playableMaps.push_back("heart");
	playableMaps.push_back("test");
	int playerLevel;
	int choice = 1;
	// Allow user to select a player of either level 3, 5 or 15.
	do {
		cout << "Select a player to start.\n";
		cout << "1- Player Level 3, 2- Player Level 5, 3- Player Level 15\n";
		cin >> choice; 
		if (choice == 1)
			playerLevel = 3;
		else if (choice == 2)
			playerLevel = 5;
		else if (choice == 3)
			playerLevel = 15;
		else {
			cout << "Only select numbers from [1-3] inclusive. Try again." << endl;
		}
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
			cout << i + 1 << "- " << playableMaps[i] << endl; // list all the available maps
		}
		cout << "Choice: ";
		cin >> choice;
		if (choice < 1 || choice > numOfMaps)
			cout << "Invalid map. Try again.\n" << endl;
	} while (choice < 1 || choice > numOfMaps);
	mapName = playableMaps[choice - 1];
	cout << endl;

	// Construct the Map from a specific file by passing the file name in the parameter and current player
	d.constructMap("Maps/" + mapName, playerLevel);
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

	// Delete pointers and call destructors
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