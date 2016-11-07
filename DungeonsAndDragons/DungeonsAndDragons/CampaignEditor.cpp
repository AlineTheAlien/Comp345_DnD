#include "stdafx.h"
#include "CampaignEditor.h"


//! Implementation of the default constructor of CampaignEditor
CampaignEditor::CampaignEditor()
{
	campaign = new Campaign();
	setAvailableMaps();
	setAvailableCampaigns();
}

//! Implementation of setAvailableMaps to set all the available maps in the availableMaps vector
void CampaignEditor::setAvailableMaps()
{
	//Get Maps
	boost::filesystem::path path2("Maps/");
	boost::filesystem::directory_iterator i2(path2);
	availableMaps.clear();
	cout << "Available maps : ";
	for (; i2 != boost::filesystem::directory_iterator(); i2++)
	{
		availableMaps.push_back(i2->path().filename().string());
		cout << i2->path().filename().string() << ", ";
	}
	cout << endl;
}


//! Implementation of setAvailableCampaigns to set all the available campaigns in the availableCampaigns vector
void CampaignEditor::setAvailableCampaigns()
{
	//Get Campaigns
	boost::filesystem::path path("Campaigns/");
	boost::filesystem::directory_iterator i(path);
	availableCampaigns.clear();
	cout << "Available campaigns : ";
	for (; i != boost::filesystem::directory_iterator(); i++)
	{
		//cout << i->path().filename().string() << endl;
		availableCampaigns.push_back(i->path().filename().string());
		cout << i->path().filename().string() << ", ";
	}
	cout << endl;
}


//! Implementation of newCampaign to create a new campaign
void CampaignEditor::newCampaign()
{
	delete campaign;
	campaign = NULL;
	campaign = new Campaign();
}

//! Implementation of addMap to add a map in a campaign
//! @param mapName : a string value of the name of the map
void CampaignEditor::addMap(string mapName)
{
	campaign->addMap(mapName);
}

//! Implementation of removeMap to remove the last map of the campaign
void CampaignEditor::removeMap()
{
	campaign->removeMap();
}


//! Implementation of getMap to get the name of a map of the campaign object
//! @param index : an integer value of the position of the map
//! @return : string representating name of the map at the specified position
string CampaignEditor::getMap(int index)
{
	return campaign->getMap(index);
}

//! Implementation of getAvailableMap to get a specific saved map 
//! @param index : an integer value of the position of the map in the vector
//! @return : a string representing the name of the map
string CampaignEditor::getAvailableMap(int index)
{
	//get all maps available
	return availableMaps.at(index);
}


//! Implementation of getAvailableMapsSize to get the number of maps available
//! @return : an integer representing the size of the map
int CampaignEditor::getAvailableMapsSize()
{
	return availableMaps.size();
}


//! Implementation of getAvailableCampaigns to get a specific saved campaign
//! @param index : an integer value of the position of the campaign in the vector
//! @return : a string representing the name of the campaign
string CampaignEditor::getAvailableCampaigns(int index)
{
	return availableCampaigns.at(index);
}

int CampaignEditor::getAvailableCampaignsSize()
{
	return availableCampaigns.size();
}

//! Implementation of getCampaignMap to get a specific map from a campaign
//! @param index : an integer value of the position of the map in the campaign vector
//! @return : a map object at the specified position
Map* CampaignEditor::getCampaignMap(int index)
{
	return campaignMaps[index];
}

//! Implementation of getCampaignSize to get the size of the campaign vector
//! @return : the size of the campaign vector
int CampaignEditor::getCampaignSize()
{
	return campaign->getMapListSize();
}


//! Implementation of loadMaps to load all the maps of the campaign into campaignMaps 
bool CampaignEditor::loadMaps()
{
	//Create an input archive
	for (int i = 0; i < campaignMaps.size(); i++)
	{
		delete campaignMaps[i];
		campaignMaps[i] = NULL;
	}

	campaignMaps.resize(campaign->getMapListSize());
	for (int i = 0; i < campaign->getMapListSize(); i++)
	{
		std::ifstream ifs("Maps/" + campaign->getMap(i), std::ios::binary);
		if (!ifs)
			return false;
		boost::archive::binary_iarchive ar(ifs);

		//read class state from archive
		ar >> campaignMaps[i];
		if (!campaignMaps[i]->validatePath())
		{
			cout << "A map in the campaign is invalid, failed to load campaign." << endl;
			ifs.close();
			return false;
		}
		ifs.close();
	}
	if (campaignMaps.empty())
	{
		cout << "Campaign is empty. Nothing to preview" << endl;
		return false;
	}
	return true;

}

//! Implementation of loadCampaign to load the specified campaign into the campaign object
//! @Param : a string value representing the name of the campaign
bool CampaignEditor::loadCampaign(string campaignName)
{
	delete campaign;
	campaign = NULL;
	//Create an input archive
	std::ifstream ifs("Campaigns/" + campaignName, std::ios::binary);
	if (!ifs)
		return false;
	boost::archive::binary_iarchive ar(ifs);
	//read class state from archive
	ar >> campaign;

	cout << "Current maps in the campaign: " << endl;
	for (int i = 0; i < campaign->getMapListSize(); i++)
		cout << campaign->getMap(i) << " -> ";
	cout << " End" << endl;
	ifs.close();
	//Check validity of the campaign
	setAvailableMaps();
	for (int i = 0; i < campaign->getMapListSize(); i++)
	{
		bool foundMap = false;
		for (int j = 0; j < availableMaps.size(); j++)
		{
			if (availableMaps[j] == getMap(i))
				foundMap = true;
		}
		if (!foundMap)
		{
			cout << "Invalid campaign, a map in the campaign was not found..." << endl;
			return false;
		}
	}
	return true;
}


//! Implementation of saveCampaign to save the campaign 
//! @param camapignName : string representing the file name of the campaign
void CampaignEditor::saveCampaign(string campaignName)
{
	if (campaign->getMapListSize() > 0)
	{
		campaign->setName(campaignName);
		//Create an output archive
		ofstream ofs("Campaigns/" + campaign->getName(), std::ios::binary);
		boost::archive::binary_oarchive ar(ofs);
		//Write data
		ar << campaign;
		cout << "Campaign is valid and was saved to file " << endl;
		ofs.close();
		//	cout << "Campaign is invalid!" << endl;
	}
	else
		cout << "Campaign is empty, saving aborted..." << endl;
}


//! Implementation of destructor of CampaignEditor class
CampaignEditor::~CampaignEditor()
{
	for (int i = 0; i < campaignMaps.size(); i++)
	{
		delete campaignMaps[i];
		campaignMaps[i] = NULL;
	}

	delete campaign;
	campaign = NULL;
}
