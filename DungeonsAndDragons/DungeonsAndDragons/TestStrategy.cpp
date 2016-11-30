//! @file 
//! @brief File containing the Test Class and the Test Methods
//!
//! It must be a subclass of CppUnit::TestFixture
//! It then uses CPPUNIT_TEST_SUITE() to create the test suite, and CPPUNIT_TEST() to include the test methods in the test suite. 
//! CPPUNIT_TEST_SUITE_REGISTRATION() is then used to register the test class in the test registry.
#include <iostream>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include "Combat.h"
#include "Character.h"
#include "Map.h"
#include "MapObject.h"
#include "Strategy.h"
#include "HumanPlayerStrategy.h"
#include "AggressorStrategy.h"
#include "FriendlyStrategy.h"
#include <stdio.h>
#include <math.h> 
using namespace CppUnit;
using namespace std;

//! Test Class for the Strategy class and its subclasses
class TestStrategy : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestStrategy);
	CPPUNIT_TEST(testAggressiveStrategy);
	CPPUNIT_TEST_SUITE_END();
protected:
	void testAggressiveStrategy();
};

//!Register for running the test
CPPUNIT_TEST_SUITE_REGISTRATION(TestStrategy);//most important

//! Test method to test the execute function for the aggressive strategy.
//! Test Case: calling execute(..) method from the AggressiveStrategy class will have the enemy not occupy
//! the same position on the map and move towards the player. Distance between the two characters should be smaller.
//! It will also reduce player's HP if attack is successful, unless the enemy rolls a 1 for attack roll.
void TestStrategy::testAggressiveStrategy()
{
	cout << "\nTEST 2\n" << endl;
	// Create two characters, a player and an enemy
	MapObject* player = new Character('P', 12, 12, 12, 12, 12, 12);
	MapObject* enemy = new Character('E', 5, 5, 5, 5, 5, 5);

	// Player's first HP
	int playerHP = static_cast<Character*>(player)->getHitPoints();

	// Set player's armor class to 0 such that its armor class is low, giving all the chances to enemy to attack
	static_cast<Character*>(player)->setArmorClass(0);

	// Create a map
	Map* map = new Map(4, 4);

	// Set characters on the map
	map->setTile(0, 0, player);
	map->setTile(3, 3, enemy);

	// Display initial map
	map->showMap();

	// NPC execute an aggressive strategy. Its position should be closer to the player and it should
	static_cast<Character*>(enemy)->executeStrategy(map, enemy, player);

	// Calculate the distance
	double firstDistance = sqrt(pow((3 - 0), 2) + pow((3 - 0), 2));
	cout << "First distance: " << firstDistance << endl;
	// Get the new x,y, position of the npc on the map using a simple getter method as these values are stored in
	// the character's attributes
	int x = static_cast<Character*>(enemy)->getMapX();
	int y = static_cast<Character*>(enemy)->getMapY();

	// Calculate the new distance after NPC moved
	double secondDistance = sqrt(pow((x - 0), 2) + pow((y - 0), 2));
	cout << "Second distance: " << secondDistance << endl;

	cout << "Player's initial HP: " << playerHP << endl;

	// Player's HP after getting attacked
	int newPlayerHP = static_cast<Character*>(player)->getHitPoints();
	cout << "Player's new HP: " << newPlayerHP << endl;

	// Info can be viewed in the console. If enemy rolled a 1, rerun the test again to see other possibilities.
	CPPUNIT_ASSERT((firstDistance > secondDistance) && (newPlayerHP <= playerHP));
}