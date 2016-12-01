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
#include "stdafx.h"
#include "Map.h"
#include "Character.h"
#include "MapObject.h"
#include "ItemContainer.h"
using namespace CppUnit;
using std::cout;
using std::cin;
using std::endl;

class TestMap : public CppUnit::TestFixture
{

	CPPUNIT_TEST_SUITE(TestMap);
	CPPUNIT_TEST(testConstructor);
	CPPUNIT_TEST(testsetTile);
	CPPUNIT_TEST(testMapTileFilled);
	CPPUNIT_TEST(testMapTileEmpty);
	CPPUNIT_TEST(testValidPath);
	CPPUNIT_TEST(testInvalidPath);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();
protected:
	void testConstructor();
	void testsetTile();
	void testMapTileFilled();
	void testMapTileEmpty();
	void testValidPath();
	void testInvalidPath();
private:
	Map *map;
};
//! cppunit registry creation
CPPUNIT_TEST_SUITE_REGISTRATION(TestMap);

//! method called before every test case in this test class
void TestMap::setUp()
{
	map = new Map(5, 5);
}

//! method called after every test case in this test class
void TestMap::tearDown()
{
	delete map;
}

//! test method to test the map(int, int) constructor of the Map class
//! Test Case: returned values of the width and length should be true
//! Tested item: Map::Map(int, int)
void TestMap::testConstructor()
{
	Map newMap(5, 4);
	cout << "Testing overloaded constructor with parameters X = 5, Y = 4" << endl;
	newMap.showMap();
	CPPUNIT_ASSERT(newMap.getMapY() == 4);
	CPPUNIT_ASSERT(newMap.getMapX() == 5);
}

//! test method to test the setTile(int, int, char) method of the Map class
//! Test Case: returned value should be true
//! Tested item: Map::setTile()
void TestMap::testsetTile()
{
	MapObject* chest = new ItemContainer("CHEST");
	map->setTile(2, 2, chest);
	cout << "Testing if tile contains a C (Chest) at position 2,2" << endl;
	map->showMap();
	char type = chest->getObjectType();
	cout << type << endl;
	CPPUNIT_ASSERT(map->getTile(2, 2) == 'C');
}
//! test method to test the isOccupied() method of the Map class 
//! Test Case: the returned value should be true after filling the tile
//! Tested item: Map::isOccupied()
void TestMap::testMapTileFilled()
{
	MapObject* wall = new MapObject('W');
	// context: set a tile
	map->setTile(1, 1,wall);
	cout << "Testing if tile is occupied (W) at position 1,1" << endl;
	map->showMap();
	//test: isOccupied() should return true after the tile was not set
	CPPUNIT_ASSERT(true == map->isOccupied(1, 1));
}

//! test method to test the isOccupied() method of the Map class 
//! Test Case: the returned value should be true after emptying the tile
//! Tested item: Map::isOccupied()
void TestMap::testMapTileEmpty()
{
	// context: make a tile empty
	map->setTile(1, 1, NULL);
	cout << "Testing if tile is empty (X) at position 1,1" << endl;
	map->showMap();
	// test: isOccupied() should return false if the tile was not set
	CPPUNIT_ASSERT(false == map->isOccupied(1, 1));
}

//! test method to test the validatePath() method of the Map class 
//! Test Case: the returned value should be true if there is a valid path in the map
//! Tested item: Map::validatePath()
void TestMap::testValidPath()
{
	// context: create a map with a valid path
	for (int i = 0; i < map->getMapX(); i++)
		for (int j = 0; j < map->getMapY(); j++)
			map->setTile(i, j, NULL);

	MapObject* player = new Character();
	MapObject* door = new MapObject('D');
	map->setTile(0, 0, player);
	map->setTile(map->getMapX() - 1, map->getMapY() - 1, door);
	cout << "Testing if valid path" << endl;
	map->showMap();
	// test: validatePath() should return true
	CPPUNIT_ASSERT(true == map->validatePath());
}

//! test method to test the validatePath() method of the Map class 
//! Test Case: the returned value should be false if there is no valid path in the map
//! Tested item: Map::validatePath()
void TestMap::testInvalidPath()
{
	MapObject* wall = new MapObject('W');
	// context: create a map without a valid path
	for (int i = 0; i < map->getMapX(); i++)
		for (int j = 0; j < map->getMapY(); j++)
			map->setTile(i, j, wall);
	MapObject* player = new Character();
	MapObject* door = new MapObject('D');
	map->setTile(0, 0, player);
	map->setTile(map->getMapX() - 1, map->getMapY() - 1, door);
	cout << "Testing if invalid path" << endl;
	map->showMap();
	// test: validatePath() should return false
	CPPUNIT_ASSERT(false == map->validatePath());
}