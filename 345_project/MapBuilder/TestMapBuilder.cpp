//! @file 
//! @brief File containing the Test Class for the MapBuilder class and the Test Methods
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

#include "Map.h"
#include "MapObject.h"
#include "Director.h"
#include "MapBuilder.h"
#include "ConcreteBuilderA.h"
#include "ConcreteBuilderB.h"
#include "Character.h"

using namespace CppUnit;
using namespace std;

//! Test Class for the MapBuilder class and its subclasses
//! It must be a subclass of CppUnit::TestFixture
//! It then uses CPPUNIT_TEST_SUITE() to create the test suite, and CPPUNIT_TEST() to include the test methods in the test suite. 
//! CPPUNIT_TEST_SUITE_REGISTRATION() is then used to register the test class in the test registry.
class TestMapBuilder : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestMapBuilder);
	CPPUNIT_TEST(testBuildEnemy);
	CPPUNIT_TEST(testBuildContainer);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp(void);
	void tearDown(void);
protected:
	void testBuildEnemy(void);
	void testBuildContainer(void);
private:
	MapBuilder* mb;
	Director d;
};

//! Register for running the test
CPPUNIT_TEST_SUITE_REGISTRATION(TestMapBuilder);

//! Test method to test the buildEnemy(..) method of the  ConcreteBuilderA class
//! Test Case: After manually calling the buildEnemy(..) method, the object at the specified position should be of type 'E' (Enemy)
void TestMapBuilder::testBuildEnemy(void)
{
	Map* map = new Map(5, 5);
	d.setMapBuilder(mb);
	mb->setMap(map);
	mb->buildEnemy(1, 1, "Characters/testEnemy.txt"); // call buildEnemy(...) method, reading from testEnemy.txt file
	Map* testMap = d.getMap();
	MapObject* p = testMap->getTile(1, 1); // Enemy created should be at position (1,1)
	char type = p->getObjectType();
	CPPUNIT_ASSERT(type == 'E');
}

//! Test method to test the buildChest(..) method of the  ConcreteBuilderA class
//! Test Case: After manually calling the buildChest(..) method, the object at the specified position should be of type 'C' (Enemy)
void TestMapBuilder::testBuildContainer(void)
{
	Map* map = new Map(5, 5);
	d.setMapBuilder(mb);
	mb->setMap(map);
	mb->buildContainer(1, 2, 5, "Chests/testChest"); // call buildChest(...) method, reading from testChestlvl5.txt file
	Map* testMap = d.getMap();
	MapObject* p = testMap->getTile(1, 2); // Enemy created should be at position (1,1)
	char type = p->getObjectType();
	CPPUNIT_ASSERT(type == 'C');
}

//! setUp() method that is executed before all the test cases that the test class includes 
void TestMapBuilder::setUp(void)
{
	mb = new ConcreteBuilderA();
}

//! tearDown() method that is executed after all the test cases that the test class includes 
void TestMapBuilder::tearDown(void)
{
	delete mb;
}
