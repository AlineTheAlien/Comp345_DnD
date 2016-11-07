//! @file 
//! @brief Header file for the CampaignEditor class  
//! The following class implements the campaign editor according to the requirements.
//! It allows a user to modify, and create maps
//! The user can load previously created maps and save new ones
//! The library used for serialization of classes is Boost.Serialization
//! It was used because of its efficiency and portability. With Boost, it is possible
//! to serialize and export a class into a binary data file

#pragma once
#include "Campaign.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <boost/filesystem.hpp>


class CampaignEditor
{
private:
	//!Campaign instance
	Campaign* campaign;
	//!Loaded map according to the path list in the campaign
	vector<Map*> campaignMaps;
	//!Available campaigns to load
	vector<string> availableCampaigns;
	//!Available maps to load
	vector<string> availableMaps;
public:
	CampaignEditor();
	void newCampaign();
	void setAvailableMaps();
	void setAvailableCampaigns();
	void addMap(string mapName);
	void removeMap();
	string getMap(int index);
	string getAvailableMap(int index);
	string getAvailableCampaigns(int index);
	int getAvailableMapsSize();
	int getAvailableCampaignsSize();
	int getCampaignSize();
	bool loadMaps();
	Map* getCampaignMap(int index);
	bool loadCampaign(string campaignName);
	void saveCampaign(string campaignName);
	~CampaignEditor();
};

