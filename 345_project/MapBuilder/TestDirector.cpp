//! @file 
//! @brief File containing the Test Class for the Director class and the Test Methods
//!
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

#include "Map.h"
#include "MapObject.h"
#include "Director.h"
#include "MapBuilder.h"
#include "ConcreteBuilderA.h"
#include "ConcreteBuilderB.h"
#include "Character.h"

using namespace CppUnit;
using namespace std;

//! Test Class for the Director class
//! It must be a subclass of CppUnit::TestFixture
//! It then uses CPPUNIT_TEST_SUITE() to create the test suite, and CPPUNIT_TEST() to include the test methods in the test suite. 
//! CPPUNIT_TEST_SUITE_REGISTRATION() is then used to register the test class in the test registry.
class TestDirector : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestDirector);
	CPPUNIT_TEST(testConstructMap);
	CPPUNIT_TEST(testAdaptMapLevel);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp(void);
	void tearDown(void);
protected:
	void testConstructMap(void);
	void testAdaptMapLevel(void);
private:
	MapBuilder* mbA;
	MapBuilder* mbB;
	Director d;
};

//! Register for running the test
CPPUNIT_TEST_SUITE_REGISTRATION(TestDirector);

//! Test method to test the constructMap(..) method of the Director class 
//! Test Case: The map read and constructed from the file should have the same number of objects as in the txt file
void TestDirector::testConstructMap(void)
{
	const int numOfObjects = 4; // There should be 4 objects in the file to be read.
	const int playerLevel = 15;
	d.setMapBuilder(mbA);
	d.constructMap("Maps/test", playerLevel); // Read from file "Maps/test.txt" and passing level of player into the parameter
	Map* testMap = d.getMap();
	// Get the number of objects currently in the map after loading it
	// Method will loop through the array and a counter increases if an object exists in a tile
	int num = testMap->getNumOfOccupiedTiles();

	CPPUNIT_ASSERT(numOfObjects == num);
}

//! Test method to test whether level of an enemy is adapted to player's level using ConcreteBuilderB
//! Test Case: The enemy create with ConcreteBuilderB should be of different level than the enemy created with ConcreteBuilderA
//! and it should have the same level as the player's level
void TestDirector::testAdaptMapLevel(void)
{
	const int playerLevel = 15;
	d.setMapBuilder(mbA);
	// Construct a map with ConcreteBuilderA reading the same file
	d.constructMap("Maps/test", playerLevel); // Enemy in file is of level 5, player is level 15 and this is passed as parameter to the constructMap method
	Map* testMap1 = d.getMap(); // Get the map product
	MapObject* p1 = testMap1->getTile(1, 1); // Enemy created should be at position (1,1)

	// Construct a map with ConcreteBuilderB reading the same file
	MapBuilder* mbB = new ConcreteBuilderB(); // Use of ConcreteBuilderB which adapts map to player's level
	d.setMapBuilder(mbB);
	d.constructMap("Maps/test", playerLevel); // Enemy in file is of level 5, player is level 15 and this is passed as parameter to the constructMap method
	Map* testMap2 = d.getMap(); // Get the map product
	MapObject* p2 = testMap2->getTile(1, 1); // Enemy created should be at position (1,1)

	// Get the level of the enemy created using ConcreteBuilderA vs ConcreteBuilderB
	int level1 = static_cast<Character*>(p1)->getLevel();
	int level2 = static_cast<Character*>(p2)->getLevel();

	CPPUNIT_ASSERT((level1 != level2) && (level2 == playerLevel));
}

//! setUp() method that is executed before all the test cases that the test class includes 
void TestDirector::setUp(void)
{
	mbA = new ConcreteBuilderA();
	mbB = new ConcreteBuilderB();
}

//! tearDown() method that is executed after all the test cases that the test class includes 
void TestDirector::tearDown(void)
{
	delete mbA;
	delete mbB;
}
