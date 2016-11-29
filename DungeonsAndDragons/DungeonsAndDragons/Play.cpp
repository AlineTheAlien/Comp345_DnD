//! @file 
//! @brief Implementation file for the Play class  
//!
#include "stdafx.h"
#include "Play.h"
#include "Director.h"
#include "MonsterBuilder.h"
#include "FriendlyBuilder.h"
#include "HumanPlayerStrategy.h"

Play::Play()
{
	setAvailableCampaigns();
	setAvailableCharacters();
	currentMap = 0;
	ContentBuilder* m = new ConcreteContentBuilder();
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

//! Method to adapt the map to a player
//! @param map : Pointer to a map object
void Play::adaptMapToPlayer(Map* map) {
	mbuilder->setPlayerLevel(character->getCurrentLevel());
	mbuilder->setMap(map); // set the current map for the map content builder
	for (int i = 0; i < map->getMapY(); i++)
	{
		for (int j = 0; j < map->getMapX(); j++)
		{
			if (map->getTile(j, i) == 'E') {
				delete map->getObjectTile(j, i);
				map->setTile(j, i, NULL);
				Director director;
				Character* enemy;
				CharacterBuilder* monsterBuilder = new MonsterBuilder;
				director.setCharacterBuilder(monsterBuilder);
				director.constructCharacter();
				enemy = director.getCharacter();
				mbuilder->buildCharacter('E', j, i, enemy); // adapt to level
			}
			if (map->getTile(j, i) == 'C') {
				MapObject* chest = map->getObjectTile(j, i);
				vector<Item*> items = static_cast<ItemContainer*>(chest)->getItems(); // store a copy of items
				mbuilder->buildContainer(j, i, items); // adapt to level
			}
			if (map->getTile(j, i) == 'F') {
				delete map->getObjectTile(j, i);
				map->setTile(j, i, NULL);
				Director director;
				Character* friendlyenemy;
				CharacterBuilder* friendlybuilder = new FriendlyBuilder;
				director.setCharacterBuilder(friendlybuilder);
				director.constructCharacter();
				friendlyenemy = director.getCharacter();
				mbuilder->buildCharacter('F', j, i, friendlyenemy); // adapt to level
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

	cout << character->getCurrentLevel() << endl;

	//from here on, we are setting all the attributes that we have not loaded
	int modifiers[6];

	character->assignAbilityModifiers(modifiers);

	sort(modifiers, modifiers + 6, greater<int>());

	character->setDexterityModifier(modifiers[0]);
	character->setConstitutionModifier(modifiers[1]);
	character->setStrengthModifier(modifiers[2]);
	character->setIntelligenceModifier(modifiers[3]);
	character->setCharismaModifier(modifiers[4]);
	character->setWisdomModifier(modifiers[5]);

	//set hit points as 10 summed with the character's calculated  constitution modifier
	character->setCurrentHitPoints(10 + character->getConstitutionModifier());

	//Initially, as character is not hit, the maximum HP is the same as the current HP
	character->setMaxHitPoints(character->getHitPoints());

	//Depending on type of armor worn, armor class differs
	//Default armor class will be 11 + dexterity modifier, as I don't have access to the Items class yet
	character->setArmorClass(11 + character->getDexterityModifier());

	//Attack bonus, is based on strength modifier, dexterity modifier, and level
	//In the default constructor, level is 0 therefore attack bonus is just based on strength + dexterity modifiers
	character->setAttackBonus(character->getStrengthModifier() + character->getDexterityModifier());

	//Damage bonus, based on strength modifier
	character->setDamageBonus(character->getStrengthModifier());

	character->displayCharacterInfo();
	character->displayEquipment();
	cout << "OBJECT TYPE" << endl;
	char type = character->getObjectType();
	cout << type << endl;

	// Set strategy to Human Player Strategy
	if (type == 'P') {
		character->setStrategy(new HumanPlayerStrategy());
	}

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
					if (map->getTile(j - 1, i) == 'C')
					{
						character->displayBackpack();
						int x = static_cast<ItemContainer*>(map->getObjectTile(j - 1, i))->getItems().size() - 1;
						while (!static_cast<ItemContainer*>(map->getObjectTile(j - 1, i))->getItems().empty())
						{
							static_cast<ItemContainer*>(map->getObjectTile(j - 1, i))->transfer(character->getBackpack(), x);
							x--;
						}
						character->displayBackpack();
					}
					map->movePlayer(j - 1, i, character);
					return true;
				}
				else
					if (direction == 'R' && j < map->getMapX() - 1)
					{
						if (map->getTile(j + 1, i) == 'C')
						{
							character->displayBackpack();
							int x = static_cast<ItemContainer*>(map->getObjectTile(j + 1, i))->getItems().size() - 1;
							while (!static_cast<ItemContainer*>(map->getObjectTile(j + 1, i))->getItems().empty())
							{
								static_cast<ItemContainer*>(map->getObjectTile(j + 1, i))->transfer(character->getBackpack(), x);
								x--;
							}
							character->displayBackpack();
						}
						map->movePlayer(j + 1, i, character);
						return true;
					}
					else
						if (direction == 'U' && i > 0)
						{
							if (map->getTile(j, i - 1) == 'C')
							{
								character->displayBackpack();
								int x = static_cast<ItemContainer*>(map->getObjectTile(j, i - 1))->getItems().size() - 1;
								while (!static_cast<ItemContainer*>(map->getObjectTile(j, i - 1))->getItems().empty())
								{
									static_cast<ItemContainer*>(map->getObjectTile(j, i - 1))->transfer(character->getBackpack(), x);
									x--;
								}
								character->displayBackpack();
							}
							map->movePlayer(j, i - 1, character);
							return true;
						}
						else
							if (direction == 'D' && i < map->getMapY() - 1)
							{
								if (map->getTile(j, i + 1) == 'C')
								{
									character->displayBackpack();
									int x = static_cast<ItemContainer*>(map->getObjectTile(j, i + 1))->getItems().size() - 1;
									while (!static_cast<ItemContainer*>(map->getObjectTile(j, i + 1))->getItems().empty())
									{
										static_cast<ItemContainer*>(map->getObjectTile(j, i + 1))->transfer(character->getBackpack(), x);
										x--;
									}
									character->displayBackpack();
								}
								map->movePlayer(j, i + 1, character);
								return true;
							}
			}
		}
	}
	return false;
}

