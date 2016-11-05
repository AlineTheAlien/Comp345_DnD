#include "stdafx.h"
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


//! Test Class for the Character class
class CharacterTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(CharacterTest);
	CPPUNIT_TEST(testValidNewCharacter);
	CPPUNIT_TEST(testInvalidNewCharacter);
	CPPUNIT_TEST(testHit);
	CPPUNIT_TEST(testLowestDiceRolls);
	CPPUNIT_TEST(testHighestDiceRolls);
	CPPUNIT_TEST(testAbilityModifier);
	CPPUNIT_TEST_SUITE_END();
protected:
	void testValidNewCharacter();
	void testInvalidNewCharacter();
	void testHit();
	void testLowestDiceRolls();
	void testHighestDiceRolls();
	void testAbilityModifier();
};