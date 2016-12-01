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
#include "BullyBuilder.h"
#include "TankBuilder.h"
#include "Director.h"
#include <stdio.h>
#include <math.h> 
using namespace CppUnit;
using namespace std;

//! Test Class for the Strategy class and its subclasses
class TestCharacter : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestCharacter);
	CPPUNIT_TEST(testEquipItem);
	CPPUNIT_TEST(testUnequipItem);
	CPPUNIT_TEST(testBuilderCreation);
	CPPUNIT_TEST(testNumberOfAttacks);
	CPPUNIT_TEST_SUITE_END();
protected:
	void testAggressorStrategy();
	void testEquipItem();
	void testUnequipItem();
	void testBuilderCreation();
	void testNumberOfAttacks();
};

//!Register for running the test
CPPUNIT_TEST_SUITE_REGISTRATION(TestCharacter);//most important


//! Test case to ensure that the builder is correctly assigning ability scores
//! Test Case: A properly build character should have all of its ability scores in the [3,18] interval
//! Tested item: Director::constructCharacter()
void TestCharacter::testBuilderCreation() {
	Director director;
	Character* myCharacter;
	CharacterBuilder* bullybuilder = new BullyBuilder();
	director.setCharacterBuilder(bullybuilder);
	director.constructCharacter();
	myCharacter = director.getCharacter();
	CPPUNIT_ASSERT(myCharacter->validateNewCharacter());
}

//! Test case to ensure that the number of attacks/round increases by one every 5 levels
//! Test Case: A correct implementation of numofattacks/round is if it increases by one per 5 levels
//! Tested item: Character::levelUp()
void TestCharacter::testNumberOfAttacks() {
	Director director;
	Character* myCharacter;
	CharacterBuilder* tankbuilder = new TankBuilder();
	director.setCharacterBuilder(tankbuilder);
	director.constructCharacter();
	myCharacter = director.getCharacter();

	for (int i = 0; i < 21; i++) {
		myCharacter->levelUp();
	}
	CPPUNIT_ASSERT(myCharacter->getNumberOfAttacks() == 5);
}


//! Test method to test character equip an item
//! Test Case: When character equips an item, the size of 'equipped' array should increase, and the size of 'backpack' should decrease
void TestCharacter::testEquipItem()
{
	
}

//! Test method to test character unequip an item
//! Test Case: When character unequip an item, the size of 'equipped' array should decrease, and the size of 'backpack' should increase
void TestCharacter::testEquipItem()
{

}