//! @file 
//! @brief File containing the Test Class and the Test Methods
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
#include "Item.h"
#include "Armor.h"
#include "Belt.h"
#include "Boots.h"
#include "Helmet.h"
#include "Ring.h"
#include "Shield.h"
#include "Weapon.h"
#include "Enhancement.h"

using namespace CppUnit;
using namespace std;

//! Test Class for the Item class
//! It must be a subclass of CppUnit::TestFixture
//! It then uses CPPUNIT_TEST_SUITE() to create the test suite, and CPPUNIT_TEST() to include the test methods in the test suite. 
//! CPPUNIT_TEST_SUITE_REGISTRATION() is then used to register the test class in the test registry.
class TestItem : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestItem);
	CPPUNIT_TEST(testValidItem);
	CPPUNIT_TEST(testInvalidItem);
	CPPUNIT_TEST(testgetEnhancements);
	CPPUNIT_TEST(testgetEnhancementBonusAndType);
	CPPUNIT_TEST_SUITE_END();
protected:
	void testValidItem(void);
	void testInvalidItem(void);
	void testgetEnhancements(void);
	void testgetEnhancementBonusAndType(void);
};

//! Register for running the test
CPPUNIT_TEST_SUITE_REGISTRATION(TestItem);//most important

//! Test method to test the validateItem() method of the Item class
//! Test Case: calling validateItem() on a valid item should return true 
void TestItem::testValidItem(void)
{
	cout << "\nTest case: Creating a valid belt item.\n" << endl;
	bool test;
	// Create a valid item
	Belt b1 = Belt(1, 2);
	// Test that calling validateItem() returns true
	test = b1.validateItem();
	CPPUNIT_ASSERT(test == true);
	return;
}

//! Test method to test the validateItem() method of the Item class
//! Test Case: calling validateItem() on an invalid item should return false
void TestItem::testInvalidItem(void)
{
	cout << "\nTest case: Creating a shield item with invalid bonus value (7).\n" << endl;
	bool test;
	// Create an invalid item
	Shield s1 = Shield(7);
	// Test that calling validateItem() returns false
	test = s1.validateItem();
	CPPUNIT_ASSERT(test == false);
	return;
}

//! Test method to test the getEnhancements() method of the Item class
//! Test case: calling getEnhancements() will return a vector of enhancements
void TestItem::testgetEnhancements(void)
{
	cout << "\nTest case: Get enhancements of an item\n" << endl;
	// Create an item with enhancements
	Ring r1 = Ring(1, 2, 3, 4, 5);
	// Test that calling getEnhancements() will return a vector of enhancements
	vector<Enhancement> retrievedEnhancements = r1.getEnhancements();
	CPPUNIT_ASSERT(retrievedEnhancements.size() == (r1.getEnhancements()).size());
	return;
}

//! Test method to test the getType and getBonus() method for an enhancement
//! Test case: calling getType() will return the enhancement type and getBonus() will return the enhancement bonus
void TestItem::testgetEnhancementBonusAndType(void)
{
	cout << "\nTest case: Get the first enhancement of an item with its bonus value\n" << endl;

	// Create an item with enhancement values passed as parameters
	Weapon w1 = Weapon(3,4);

	// Test that calling getBonus() and getType() will return the influence bonus of the first enhancement along with
	// its corresponding type
	int bonus = (w1.getEnhancements())[0].getBonus();
	string type = (w1.getEnhancements())[0].getType();

	CPPUNIT_ASSERT((bonus == (w1.getEnhancements())[0].getBonus()) && (type == (w1.getEnhancements())[0].getType()));
	return;
}