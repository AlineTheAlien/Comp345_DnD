#pragma once
#include "Campaign.h"
#include "MapBuilder.h"
#include "ConcreteBuilderA.h"
#include "ConcreteBuilderB.h"
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include "UserDrivenEditor.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <boost/filesystem.hpp>

class Play
{
private:
	Campaign* campaign;
	Character* character;
	vector<Map*> campaignMaps;
	vector<string> availableCampaigns;
	vector<string> availableCharacters;
	MapBuilder* mbuilder;
public:
	Play();
	bool loadCampaign(string campaignName);
	Map* getCampaignMap(int index);
	int getAvailableCampaignsSize();
	void setAvailableCampaigns();
	void setAvailableCharacters();
	string getAvailableCampaigns(int index);
	bool loadMaps();
	bool loadCharacter(string characterName);
	int getAvailableCharactersSize();
	int getCampaignSize();
	string getAvailableCharacters(int index);
	void createNewCharacter();
	bool saveCharacter(string);
	void placeCharacterOnMap(Map* map);
	bool moveCharacter(Map* map, char direction);
	void adaptMapToPlayer(Map* map);
	void setMapBuilder(MapBuilder*);
	~Play();
};

