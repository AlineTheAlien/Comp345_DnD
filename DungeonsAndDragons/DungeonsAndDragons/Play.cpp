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
				// get the enemy object
				MapObject* oldEnemy = map->getObjectTile(j, i);
				// create a new backpack to transfer enemy's backpack
				ItemContainer* backpack = new ItemContainer("BACKPACK");
				// transferring the backpack content before deleting...
				int x = static_cast<Character*>(oldEnemy)->getBackpack()->getItems().size() - 1;
				while (!static_cast<Character*>(oldEnemy)->getBackpack()->getItems().empty())
				{
					static_cast<Character*>(oldEnemy)->getBackpack()->transfer(backpack, x);
					x--;
				}
				// delete the enemy
				delete map->getObjectTile(j, i);
				map->setTile(j, i, NULL);
				Director director;
				Character* enemy;
				CharacterBuilder* monsterBuilder = new MonsterBuilder;
				director.setCharacterBuilder(monsterBuilder);
				director.constructCharacter();
				enemy = director.getCharacter();
				mbuilder->buildCharacter('E', j, i, enemy); // adapt to level
				// set the enemy's backpack
				static_cast<Character*>(enemy)->setBackpack(backpack);
			}
			if (map->getTile(j, i) == 'C') {
				MapObject* chest = map->getObjectTile(j, i);
				vector<Item*> items = static_cast<ItemContainer*>(chest)->getItems(); // store a copy of items
				mbuilder->buildContainer(j, i, items); // adapt to level
			}
			if (map->getTile(j, i) == 'F') {
				// get the character backpack
				MapObject* oldFriend = map->getObjectTile(j, i);
				// create a new backpack to transfer enemy's backpack
				ItemContainer* backpack = new ItemContainer("BACKPACK");
				// transferring...
				int x = static_cast<Character*>(oldFriend)->getBackpack()->getItems().size() - 1;
				while (!static_cast<Character*>(oldFriend)->getBackpack()->getItems().empty())
				{
					static_cast<Character*>(oldFriend)->getBackpack()->transfer(backpack, x);
					x--;
				}
				delete map->getObjectTile(j, i);
				map->setTile(j, i, NULL);
				Director director;
				Character* friendly;
				CharacterBuilder* friendlybuilder = new FriendlyBuilder;
				director.setCharacterBuilder(friendlybuilder);
				director.constructCharacter();
				friendly = director.getCharacter();
				mbuilder->buildCharacter('F', j, i, friendly); // adapt to level
				static_cast<Character*>(friendly)->setBackpack(backpack);
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
	ar.template register_type<Character>();
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
		ar.template register_type<Character>();
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
	availableCharacters.clear();
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
	playerAlive = true;
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
	playerAlive = true;
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
			{
				map->setTile(j, i, character);
			}
		}
	}
	adaptMapToPlayer(map);
}