void Play::startCombat(Map* map, MapObject* player, MapObject* other)
{
	Combat::startCombat(map, player, other);

	//if (static_cast<Character*>(player)->getHitPoints() <= 0) 
	if (character->getHitPoints <= 0)
	{
		//cout << "Player is defeated." << endl;
		//state.setLaunchState(LaunchState::MENU);
		playerAlive = false;
		return;
	}
	else
	{
		cout << "Enemy is defeated." << endl;
		//int i = enemy->getMapY();
		//int j = enemy->getMapX();
		//int iPlayer = player->getMapY();
		//int jPlayer = player->getMapX();
		//// Take all the fallen items
		//delete enemy;
		//map->movePlayer(j, i, player);
		//play->getCampaignMap(currentMap)->showMap();
		//currentPositionX = j;
		//currentPositionY = i;
		//maps[currentMap].at(jPlayer + iPlayer * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getGroundTexture());
		//maps[currentMap].at(currentPositionX + currentPositionY * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getPlayerTexture());
		//Combat::activateNPC(map, player);
	}
}

bool Play::playerIsAlive()
{
	return playerAlive;
}

void Play::setCurrentMap(int index)
{
	currentMap = index;
}

int Play::getCurrentMap()
{
	return currentMap;
}

void Play::modifyEquipment()
{
	int choice;
	int itemChoice;
	int size = character->getBackpack()->getItems().size();
	bool isValid = false;
	do {
		cout << "Press 1 to equip items, or press 2 to unequip your current items. Enter -1 to exit" << endl;
		cin >> choice;
		if (choice == 1 || choice == 2)
			isValid = true;
		if (choice == -1)
			return;
	} while (isValid == false);

	if (choice == 1)
	{
		do {
			character->displayBackpack();
			cout << "Which index item do you want to equip? Enter -1 to exit" << endl;
			cin >> itemChoice;
			if (itemChoice == -1)
				return;
		} while (itemChoice > size || itemChoice < 0);
		character->equipItem(itemChoice);
		character->displayBackpack();
		character->displayEquipment();
	}
	else
		if (choice == 2)
		{
			do {
				character->getEquippedItems()->displayItems();
				cout << "Which index item do you want to unequip? Enter -1 to exit" << endl;
				cin >> itemChoice;
				if (itemChoice == -1)
					return;
			} while (itemChoice > character->getEquippedItems()->getItems().size() || itemChoice < 0);
			character->unequipItem(itemChoice);
			character->displayBackpack();
			character->displayEquipment();
		}
}

MapObject* Play::getCharacter() {
	return character;
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
