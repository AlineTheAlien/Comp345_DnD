#include "stdafx.h"
#include "Play.h"


Play::Play()
{
	setAvailableCampaigns();
	setAvailableCharacters();
	currentMap = 0;
	MapBuilder* m = new ConcreteBuilderA();
	mbuilder = m;
}


//! Implementation of getAvailableCampaigns to get a specific saved campaign
//! @param index : an integer value of the position of the campaign in the vector
//! @return : a string representing the name of the campaign
string Play::getAvailableCampaigns(int index)
{
	return availableCampaigns.at(index);
}


int Play::getAvailableCampaignsSize()
{
	return availableCampaigns.size();
}

int Play::getCampaignSize()
{
	return campaign->getMapListSize();
}

//! Implementation of getCampaignMap to get a specific map from a campaign
//! @param index : an integer value of the position of the map in the campaign vector
//! @return : a map object at the specified position
Map* Play::getCampaignMap(int index)
{
	return campaignMaps[index];
}

void Play::levelUpCharacter()
{
	character->levelUp();
	mbuilder->setPlayerLevel(character->getCurrentLevel());
	saveCharacter(character->getCharacterName());
}

void Play::adaptMapToPlayer(Map* map)
{
	mbuilder->setMap(map); // set the current map for the map builder
	for (int i = 0; i < map->getMapY(); i++)
	{
		for (int j = 0; j < map->getMapX(); j++)
		{
			if (map->getTile(j, i) == 'E') {
				delete map->getObjectTile(j, i);
				map->setTile(j, i, NULL);
				MapObject* enemy = new Character('E', 5, 5, 5, 5, 5 ,5);
				map->setTile(j, i, enemy);
				mbuilder->buildCharacter('E', j, i, enemy);
			}
		}
	}
}

//! Implementation of loadCampaign to load the specified campaign into the campaign object
//! @Param : a string value representing the name of the campaign
bool Play::loadCampaign(string campaignName)
{
	delete campaign;
	campaign = NULL;
	//Create an input archive
	std::ifstream ifs("Campaigns/" + campaignName, std::ios::binary);
	if (!ifs)
		return false;
	boost::archive::binary_iarchive ar(ifs);
	ar.template register_type<MapObject>();
	ar.template register_type<ItemContainer>();
	ar.template register_type<Item>();
	ar.template register_type<Armor>();
	ar.template register_type<Helmet>();
	ar.template register_type<Boots>();
	ar.template register_type<Ring>();
	ar.template register_type<Weapon>();
	ar.template register_type<Shield>();
	ar.template register_type<Belt>();
	//read class state from archive
	ar >> campaign;

	cout << "Current maps in the campaign: " << endl;
	for (int i = 0; i < campaign->getMapListSize(); i++)
		cout << campaign->getMap(i) << " -> ";
	cout << " End" << endl;
	ifs.close();
	//Check validity of the campaign
	return true;
}

//! Implementation of setAvailableCampaigns to set all the available campaigns in the availableCampaigns vector
void Play::setAvailableCampaigns()
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

//! Implementation of loadMaps to load all the maps of the campaign into campaignMaps 
bool Play::loadMaps()
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
		ar.template register_type<MapObject>();
		ar.template register_type<ItemContainer>();
		ar.template register_type<Item>();
		ar.template register_type<Armor>();
		ar.template register_type<Helmet>();
		ar.template register_type<Boots>();
		ar.template register_type<Ring>();
		ar.template register_type<Weapon>();
		ar.template register_type<Shield>();
		ar.template register_type<Belt>();
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

void Play::setAvailableCharacters()
{
	//Get Campaigns
	boost::filesystem::path path("Characters/");
	boost::filesystem::directory_iterator i(path);
	availableCharacters.clear();
	cout << "Available characters : ";
	for (; i != boost::filesystem::directory_iterator(); i++)
	{
		//cout << i->path().filename().string() << endl;
		availableCharacters.push_back(i->path().filename().string());
		cout << i->path().filename().string() << ", ";
	}
	cout << endl;
}

bool Play::loadCharacter(string characterName) {
	delete character;
	character = NULL;
	//Create an input archive
	std::ifstream ifs("Characters/" + characterName, std::ios::binary);
	if (!ifs)
		return false;
	boost::archive::binary_iarchive ar(ifs);
	ar.template register_type<MapObject>();
	ar.template register_type<ItemContainer>();
	ar.template register_type<Item>();
	ar.template register_type<Armor>();
	ar.template register_type<Helmet>();
	ar.template register_type<Boots>();
	ar.template register_type<Ring>();
	ar.template register_type<Weapon>();
	ar.template register_type<Shield>();
	ar.template register_type<Belt>();
	//read class state from archive
	ar >> character;
	character->displayCharacterInfo();
	character->displayEquipment();
	cout << "OBJECT TYPE" << endl;
	cout << character->getObjectType() << endl;
	mbuilder->setPlayerLevel(character->getCurrentLevel());
	ifs.close();
	//Check validity of the campaign
	return true;
}

int Play::getAvailableCharactersSize() {
	return (availableCharacters.size());
}

string Play::getAvailableCharacters(int index) {
	return availableCharacters[index];
}

void Play::createNewCharacter()
{
	character = UserDrivenEditor::createCharacter();
	saveCharacter(character->getCharacterName());
}

bool Play::saveCharacter(string characterName) {
	ofstream ofs("Characters/" + characterName, std::ios::binary);
	boost::archive::binary_oarchive ar(ofs);
	ar.template register_type<MapObject>();
	ar.template register_type<ItemContainer>();
	ar.template register_type<Item>();
	ar.template register_type<Armor>();
	ar.template register_type<Helmet>();
	ar.template register_type<Boots>();
	ar.template register_type<Ring>();
	ar.template register_type<Weapon>();
	ar.template register_type<Shield>();
	ar.template register_type<Belt>();
	ar << character;
	ofs.close();
	cout << "Your character has been succesfully saved!" << endl;
	return true;
}

void Play::placeCharacterOnMap(Map* map)
{
	for (int i = 0; i < map->getMapY(); i++)
	{
		for (int j = 0; j < map->getMapX(); j++)
		{
			if (map->getTile(j, i) == 'P')
				map->setTile(j, i, character);
		}
	}
	adaptMapToPlayer(map);
}

bool Play::moveCharacter(Map* map, char direction)
{
	for (int i = 0; i < map->getMapY(); i++)
	{
		for (int j = 0; j < map->getMapX(); j++)
		{
			if (map->getTile(j, i) == 'P')
			{
				if (direction == 'L' && j > 0)
				{
					map->movePlayer(j - 1, i, character);
					return true;
				}
				else
				if (direction == 'R' && j < map->getMapX() - 1)
				{
					map->movePlayer(j + 1, i, character);
					return true;
				}
				else
				if (direction == 'U' && i > 0)
				{
					map->movePlayer(j, i - 1, character);
					return true;
				}
				else
				if (direction == 'D' && i < map->getMapY() - 1)
				{
					map->movePlayer(j, i + 1, character);
					return true;
				}
			}
		}
	}
	return false;
}

void Play::setCurrentMap(int index)
{
	currentMap = index;
}

int Play::getCurrentMap()
{
	return currentMap;
}

Play::~Play()
{
	delete campaign;
	campaign = NULL;
	delete character;
	character = NULL;
	for (int i = 0; i < campaignMaps.size(); i++)
	{
		delete campaignMaps[i];
		campaignMaps[i] = NULL;
	}
	delete mbuilder;
}
