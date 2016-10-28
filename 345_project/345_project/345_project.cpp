//! @file 
//! @brief Entry point for the console application

#include "stdafx.h"
#include "Character.h"
#include <iostream>
#include <ctime>
#include <string>
using namespace std;


/*

int main()
{
	//Initializes the seed used for the random dice rolls
	srand(time(NULL));

	//Displaying default constructor...
	Character fighter = Character();
	fighter.displayCharacterInfo();
	fighter.displayEquipment();

	if (fighter.validateNewCharacter()) {
		std::cout << "\nThis character  is valid!\n\n" << endl;
	}
	else {
		std::cout << "\nThis character  is invalid!\n\n" << endl;
	}

	//Displaying nondefault constructor...
	Character fighter2 = Character(17, 16, 13, 9, 9, 10);
	fighter2.displayCharacterInfo();
	fighter2.displayEquipment();

	if (fighter.validateNewCharacter()) {
		std::cout << "\nThis character  is valid!\n\n" << endl;
	}
	else {
		std::cout << "\nThis character  is invalid!\n\n" << endl;
	}

	getchar();
	return 0;
}

*/
//All code below this is the main function to run the test cases
//Code should be uncommented to be executed, and the driver's main function should be commented



#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

//! main() function. Entry point of the program
//! It does the following: 
//! 1. Create a test suite object from the registry as populated by the code in the Test Classes
//! 2. Create a test runner that will execute all the tests in the registry
//! 3. (optionally) sets an outputter that will output the results
//! 4. Run the test cases. 
int main(int argc, char* argv[])
{
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
}

