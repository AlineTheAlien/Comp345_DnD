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
#include "CharacterObserver.h"
#include "Subject.h"
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
	CPPUNIT_TEST(testValidateNewCharacter);
	CPPUNIT_TEST(testInvalidNewCharacter);
	CPPUNIT_TEST(testHit);
	CPPUNIT_TEST(testLowestDiceRolls);
	CPPUNIT_TEST(testHighestDiceRolls);
	CPPUNIT_TEST(testAbilityModifier);
	CPPUNIT_TEST(testManyObserversAttaching);
	CPPUNIT_TEST(testDetachObserver);
	CPPUNIT_TEST_SUITE_END();
protected:
	void testEquipItem();
	void testUnequipItem();
	void testBuilderCreation();
	void testValidateNewCharacter();
	void testInvalidNewCharacter();
	void testHit();
	void testLowestDiceRolls();
	void testHighestDiceRolls();
	void testAbilityModifier();
	void testManyObserversAttaching();
	void testDetachObserver();
};

//!Register for running the test
CPPUNIT_TEST_SUITE_REGISTRATION(TestCharacter);//most important

//! Test method to test the validateNewCharacter() method of the Character class 
//! Test Case: a valid newly created character should have all its ability scores in the [3-18] range
//! Tested item: Character::validateNewCharacter()
void TestCharacter::testValidateNewCharacter()
{
	Character *conan = new Character('P', 12, 12, 12, 12, 12, 12);
	CPPUNIT_ASSERT(conan->validateNewCharacter());
}

//! test method to test the validateNewCharacter() method of the Character class 
//! Test Case: an invalid newly created character should have any of its ability scores outside the [3-18] range
//! Tested item: Character::validateNewCharacter()
void TestCharacter::testInvalidNewCharacter()
{
	Character *conan = new Character('P', 20, 12, 12, 12, 12, 12);
	CPPUNIT_ASSERT(conan->validateNewCharacter() == false);
}

//! test method to test the hit() method of the Map class 
//! Test Case: a character that has been hit(x) should have its hit points reduced by x 
//! Tested item: Character::hit()
void TestCharacter::testHit()
{
	Character *conan = new Character('P', 12, 12, 12, 12, 12, 12);
	conan->getDamaged(4);
	CPPUNIT_ASSERT(conan->getHitPoints() == 7);
}

//! Test case to ensure that if dice rolls for ability scores were 1, 1, 1, and 1, summing up the highest 3 to a total of 3, that the odd negative ability modifier associated to it is rounded down instead of up.
//! Test Case: A correct ability modifier associated with the lowest possible dice rolls must be -4
//! Tested item: Character::generateAbilityModifiers()
void TestCharacter::testLowestDiceRolls()
{
	Character *fighter = new Character();
	int test = fighter->generateAbilityModifier(3);
	CPPUNIT_ASSERT(test == -4);
}

//! Test case to ensure that if dice rolls for ability scores were 6, 6, 6, and 1-6, summing up the highest 3 to a total of 18, the ability modifier associated to it is 4.
//! Test Case: A correct ability modifier associated with the highest possible dice rolls must be 4
//! Tested item: Character::generateAbilityModifiers()
void TestCharacter::testHighestDiceRolls()
{
	Character *fighter = new Character();
	int test = fighter->generateAbilityModifier(18);
	CPPUNIT_ASSERT(test == 4);
}

//! Test case to ensure that the ability modifiers are in the correct range, for the default constructor
//! Test Case: A correct ability modifier should have all of its scores in the [-4, 4] range
//! Tested item: Character::validateAbilityModifiers()
void TestCharacter::testAbilityModifier()
{
	Character *fighter = new Character();
	CPPUNIT_ASSERT(fighter->validateAbilityModifiers());
}

//! Test case to ensure that more than one observer can be succesfully attached to a subject
//! Test Case: More than one observer can be attached to one subject
//! Tested item: Subject::Attach(Observer* o)
void TestCharacter::testManyObserversAttaching() {
	int test = 0;
	Character *fighter = new Character();
	CharacterObserver *charobv = new CharacterObserver(fighter);
	CharacterObserver *charobv2 = new CharacterObserver(fighter);

	test = fighter->getNumberObservers();

	CPPUNIT_ASSERT(test == 2);
}

//! Test case to ensure that the observers can be succesfully detached from the subject upon calling detach function
//! Test Case: Detach function must remove the observer from the subject's list of observers
//! Tested item: Subject::Detach(Observer* o)
void TestCharacter::testDetachObserver() {
	int test = 0;
	Character *fighter = new Character();
	CharacterObserver *charobv = new CharacterObserver(fighter);
	fighter->Detach(charobv);

	test = fighter->getNumberObservers();

	CPPUNIT_ASSERT(test == 0);
}


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

//! Test method to test character equip an item
//! Test Case: When character equips an item, the size of 'equipped' array should increase, and the size of 'backpack' should decrease
void TestCharacter::testEquipItem()
{
	cout << "\nTest case: Equip item\n" << endl; 
	Character *fighter = new Character();
	ItemContainer* items = new ItemContainer("BACKPACK");
	Item* armor = new Armor();
	items->addItem(armor);
	fighter->setBackpack(items);
	int backpackBefore = fighter->getBackpack()->getItems().size();
	int equippedBefore = fighter->getEquippedItems()->getItems().size();
	cout << backpackBefore << " " << equippedBefore << endl;
	fighter->equipItem(0); // calling equip method
	int backpackAfter = fighter->getBackpack()->getItems().size();
	int equippedAfter = fighter->getEquippedItems()->getItems().size();
	cout << backpackAfter << " " << equippedAfter << endl;
	CPPUNIT_ASSERT(backpackBefore == equippedAfter && equippedBefore == backpackAfter);
}

//! Test method to test character unequip an item
//! Test Case: When character unequip an item, the size of 'equipped' array should decrease, and the size of 'backpack' should increase
void TestCharacter::testUnequipItem()
{
	cout << "\nTest case: Unequip item\n" << endl;
	Character *fighter = new Character();
	ItemContainer* items = new ItemContainer("EQUIPPED");
	Item* armor = new Armor();
	items->addItem(armor);
	fighter->setEquippedItems(items);
	int backpackBefore = fighter->getBackpack()->getItems().size();
	int equippedBefore = fighter->getEquippedItems()->getItems().size();
	cout << backpackBefore << " " << equippedBefore << endl;
	fighter->unequipItem(0); // calling equip method
	int backpackAfter = fighter->getBackpack()->getItems().size();
	int equippedAfter = fighter->getEquippedItems()->getItems().size();
	cout << backpackAfter << " " << equippedAfter << endl;
	CPPUNIT_ASSERT(backpackBefore == equippedAfter && equippedBefore == backpackAfter);
}