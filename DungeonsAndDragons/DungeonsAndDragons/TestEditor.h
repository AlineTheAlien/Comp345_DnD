//! @file 
//! @brief Implementation file for the TestEditor class  
//!
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
#include "MapEditor.h"
#include "CampaignEditor.h"
using namespace CppUnit;
class TestEditor : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestEditor);
	CPPUNIT_TEST(testSaveMap);
	CPPUNIT_TEST(testLoadMap);
	CPPUNIT_TEST(testSaveCampaign);
	CPPUNIT_TEST(testLoadCampaign);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();
protected:
	void testSaveMap();
	void testLoadMap();
	void testSaveCampaign();
	void testLoadCampaign();
private:
	MapEditor* mapEditor;
	CampaignEditor* campaignEditor;

};

