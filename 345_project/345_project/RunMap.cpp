// RunMap.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include "Map.h"

using std::cout;
using std::cin;
using std::endl;


//! main() function. Entry point of the program
//! It does the following: 
//! 1. Create a test suite object from the registry as populated by the code in the Test Classes
//! 2. Create a test runner that will execute all the tests in the registry
//! 3. (optionally) sets an outputter that will output the results
//! 4. Run the test cases. 
//! 5. Tests are commented out. Comment out the driver first to use the test cases

int main(int argc, char* argv[])
{
/**
	// Get the top level suite from the registry
	CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

	// Adds the test to the list of test to run
	CppUnit::TextUi::TestRunner runner;
	runner.addTest(suite);

	// Change the default outputter to a compiler error format outputter
	runner.setOutputter(new CppUnit::CompilerOutputter(&runner.result(),
		std::cerr));

	// Run the tests.
	bool wasSucessful = runner.run();
	getchar();

	// Return error code 1 if the one of test failed.
	return wasSucessful ? 0 : 1;

*/
	int mapSizeX, mapSizeY;
	cout << "Enter number for width of the map : " << endl;
	cin >> mapSizeX;
	cout << "Enter number for length of the map : " << endl;
	cin >> mapSizeY;

	Map map(mapSizeX, mapSizeY);

	for (int i = 0; i < map.getMapY(); i++)
	{
		for (int j = 0; j < map.getMapX(); j++)
		{
			char object;
			cout << "Enter map value at position : " << j +  map.getMapX() * i << endl;
			cout << "Values accepted : E (Enemy), C (Chest), "
				<< "P (Player), W (Wall), D (Door), X (Empty)" << endl;
			cin >> object;
			map.setTile(j, i, object);
			cout << "Current map : " << endl;
			map.showMap();	
		}
	}
	
	
	if (map.validatePath())
		cout << "Map is valid" << endl;
	else
		cout << "Map is invalid" << endl;;
	system("pause");
	map.~Map();
    return 0;

}

