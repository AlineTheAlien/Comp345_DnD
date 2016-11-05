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
#include "ItemContainer.h"
#include "Armor.h"
#include "Belt.h"
#include "Boots.h"
#include "Helmet.h"
#include "Ring.h"
#include "Shield.h"
#include "Weapon.h"
using namespace CppUnit;
using namespace std;

//! Test Class for the ItemContainer class
//! It must be a subclass of CppUnit::TestFixture
//! It then uses CPPUNIT_TEST_SUITE() to create the test suite, and CPPUNIT_TEST() to include the test methods in the test suite. 
//! CPPUNIT_TEST_SUITE_REGISTRATION() is then used to register the test class in the test registry.
class TestItemContainer : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestItemContainer);
	CPPUNIT_TEST(testAddItem);
	CPPUNIT_TEST(testGetItem);
	CPPUNIT_TEST(testRemoveItem);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp(void);
	void tearDown(void);
protected:
	void testAddItem(void);
	void testGetItem(void);
	void testRemoveItem(void);
private:
	ItemContainer *ItemContainerObject;

};

//! Register for running the test
CPPUNIT_TEST_SUITE_REGISTRATION(TestItemContainer);//most important

//! Test method to test the addItem() method of the ItemContainer class 
//! Test Case: the size of the container is increased by one after adding an item to it
void TestItemContainer::testAddItem(void)
{
	cout << "\nTest case: Add item to a container\n" << endl;
	Armor newItem;
	int OldSize = ItemContainerObject->getItems().size();
	ItemContainerObject->addItem(newItem);
	int NewSize = ItemContainerObject->getItems().size();
	CPPUNIT_ASSERT(OldSize == NewSize - 1);
	return;
}

//! Test method to test the getItem() method of the ItemContainer class 
//! Test Case: if we put an item of a certain type in the container, getItem() will return this object
void TestItemContainer::testGetItem(void)
{
	cout << "\nTest case: Get item from a container\n" << endl;
	vector<Enhancement> influencesofnewitem = vector<Enhancement>();
	Armor newItem(influencesofnewitem);
	ItemContainerObject->addItem(newItem);
	Item retrievedItem = ItemContainerObject->getItem("ARMOR");
	cout << "Type of the retrieved item is: " << retrievedItem.getType() << endl;
	CPPUNIT_ASSERT(newItem.getType() == retrievedItem.getType());
	return;
}

//! Test method to test the removeItem() method of the ItemContainer class 
//! Test Case: the size of the container is decreased by one after removing an item from it
void TestItemContainer::testRemoveItem(void)
{
	cout << "\nTest case: Remove item from a container\n" << endl;
	// Create two items
	Weapon newWeapon(5, 4);
	Ring newRing(3, 4, 0, 1, 2);
	// Add the two items into the container
	ItemContainerObject->addItem(newRing);
	ItemContainerObject->addItem(newWeapon);
	// Keep track of the old size
	int OldSize = ItemContainerObject->getItems().size();
	// Remove an item from the container
	Item retrievedItem = ItemContainerObject->removeItem("WEAPON");
	int NewSize = ItemContainerObject->getItems().size();
	CPPUNIT_ASSERT(NewSize == OldSize - 1);
	return;
}

//! setUp() method that is executed before all the test cases that the test class includes 
void TestItemContainer::setUp(void)
{
	ItemContainerObject = new ItemContainer("TREASURE CHEST");
}

//! tearDown() method that is executed after all the test cases that the test class includes 
void TestItemContainer::tearDown(void)
{
	delete ItemContainerObject;
}
