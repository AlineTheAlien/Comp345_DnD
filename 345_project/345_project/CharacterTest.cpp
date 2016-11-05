#include "stdafx.h"
#include "CharacterTest.h"
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
using namespace CppUnit;
#include "Character.h"
#include <string>
using namespace std;


//! Test case registration
CPPUNIT_TEST_SUITE_REGISTRATION(CharacterTest);

//! Test method to test the validateNewCharacter() method of the Character class 
//! Test Case: a valid newly created character should have all its ability scores in the [3-18] range
//! Tested item: Character::validateNewCharacter()
void CharacterTest::testValidNewCharacter()
{
	Character *conan = new Character(12, 12, 12, 12, 12, 12);
	CPPUNIT_ASSERT(conan->validateNewCharacter());
}

//! test method to test the validateNewCharacter() method of the Character class 
//! Test Case: an invalid newly created character should have any of its ability scores outside the [3-18] range
//! Tested item: Character::validateNewCharacter()
void CharacterTest::testInvalidNewCharacter()
{
	Character *conan = new Character(20, 12, 12, 12, 12, 12);
	CPPUNIT_ASSERT(conan->validateNewCharacter() == false);
}

//! test method to test the hit() method of the Map class 
//! Test Case: a character that has been hit(x) should have its hit points reduced by x 
//! Tested item: Character::hit()
void CharacterTest::testHit()
{
	Character *conan = new Character(12, 12, 12, 12, 12, 12);
	conan->getDamaged(4);
	CPPUNIT_ASSERT(conan->getHitPoints() == 7);
}

//! Test case to ensure that if dice rolls for ability scores were 1, 1, 1, and 1, summing up the highest 3 to a total of 3, that the odd negative ability modifier associated to it is rounded down instead of up.
//! Test Case: A correct ability modifier associated with the lowest possible dice rolls must be -4
//! Tested item: Character::generateAbilityModifiers()
void CharacterTest::testLowestDiceRolls()
{
	Character *fighter = new Character();
	int test = fighter->generateAbilityModifier(3);
	CPPUNIT_ASSERT(test == -4);
}

//! Test case to ensure that if dice rolls for ability scores were 6, 6, 6, and 1-6, summing up the highest 3 to a total of 18, the ability modifier associated to it is 4.
//! Test Case: A correct ability modifier associated with the highest possible dice rolls must be 4
//! Tested item: Character::generateAbilityModifiers()
void CharacterTest::testHighestDiceRolls()
{
	Character *fighter = new Character();
	int test = fighter->generateAbilityModifier(18);
	CPPUNIT_ASSERT(test == 4);
}

//! Test case to ensure that the ability modifiers are in the correct range, for the default constructor
//! Test Case: A correct ability modifier should have all of its scores in the [-4, 4] range
//! Tested item: Character::validateAbilityModifiers()
void CharacterTest::testAbilityModifier()
{
	Character *fighter = new Character();
	CPPUNIT_ASSERT(fighter->validateAbilityModifiers());
}
