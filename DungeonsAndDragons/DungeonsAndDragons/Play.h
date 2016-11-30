//! @file 
//! @brief Cpp file for Play class
#pragma once
#include "Campaign.h"
#include "ContentBuilder.h"
#include "ConcreteContentBuilder.h"
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include "UserDrivenEditor.h"
#include <iostream>
#include "Combat.h"
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
	ContentBuilder* mbuilder;
	int currentMap;
	bool playerAlive;
	static bool logCampaignInfo;
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
	bool playerIsAlive();
	void startCombat(Map*, MapObject*, MapObject*);
	bool friendInteraction(Map*, MapObject*, MapObject*);
	string getAvailableCharacters(int index);
	void createNewCharacter();
	bool saveCharacter(string);
	void modifyEquipment();
	void placeCharacterOnMap(Map* map);
	bool moveCharacter(Map* map, char direction);
	void adaptMapToPlayer(Map* map);
	void levelUpCharacter();
	void setCurrentMap(int);
	int getCurrentMap();
	MapObject* getCharacter();
	static void setCampaignInfoLog(bool);
	~Play();
};

