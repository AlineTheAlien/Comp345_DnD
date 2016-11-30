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
#include "Character.h"
#include "MapObject.h"
#include "ItemContainer.h"
#include "Armor.h"
#include "Weapon.h"
#include <stdio.h>
#include <math.h> 
using namespace CppUnit;
using namespace std;

//! Test Class for the Strategy class and its subclasses
class TestStrategy : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestStrategy);
	CPPUNIT_TEST(testEquipItem);
	CPPUNIT_TEST(testUnequipItem);
	CPPUNIT_TEST_SUITE_END();
protected:
	void testAggressorStrategy();
};

//!Register for running the test
CPPUNIT_TEST_SUITE_REGISTRATION(TestStrategy);//most important

//! Test method to test character equip an item
//! Test Case: When character equips an item, the size of 'equipped' array should increase, and the size of 'backpack' should decrease
void TestStrategy::testEquipItem()
{
	
}

//! Test method to test character unequip an item
//! Test Case: When character unequip an item, the size of 'equipped' array should decrease, and the size of 'backpack' should increase
void TestStrategy::testEquipItem()
{

}