#pragma once
#include "Campaign.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <boost/filesystem.hpp>

class Play
{
private:
	Campaign* campaign;
	vector<Map*> campaignMaps;
	vector<string> availableCampaigns;
public:
	Play();
	bool loadCampaign(string campaignName);
	Map* getCampaignMap(int index);
	int getAvailableCampaignsSize();
	void setAvailableCampaigns();
	string getAvailableCampaigns(int index);
	bool loadMaps();



	~Play();
};

