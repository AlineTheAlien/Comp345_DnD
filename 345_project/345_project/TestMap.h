#pragma once
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
#include "stdafx.h"
using namespace CppUnit;


//! Test Class for the Map class
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