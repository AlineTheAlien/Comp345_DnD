#include "stdafx.h"
#include "TestMap.h"
#include "Map.h"
using namespace CppUnit;
using std::cout;
using std::cin;
using std::endl;

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
	map->setTile(2, 2, map->CHEST);
	cout << "Testing if tile contains a C (Chest) at position 2,2" << endl;
	map->showMap();
	CPPUNIT_ASSERT('C' == map->getTile(2,2));
}
//! test method to test the isOccupied() method of the Map class 
//! Test Case: the returned value should be true after filling the tile
//! Tested item: Map::isOccupied()
void TestMap::testMapTileFilled()
{
	// context: set a tile
	map->setTile(1, 1, 'W');
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
	map->setTile(1, 1, 'X');
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
			map->setTile(i, j, 'X');

	map->setTile(0, 0, 'P');
	map->setTile(map->getMapX() -1, map->getMapY() -1, 'D');
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
	// context: create a map without a valid path
	for (int i = 0; i < map->getMapX(); i++)
		for (int j = 0; j < map->getMapY(); j++)
			map->setTile(i, j, 'W');

	map->setTile(0, 0, 'P');
	map->setTile(map->getMapX()-1, map->getMapY()-1, 'D');
	cout << "Testing if invalid path" << endl;
	map->showMap();
	// test: validatePath() should return false
	CPPUNIT_ASSERT(false == map->validatePath());
}