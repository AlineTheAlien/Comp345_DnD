#include "stdafx.h"
#include "TestEditor.h"
using namespace CppUnit;
using std::cout;
using std::cin;
using std::endl;

//! cppunit registry creation
CPPUNIT_TEST_SUITE_REGISTRATION(TestEditor);

//! method called before every test case in this test class
void TestEditor::setUp()
{
	campaignEditor = new CampaignEditor();
	mapEditor = new MapEditor();
}

//! method called after every test case in this test class
void TestEditor::tearDown()
{
	delete campaignEditor;
	delete mapEditor;
}

//! test method to test the saveMap(string name) method of the MapEditor class
//! Test Case: the returned value should be true after finding the saved file
//! Tested item: MapEditor::saveMap(string name)
void TestEditor::testSaveMap()
{
	mapEditor->setTile(0, 0, 'P');
	mapEditor->setTile(10, 10, 'D');
	mapEditor->saveMap("Test map");

	bool foundMap = false;
	mapEditor->setAvailableMaps();
	for (int i = 0; i < mapEditor->getAvailableMapsSize(); i++)
	{
		if (mapEditor->getAvailableMap(i) == "Test map")
			foundMap = true;
	}
	
	CPPUNIT_ASSERT(foundMap == true);
	cout << endl;
}

//! test method to test the loadMap(string name) method of the MapEditor class
//! Test Case: the returned value should be true after loading the map
//! Tested item: MapEditor::loadMap(string name)
void TestEditor::testLoadMap()
{
	if (mapEditor->loadMap("Test map"))
	{
		cout << "Loaded map : " << endl;
		for (int i = 0; i < mapEditor->getMapSizeY(); i++)
		{
			for (int j = 0; j < mapEditor->getMapSizeX(); j++)
			{
				cout << mapEditor->getTile(j, i) << " ";
			}
			cout << endl;
		}
	}
	CPPUNIT_ASSERT(mapEditor->getTile(0, 0) == 'P' && mapEditor->getTile(10,10) == 'D');
	cout << endl;
}


//! test method to test the saveCampaign(string name) method of the CampaignEditor class
//! Test Case: the returned value should be true after find the campaign file name
//! Tested item: CampaignEditor::saveCampaign(string name)
void TestEditor::testSaveCampaign()
{
	campaignEditor->addMap("Test map");
	campaignEditor->saveCampaign("Test campaign");
	
	bool foundCampaign = false;
	campaignEditor->setAvailableCampaigns();
	for (int i = 0; i < campaignEditor->getAvailableCampaignsSize(); i++)
	{
		if (campaignEditor->getAvailableCampaigns(i) == "Test campaign")
			foundCampaign = true;
	}

	CPPUNIT_ASSERT(foundCampaign == true);
	cout << endl;
}

//! test method to test the loadCampaign(string name) method of the CampaignEditor class
//! Test Case: the returned value should be true after finding the campaign map
//! Tested item: CampaignEditor::loadCampaign(string name)
void TestEditor::testLoadCampaign()
{
	bool foundCampaignMap = false;
	if (campaignEditor->loadCampaign("Test campaign"))
	{
		if (campaignEditor->getMap(0) == "Test map")
			foundCampaignMap = true;
	}
	CPPUNIT_ASSERT(foundCampaignMap == true);
	cout << endl;
}