bool Play::moveCharacter(Map* map, char direction)
{
	int j = static_cast<Character*>(character)->getMapX();
	int i = static_cast<Character*>(character)->getMapY();

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
			map->movePlayer(j - 1, i, character);
		}
		else
			if (map->getTile(j - 1, i) == 'E')
			{
				MapObject* enemy = map->getObjectTile(j - 1, i);
				if ((static_cast<Character*>(enemy)->getHitPoints()) <= 0) {
					character->displayBackpack();
					int x = static_cast<Character*>(enemy)->getBackpack()->getItems().size() - 1;
					while (!static_cast<Character*>(enemy)->getBackpack()->getItems().empty())
					{
						static_cast<Character*>(enemy)->getBackpack()->transfer(character->getBackpack(), x);
						x--;
					}
					character->displayBackpack();
					map->movePlayer(j - 1, i, character);
				}
				else
					startCombat(map, character, map->getObjectTile(j - 1, i));
			}
			else
				if (map->getTile(j - 1, i) == 'F')
				{
					MapObject* friendly = map->getObjectTile(j - 1, i);
					if ((static_cast<Character*>(friendly)->getHitPoints()) <= 0) {
						character->displayBackpack();
						int x = static_cast<Character*>(map->getObjectTile(j - 1, i))->getBackpack()->getItems().size() - 1;
						while (!static_cast<Character*>(map->getObjectTile(j - 1, i))->getBackpack()->getItems().empty())
						{
							static_cast<Character*>(map->getObjectTile(j - 1, i))->getBackpack()->transfer(character->getBackpack(), x);
							x--;
						}
						character->displayBackpack();
						map->movePlayer(j - 1, i, character);
					}
					else {
						if (friendInteraction(map, character, map->getObjectTile(j - 1, i))) {
							// if friend is dead
						}
						else
							return false;
					}
				}
				else
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
				map->movePlayer(j + 1, i, character);
			}
			else
				if (map->getTile(j + 1, i) == 'E')
				{
					MapObject* enemy = map->getObjectTile(j + 1, i);
					if ((static_cast<Character*>(enemy)->getHitPoints()) <= 0) {
						character->displayBackpack();
						int x = static_cast<Character*>(enemy)->getBackpack()->getItems().size() - 1;
						while (!static_cast<Character*>(enemy)->getBackpack()->getItems().empty())
						{
							static_cast<Character*>(enemy)->getBackpack()->transfer(character->getBackpack(), x);
							x--;
						}
						character->displayBackpack();
						map->movePlayer(j + 1, i, character);
					}
					else
						startCombat(map, character, map->getObjectTile(j + 1, i));
				}
				else
					if (map->getTile(j + 1, i) == 'F')
					{
						MapObject* friendly = map->getObjectTile(j + 1, i);
						if ((static_cast<Character*>(friendly)->getHitPoints()) <= 0) {
							character->displayBackpack();
							int x = static_cast<Character*>(map->getObjectTile(j + 1, i))->getBackpack()->getItems().size() - 1;
							while (!static_cast<Character*>(map->getObjectTile(j + 1, i))->getBackpack()->getItems().empty())
							{
								static_cast<Character*>(map->getObjectTile(j + 1, i))->getBackpack()->transfer(character->getBackpack(), x);
								x--;
							}
							character->displayBackpack();
							map->movePlayer(j + 1, i, character);
						}
						else {
							if (friendInteraction(map, character, map->getObjectTile(j + 1, i))) {
							}
							else
								return false;
						}
					}
					else
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
					map->movePlayer(j, i - 1, character);
				}
				else
					if (map->getTile(j, i - 1) == 'E')
					{
						MapObject* enemy = map->getObjectTile(j, i - 1);
						if ((static_cast<Character*>(enemy)->getHitPoints()) <= 0) {
							character->displayBackpack();
							int x = static_cast<Character*>(enemy)->getBackpack()->getItems().size() - 1;
							while (!static_cast<Character*>(enemy)->getBackpack()->getItems().empty())
							{
								static_cast<Character*>(enemy)->getBackpack()->transfer(character->getBackpack(), x);
								x--;
							}
							character->displayBackpack();
							map->movePlayer(j, i - 1, character);
						}
						else
							startCombat(map, character, map->getObjectTile(j, i - 1));
					}
					else
						if (map->getTile(j, i - 1) == 'F')
						{
							MapObject* friendly = map->getObjectTile(j, i - 1);
							if ((static_cast<Character*>(friendly)->getHitPoints()) <= 0) {
								character->displayBackpack();
								int x = static_cast<Character*>(map->getObjectTile(j, i - 1))->getBackpack()->getItems().size() - 1;
								while (!static_cast<Character*>(map->getObjectTile(j, i - 1))->getBackpack()->getItems().empty())
								{
									static_cast<Character*>(map->getObjectTile(j, i - 1))->getBackpack()->transfer(character->getBackpack(), x);
									x--;
								}
								character->displayBackpack();
								map->movePlayer(j, i - 1, character);
							}
							else {
								if (friendInteraction(map, character, map->getObjectTile(j, i - 1))) {
								}
								else
									return false;
							}
						}
						else
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
						map->movePlayer(j, i + 1, character);
					}
					else
						if (map->getTile(j, i + 1) == 'E')
						{
							MapObject* enemy = map->getObjectTile(j, i + 1);
							if ((static_cast<Character*>(enemy)->getHitPoints()) <= 0) {
								character->displayBackpack();
								int x = static_cast<Character*>(enemy)->getBackpack()->getItems().size() - 1;
								while (!static_cast<Character*>(enemy)->getBackpack()->getItems().empty())
								{
									static_cast<Character*>(enemy)->getBackpack()->transfer(character->getBackpack(), x);
									x--;
								}
								character->displayBackpack();
								map->movePlayer(j, i + 1, character);
							}
							else
								startCombat(map, character, map->getObjectTile(j, i + 1));

						}
						else
							if (map->getTile(j, i + 1) == 'F')
							{
								MapObject* friendly = map->getObjectTile(j, i + 1);
								if ((static_cast<Character*>(friendly)->getHitPoints()) <= 0) {
									character->displayBackpack();
									int x = static_cast<Character*>(map->getObjectTile(j, i + 1))->getBackpack()->getItems().size() - 1;
									while (!static_cast<Character*>(map->getObjectTile(j, i + 1))->getBackpack()->getItems().empty())
									{
										static_cast<Character*>(map->getObjectTile(j, i + 1))->getBackpack()->transfer(character->getBackpack(), x);
										x--;
									}
									character->displayBackpack();
									map->movePlayer(j, i + 1, character);
								}
								else {
									if (friendInteraction(map, character, map->getObjectTile(j, i + 1))) {
									}
									else
										return false;
								}
							}
							else
								map->movePlayer(j, i + 1, character);
					return true;
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

void Play::startCombat(Map* map, MapObject* player, MapObject* enemy)
{
	Combat::startCombat(map, player, enemy);

	if (character->getHitPoints() <= 0)
	{
		cout << "Player is defeated." << endl;
		playerAlive = false;
		return;
	}
	else
	{
		cout << "Enemy is defeated." << endl;
	}
}

bool Play::friendInteraction(Map* map, MapObject* player, MapObject* npc)
{
	static_cast<Character*>(npc)->executeStrategy(map, npc, player);
	if (character->getHitPoints() <= 0) {
		cout << "Played is defeated." << endl;
		playerAlive = false;
		return false;
	}
	else if (static_cast<Character*>(npc)->getHitPoints() <= 0)
	{
		cout << "NPC is defeated." << endl;
		return true;
	}
	return false;
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

bool Play::playerIsAlive()
{
	return playerAlive;
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
