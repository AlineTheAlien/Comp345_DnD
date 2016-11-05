//! @file 
//! @brief Driver file to create and execute the test suite 
//!
//! The driver contains both code from 'RunApp.cpp' that was provided with the Cppunittest, and my own driver.
//! I've put both drivers into one main function.
//! To test the test cases: Run the code as is.
//! To test my own driver: Comment out the 'RunApp.cpp' code as specified below, and run the code again.

#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <string>
#include <iostream>
#include <vector>

#include "Item.h"
#include "ItemContainer.h"

#include "Belt.h"
#include "Armor.h"
#include "Boots.h"
#include "Helmet.h"
#include "Ring.h"
#include "Shield.h"
#include "Weapon.h"
#include "Enhancement.h"

using namespace std;
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
	bool wasSuccessful = runner.run();

	getchar();

	// Return error code 1 if one of the tests failed.
	return wasSuccessful ? 0 : 1;


	// Comment out the Cppunit test code above to run the driver below

	int x;

	cout << "Testing Item and Item Container creation..." << endl;
	cout << endl;

	// Create some enhancements manually
	Enhancement e1 = Enhancement("STRENGTH", 1);
	Enhancement e2 = Enhancement("CONSTITUTION", 2);
	Enhancement e3 = Enhancement("ARMOR CLASS", 3);
	Enhancement e4 = Enhancement("DEXTERITY", 4);
	Enhancement e5 = Enhancement("ATTACK BONUS", 5);
	Enhancement e6 = Enhancement("DAMAGE BONUS", 1);
	Enhancement e7 = Enhancement("INTELLIGENCE", 2);
	Enhancement e8 = Enhancement("WISDOM", 3);
	Enhancement e9 = Enhancement("CHARISMA", 4);

	// Create some vectors separately
	vector<Item> listOfItems = vector<Item>();
	vector<Enhancement> helmetEnhancements = vector<Enhancement>();
	vector<Enhancement> ringEnhancements = vector<Enhancement>();
	vector<Enhancement> shieldEnhancements = vector<Enhancement>();

	// Place some enhancements together for a helmet item (intelligence, wisdom, armor class)
	helmetEnhancements.push_back(e7);
	helmetEnhancements.push_back(e8);
	helmetEnhancements.push_back(e3);

	// Place some enhancements together for a ring item (armor class, strength, constitution, wisdom for example)
	ringEnhancements.push_back(e3);
	ringEnhancements.push_back(e1);
	ringEnhancements.push_back(e2);
	ringEnhancements.push_back(e8);

	// Place some enhancements together for a shield item (armor class for example)
	// Added one extra enhancement which is invalid for this type
	shieldEnhancements.push_back(e3);
	shieldEnhancements.push_back(e5);

	// Create some containers
	ItemContainer backPack = ItemContainer("BACKPACK");
	ItemContainer chest = ItemContainer("TREASURE CHEST");
	ItemContainer originContainer = ItemContainer("EQUIPPED");
	ItemContainer recipientContainer = ItemContainer("TREASURE CHEST");

	// Create some items
	Helmet helmet1 = Helmet(helmetEnhancements);
	Ring ring1 = Ring(ringEnhancements);
	Shield shield1 = Shield(shieldEnhancements);

	// Create an item using default constructor
	Armor armor1;

	// Manually add an ARMOR CLASS enhancement
	armor1.addEnhancement(e3);

	// Add some items into containers
	originContainer.addItem(helmet1);
	originContainer.addItem(shield1);
	backPack.addItem(armor1);

	cout << "Transferring a SHIELD item from EQUIPPED to TREASURE CHEST. Here are the current contents of the containers:\n";
	// Display items inside the EQUIPPED container
	originContainer.displayItems();
	recipientContainer.displayItems();

	// Transfer from EQUIPPED to TREASURE CHEST container
	recipientContainer.addItem(originContainer.removeItem("SHIELD")); // Transfer removed item from EQUIPPED into the TREASURE CHEST
																	  // Test the validity of an item
	cout << "Testing validity of a SHIELD and ARMOR item: " << endl;
	if (shield1.validateItem())
	{
		cout << shield1.getType() << " is a valid item." << endl;
	}
	else
		cout << shield1.getType() << " is an invalid item." << endl;

	if (armor1.validateItem())
	{
		cout << armor1.getType() << " is a valid item." << endl;
	}
	else
		cout << armor1.getType() << " is an invalid item." << endl;

	cout << endl;

	// Test getType() method from Enhancement class
	cout << "Display enhancement type of the first enhancement of the item: " << endl;
	cout << (shield1.getEnhancements())[0].getType() << "\n" << endl;

	// Test getBonus() method from Enhancement class
	cout << "Display enhancement bonus of the first enhancement of the item: " << endl;
	cout << (shield1.getEnhancements())[0].getBonus() << "\n" << endl;

	// Display all the enhancements with their corresponding bonus
	cout << "List enhancements of shield1: " << endl;
	shield1.displayEnhancements();
	cout << endl;
	cout << "List enhancements of armor1: " << endl;
	armor1.displayEnhancements();

	cout << endl;
	cin >> x;
}