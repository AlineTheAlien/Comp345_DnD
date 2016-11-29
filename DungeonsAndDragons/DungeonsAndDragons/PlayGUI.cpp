//! @file 
//! @brief Implementation file for PlayGUI class

#include "stdafx.h"
#include "PlayGUI.h"
#include "Combat.h"

PlayGUI::PlayGUI()
{
	play = new Play();
}

PlayGUI::PlayGUI(sf::RenderWindow &newWindow)
{
	play = new Play();
	window = &newWindow;
}

void PlayGUI::Start()
{
	state.setPlayState(PlayState::CHARACTER_SELECTION);
	Update();
}

void PlayGUI::Update()
{
	while (state.isActive())
	{
		string currentState;

		if (state.getPlayState() == PlayState::CHARACTER_SELECTION)
			currentState = "CHARACTER_SELECTION";

		if (state.getPlayState() == PlayState::CAMPAIGN_SELECTION)
			currentState = "CAMPAIGN_SELECTION";

		if (state.getPlayState() == PlayState::MAP_VIEW)
			currentState = "MAP_VIEW";

		if (state.getLaunchState() == LaunchState::MENU)
			return;

		cout << "Current play state has changed state to : " << currentState << endl;

		Display();
	}
}

void PlayGUI::Display()
{
	if (state.getPlayState() == PlayState::CHARACTER_SELECTION)
		openLoadCharacterWindow();
	else
		if (state.getPlayState() == PlayState::CAMPAIGN_SELECTION)
			openLoadCampaignWindow();
		else
			if (state.getPlayState() == PlayState::MAP_VIEW)
				openMapView();
}

void PlayGUI::openLoadCharacterWindow()
{
	vector<sf::FloatRect> buttons;
	vector<sf::Text> texts;
	vector<bool> clicked;

	sf::FloatRect nextButton;
	sf::Text nextText;
	bool nextClicked = false;

	sf::FloatRect newCharacterButton;
	sf::Text newCharacterText;
	bool newCharacterClicked = false;

	sf::FloatRect backButton;
	sf::Text backText;
	bool backClicked = false;

	sf::Font textFont;
	sf::Color normalColor = sf::Color::White;
	sf::Color hoverColor = sf::Color::Yellow;
	sf::Color clickedColor = sf::Color::Yellow;


	if (!textFont.loadFromFile("Fonts/OldSchool.ttf"))
	{
		// error...
	}

	int currentXPosition = 300;
	int currentYPosition = 100;
	for (int i = 0; i < play->getAvailableCharactersSize(); i++)
	{
		texts.push_back(sf::Text());
		texts.back().setString(play->getAvailableCharacters(i));
		texts.back().setFont(textFont);
		texts.back().setStyle(sf::Text::Italic);
		texts.back().setCharacterSize(15);
		texts.back().setPosition(currentXPosition, currentYPosition);
		currentYPosition += 50;
	}

	for (int i = 0; i < texts.size(); i++)
	{
		buttons.push_back(sf::FloatRect());
		buttons.back() = texts.at(i).getGlobalBounds();
	}

	for (int i = 0; i < texts.size(); i++)
	{
		clicked.push_back(bool());
		clicked.back() = false;
	}

	nextText.setPosition(sf::Vector2f(GameState::WINDOW_SCALE - 150, GameState::WINDOW_SCALE - 100));
	nextText.setString("Next");
	nextText.setFont(textFont);
	nextText.setStyle(sf::Text::Italic);
	nextText.setCharacterSize(15);
	nextButton = nextText.getGlobalBounds();

	newCharacterText.setPosition(sf::Vector2f(300, 50));
	newCharacterText.setString("Create a new character");
	newCharacterText.setFont(textFont);
	newCharacterText.setStyle(sf::Text::Italic);
	newCharacterText.setCharacterSize(15);
	newCharacterButton = newCharacterText.getGlobalBounds();

	backText.setPosition(sf::Vector2f(100, GameState::WINDOW_SCALE - 100));
	backText.setString("Back");
	backText.setFont(textFont);
	backText.setStyle(sf::Text::Italic);
	backText.setCharacterSize(15);
	backButton = backText.getGlobalBounds();


	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				state.setActive(false);
				window->close();
				return;
			}


			// transform the mouse position from window coordinates to world coordinates
			sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{

				for (int i = 0; i < buttons.size(); i++)
				{
					if (buttons.at(i).contains(mousePosition))
					{
						texts.at(i).setFillColor(clickedColor);
						clicked.at(i) = true;

						for (int j = 0; j < buttons.size(); j++)
							if (buttons.at(j) != buttons.at(i))
							{
								texts.at(j).setFillColor(normalColor);
								clicked.at(j) = false;
								newCharacterClicked = false;
							}
					}
				}

				if (newCharacterButton.contains(mousePosition))
				{
					newCharacterClicked = true;
					for (int j = 0; j < buttons.size(); j++) {
						clicked.at(j) = false;
					}
				}

				if (nextButton.contains(mousePosition))
				{
					for (int i = 0; i < clicked.size(); i++)
						if (clicked.at(i))
						{
							if (play->loadCharacter(play->getAvailableCharacters(i)))
							{
								play->setAvailableCampaigns();
								state.setPlayState(PlayState::CAMPAIGN_SELECTION);
								return;
							}
						}

					if (newCharacterClicked)
					{
						play->createNewCharacter();
						play->setAvailableCampaigns();
						state.setPlayState(PlayState::CAMPAIGN_SELECTION);
						return;
					}
					//Change state
				}

				if (backButton.contains(mousePosition))
				{
					state.setLaunchState(LaunchState::MENU);
					return;
				}
			}

			for (int i = 0; i < buttons.size(); i++)
			{
				if (buttons.at(i).contains(mousePosition) && !clicked.at(i))
					texts.at(i).setFillColor(hoverColor);

				else
				{
					if (!clicked.at(i))
						texts.at(i).setFillColor(normalColor);

					if (!nextButton.contains(mousePosition))
						nextText.setFillColor(normalColor);

					if (!backButton.contains(mousePosition))
						backText.setFillColor(normalColor);

					if (!newCharacterClicked)
						newCharacterText.setFillColor(normalColor);
				}
			}

			if (nextButton.contains(mousePosition))
				nextText.setFillColor(hoverColor);

			if (newCharacterButton.contains(mousePosition))
				newCharacterText.setFillColor(hoverColor);

			if (backButton.contains(mousePosition))
				backText.setFillColor(hoverColor);
		}

		window->clear();
		for (int i = 0; i < texts.size(); i++)
			window->draw(texts.at(i));
		window->draw(backText);
		window->draw(nextText);
		window->draw(newCharacterText);
		window->display();
	}
}

void PlayGUI::openLoadCampaignWindow()
{
	vector<sf::FloatRect> buttons;
	vector<sf::Text> texts;
	vector<bool> clicked;

	sf::FloatRect nextButton;
	sf::Text nextText;
	bool nextClicked = false;

	sf::FloatRect backButton;
	sf::Text backText;
	bool backClicked = false;

	sf::Font textFont;
	sf::Color normalColor = sf::Color::White;
	sf::Color hoverColor = sf::Color::Yellow;
	sf::Color clickedColor = sf::Color::Yellow;


	if (!textFont.loadFromFile("Fonts/OldSchool.ttf"))
	{
		// error...
	}

	int currentXPosition = 300;
	int currentYPosition = 100;
	for (int i = 0; i < play->getAvailableCampaignsSize(); i++)
	{
		texts.push_back(sf::Text());
		texts.back().setString(play->getAvailableCampaigns(i));
		texts.back().setFont(textFont);
		texts.back().setStyle(sf::Text::Italic);
		texts.back().setCharacterSize(15);
		texts.back().setPosition(currentXPosition, currentYPosition);
		currentYPosition += 50;
	}

	for (int i = 0; i < texts.size(); i++)
	{
		buttons.push_back(sf::FloatRect());
		buttons.back() = texts.at(i).getGlobalBounds();
	}

	for (int i = 0; i < texts.size(); i++)
	{
		clicked.push_back(bool());
		clicked.back() = false;
	}

	nextText.setPosition(sf::Vector2f(GameState::WINDOW_SCALE - 150, GameState::WINDOW_SCALE - 100));
	nextText.setString("Next");
	nextText.setFont(textFont);
	nextText.setStyle(sf::Text::Italic);
	nextText.setCharacterSize(15);
	nextButton = nextText.getGlobalBounds();

	backText.setPosition(sf::Vector2f(100, GameState::WINDOW_SCALE - 100));
	backText.setString("Back");
	backText.setFont(textFont);
	backText.setStyle(sf::Text::Italic);
	backText.setCharacterSize(15);
	backButton = backText.getGlobalBounds();

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				state.setActive(false);
				window->close();
				return;
			}


			// transform the mouse position from window coordinates to world coordinates
			sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{

				for (int i = 0; i < buttons.size(); i++)
				{
					if (buttons.at(i).contains(mousePosition))
					{
						texts.at(i).setFillColor(clickedColor);
						clicked.at(i) = true;

						for (int j = 0; j < buttons.size(); j++)
							if (buttons.at(j) != buttons.at(i))
							{
								texts.at(j).setFillColor(normalColor);
								clicked.at(j) = false;
							}
					}
				}

				if (nextButton.contains(mousePosition))
				{
					for (int i = 0; i < clicked.size(); i++)
						if (clicked.at(i))
						{
							if (play->loadCampaign(play->getAvailableCampaigns(i)))
							{
								play->loadMaps();
								play->placeCharacterOnMap(play->getCampaignMap(play->getCurrentMap()));
								state.setPlayState(PlayState::MAP_VIEW);
								return;
							}

						}
					//Change state
				}

				if (backButton.contains(mousePosition))
				{
					play->setAvailableCharacters();
					state.setPlayState(PlayState::CHARACTER_SELECTION);
					return;
				}
			}

			for (int i = 0; i < buttons.size(); i++)
			{
				if (buttons.at(i).contains(mousePosition) && !clicked.at(i))
					texts.at(i).setFillColor(hoverColor);

				else
				{
					if (!clicked.at(i))
						texts.at(i).setFillColor(normalColor);

					if (!nextClicked)
						nextText.setFillColor(normalColor);

					if (!backClicked)
						backText.setFillColor(normalColor);
				}
			}

			if (nextButton.contains(mousePosition) && !nextClicked)
				nextText.setFillColor(hoverColor);


			if (backButton.contains(mousePosition) && !backClicked)
				backText.setFillColor(hoverColor);
		}

		window->clear();
		for (int i = 0; i < texts.size(); i++)
			window->draw(texts.at(i));
		window->draw(backText);
		window->draw(nextText);
		window->display();
	}
}

void PlayGUI::openMapView()
{
	//vector<vector<sf::Sprite>> maps;
	//int currentMap = play->getCurrentMap();
	currentMap = play->getCurrentMap();
	subject = play->getCampaignMap(currentMap);// For observer pattern
	subject->Attach(this);

	sf::Text modifyText;
	sf::Text menuText;
	sf::Text diceText;
	sf::Text mapText;
	sf::Text combatText;
	sf::Text eventText;

	sf::FloatRect modifyButton;
	sf::FloatRect menuButton;
	sf::FloatRect diceButton;
	sf::FloatRect mapButton;
	sf::FloatRect combatButton;
	sf::FloatRect eventButton;


	sf::Font textFont;
	sf::Color normalColor = sf::Color::White;
	sf::Color hoverColor = sf::Color::Yellow;
	sf::Color clickedColor = sf::Color::Yellow;

	bool modifyClicked = false;
	bool menuClicked = false;
	bool diceClicked = false;
	bool mapClicked = false;
	bool combatClicked = false;
	bool eventClicked = false;

	if (!textFont.loadFromFile("Fonts/OldSchool.ttf"))
	{
		// error...
	}

	modifyText.setString("Modify Equipment");
	modifyText.setFont(textFont);
	modifyText.setStyle(sf::Text::Italic);
	modifyText.setCharacterSize(15);

	menuText.setString("Menu");
	menuText.setFont(textFont);
	menuText.setStyle(sf::Text::Italic);
	menuText.setCharacterSize(15);

	diceText.setString("Dice Info");
	diceText.setFont(textFont);
	diceText.setStyle(sf::Text::Italic);
	diceText.setCharacterSize(15);

	mapText.setString("Map info");
	mapText.setFont(textFont);
	mapText.setStyle(sf::Text::Italic);
	mapText.setCharacterSize(15);

	combatText.setString("Combat info");
	combatText.setFont(textFont);
	combatText.setStyle(sf::Text::Italic);
	combatText.setCharacterSize(15);

	eventText.setString("Event info");
	eventText.setFont(textFont);
	eventText.setStyle(sf::Text::Italic);
	eventText.setCharacterSize(15);


	modifyText.setPosition(sf::Vector2f(300, GameState::WINDOW_SCALE - 100));
	menuText.setPosition(sf::Vector2f(660, 300));
	mapText.setPosition(sf::Vector2f(630, 50));
	combatText.setPosition(sf::Vector2f(630, 100));
	eventText.setPosition(sf::Vector2f(630, 150));
	diceText.setPosition(sf::Vector2f(630, 200));

	modifyButton = modifyText.getGlobalBounds();
	menuButton = menuText.getGlobalBounds();
	mapButton = mapText.getGlobalBounds();
	combatButton = combatText.getGlobalBounds();
	eventButton = eventText.getGlobalBounds();
	diceButton = diceText.getGlobalBounds();

	for (int i = 0; i < play->getCampaignSize(); i++)
	{
		vector<sf::Sprite> mapTiles;
		for (int j = 0; j < play->getCampaignMap(i)->getMapY(); j++)
		{
			for (int k = 0; k < play->getCampaignMap(i)->getMapX(); k++)
			{
				mapTiles.push_back(sf::Sprite());
				char currentTile = play->getCampaignMap(i)->getTile(k, j);
				if (currentTile == 'X')
					mapTiles.back().setTexture(textures.getGroundTexture());
				if (currentTile == 'P')
					mapTiles.back().setTexture(textures.getPlayerTexture());
				if (currentTile == 'D')
					mapTiles.back().setTexture(textures.getDoorTexture());
				if (currentTile == 'C')
					mapTiles.back().setTexture(textures.getTreasureTexture());
				if (currentTile == 'W')
					mapTiles.back().setTexture(textures.getWallTexture());
				if (currentTile == 'E')
					mapTiles.back().setTexture(textures.getEnemyTexture());
				if (currentTile == 'F')
					mapTiles.back().setTexture(textures.getFriendlyTexture());
				mapTiles.back().setPosition(k * mapTiles.back().getLocalBounds().width, j * mapTiles.back().getLocalBounds().height);
				//mapTiles.back().setOrigin(mapTiles.back().getLocalBounds().width / 2, mapTiles.back().getLocalBounds().height / 2);
				cout << currentTile << " ";
			}
			cout << endl;
		}
		cout << endl;
		maps.push_back(mapTiles);
	}

	int currentPositionX;
	int currentPositionY;

	for (int i = 0; i < play->getCampaignMap(currentMap)->getMapY(); i++)
		for (int j = 0; j < play->getCampaignMap(currentMap)->getMapX(); j++)
			if (play->getCampaignMap(currentMap)->getTile(j, i) == 'P')
			{
				currentPositionX = j;
				currentPositionY = i;
			}


	window->setKeyRepeatEnabled(false);
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
				state.setActive(false);
				return;
			}

			// transform the mouse position from window coordinates to world coordinates
			sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));
			// Event driven input handling
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if (currentPositionX > 0)
				{
					if (play->getCampaignMap(currentMap)->getTile(currentPositionX - 1, currentPositionY) == 'D')
					{
						play->setCurrentMap(play->getCurrentMap() + 1);
						currentMap = play->getCurrentMap();
						subject->Detach(this);
						if (play->getCurrentMap() < play->getCampaignSize()) {
							subject = play->getCampaignMap(currentMap); // For Observer pattern
							subject->Attach(this);
						}
						if (play->getCurrentMap() >= play->getCampaignSize())
						{
							play->levelUpCharacter();
							play->setCurrentMap(0);
							currentMap = play->getCurrentMap();
							subject->Detach(this);
							subject = play->getCampaignMap(currentMap); // For observer pattern
							subject->Attach(this);
							cout << "Completed the campaign" << endl;
							state.setLaunchState(LaunchState::MENU);
							return;
						}
						play->levelUpCharacter();
						play->placeCharacterOnMap(play->getCampaignMap(currentMap));
						for (int i = 0; i < play->getCampaignMap(currentMap)->getMapY(); i++)
							for (int j = 0; j < play->getCampaignMap(currentMap)->getMapX(); j++)
								if (play->getCampaignMap(currentMap)->getTile(j, i) == 'P')
								{
									currentPositionX = j;
									currentPositionY = i;
								}
					}
					else if (play->getCampaignMap(currentMap)->getTile(currentPositionX - 1, currentPositionY) == 'E')
					{
						// If it's an enemy, you don't move and start combat mode
						Map* map = play->getCampaignMap(currentMap);
						int j = currentPositionX;
						int i = currentPositionY;
						MapObject* player = play->getCharacter();
						MapObject* enemy = map->getObjectTile(j - 1, i);

						Combat::startCombat(map, player, enemy);

						if (static_cast<Character*>(player)->getHitPoints() <= 0) {
							cout << "Player is defeated." << endl;
							play->setCurrentMap(0);
							currentMap = play->getCurrentMap();
							subject->Detach(this);
							subject = play->getCampaignMap(currentMap); // For observer pattern
							subject->Attach(this);
							state.setLaunchState(LaunchState::MENU);
							return;
						}
						else
						{
							cout << "Enemy is defeated." << endl;
							int i = enemy->getMapY();
							int j = enemy->getMapX();
							int iPlayer = player->getMapY();
							int jPlayer = player->getMapX();
							// Take all the fallen items
							delete enemy;
							map->movePlayer(j, i, player);
							play->getCampaignMap(currentMap)->showMap();
							currentPositionX = j;
							currentPositionY = i;
							maps[currentMap].at(jPlayer + iPlayer * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getGroundTexture());
							maps[currentMap].at(currentPositionX + currentPositionY * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getPlayerTexture());
							Combat::activateNPC(map,player);
						}
					}
					else if (play->getCampaignMap(currentMap)->getTile(currentPositionX - 1, currentPositionY) == 'F')
					{
						Map* map = play->getCampaignMap(currentMap);
						int j = currentPositionX;
						int i = currentPositionY;
						MapObject* player = play->getCharacter();
						MapObject* npc = map->getObjectTile(j - 1, i);
						int choice;
						cout << "You encountered a friend.\nYou may choose to: 1. Ignore or 2. Attack" << endl;
						static_cast<Character*>(npc)->executeStrategy(map, npc, player);
						if (static_cast<Character*>(player)->getHitPoints() <= 0) {
							cout << "Played is defeated." << endl;
							state.setLaunchState(LaunchState::MENU);
							return;
						}
						else if (static_cast<Character*>(npc)->getHitPoints() <= 0)
						{
							cout << "NPC is defeated." << endl;
							int i = npc->getMapY();
							int j = npc->getMapX();
							int iPlayer = player->getMapY();
							int jPlayer = player->getMapX();
							delete npc;
							map->movePlayer(j, i, player);
							// Take all the fallen items
							play->getCampaignMap(currentMap)->showMap();
							Combat::activateNPC(map, player);
						}
					}
					else if (play->getCampaignMap(currentMap)->getTile(currentPositionX - 1, currentPositionY) != 'W')
					{
						if (play->moveCharacter(play->getCampaignMap(currentMap), 'L'))
						{
							play->getCampaignMap(currentMap)->showMap();
							maps[currentMap].at(currentPositionX + currentPositionY * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getGroundTexture());
							maps[currentMap].at(currentPositionX - 1 + currentPositionY * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getPlayerTexture());
							currentPositionX--;
							Combat::activateNPC(play->getCampaignMap(currentMap), play->getCharacter());
						}
					}
				}
			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if (currentPositionX < play->getCampaignMap(currentMap)->getMapX() - 1)
				{
					if (play->getCampaignMap(currentMap)->getTile(currentPositionX + 1, currentPositionY) == 'D')
					{
						play->setCurrentMap(play->getCurrentMap() + 1);
						currentMap = play->getCurrentMap();
						subject->Detach(this);
						if (play->getCurrentMap() < play->getCampaignSize()) {
							subject = play->getCampaignMap(currentMap); // For Observer pattern
							subject->Attach(this);
						}
						if (play->getCurrentMap() >= play->getCampaignSize())
						{
							play->levelUpCharacter();
							play->setCurrentMap(0);
							currentMap = play->getCurrentMap();
							subject->Detach(this);
							subject = play->getCampaignMap(currentMap); // For observer pattern
							subject->Attach(this);
							cout << "Completed the campaign" << endl;
							state.setLaunchState(LaunchState::MENU);
							return;
						}
						play->levelUpCharacter();
						play->placeCharacterOnMap(play->getCampaignMap(currentMap));
						for (int i = 0; i < play->getCampaignMap(currentMap)->getMapY(); i++)
							for (int j = 0; j < play->getCampaignMap(currentMap)->getMapX(); j++)
								if (play->getCampaignMap(currentMap)->getTile(j, i) == 'P')
								{
									currentPositionX = j;
									currentPositionY = i;
								}
					}
					else if (play->getCampaignMap(currentMap)->getTile(currentPositionX + 1, currentPositionY) == 'E')
					{
						// If it's an enemy, you don't move and start combat mode
						Map* map = play->getCampaignMap(currentMap);
						int j = currentPositionX;
						int i = currentPositionY;
						MapObject* player = play->getCharacter();
						MapObject* enemy = map->getObjectTile(j + 1, i);
						Combat::startCombat(map, player, enemy);

						if (static_cast<Character*>(player)->getHitPoints() <= 0) {
							cout << "Played is defeated." << endl;
							play->setCurrentMap(0);
							currentMap = play->getCurrentMap();
							subject->Detach(this);
							subject = play->getCampaignMap(currentMap); // For observer pattern
							subject->Attach(this);
							state.setLaunchState(LaunchState::MENU);
							return;
						}
						else
						{
							cout << "Enemy is defeated." << endl;
							int i = enemy->getMapY();
							int j = enemy->getMapX();
							int iPlayer = player->getMapY();
							int jPlayer = player->getMapX();
							// Take all the fallen items
							delete enemy;
							map->movePlayer(j, i, player);
							play->getCampaignMap(currentMap)->showMap();
							currentPositionX = j;
							currentPositionY = i;
							maps[currentMap].at(jPlayer + iPlayer * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getGroundTexture());
							maps[currentMap].at(currentPositionX + currentPositionY * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getPlayerTexture());
							Combat::activateNPC(map, player);
						}
					}
					else if (play->getCampaignMap(currentMap)->getTile(currentPositionX + 1, currentPositionY) == 'F')
					{
						Map* map = play->getCampaignMap(currentMap);
						int j = currentPositionX;
						int i = currentPositionY;
						MapObject* player = play->getCharacter();
						MapObject* npc = map->getObjectTile(j + 1, i);
						static_cast<Character*>(npc)->executeStrategy(map, npc, player);
						if (static_cast<Character*>(player)->getHitPoints() <= 0) {
							cout << "Played is defeated." << endl;
							state.setLaunchState(LaunchState::MENU);
							return;
						}
						else if (static_cast<Character*>(npc)->getHitPoints() <= 0)
						{
							cout << "NPC is defeated." << endl;
							int i = npc->getMapY();
							int j = npc->getMapX();
							int iPlayer = player->getMapY();
							int jPlayer = player->getMapX();
							// Take all the fallen items
							delete npc;
							map->movePlayer(j, i, player);
							play->getCampaignMap(currentMap)->showMap();
							currentPositionX = j;
							currentPositionY = i;
							maps[currentMap].at(jPlayer + iPlayer * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getGroundTexture());
							maps[currentMap].at(currentPositionX + currentPositionY * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getPlayerTexture());
							Combat::activateNPC(map, player);
						}
					}
					else
						if (play->getCampaignMap(currentMap)->getTile(currentPositionX + 1, currentPositionY) != 'W')
						{
							if (play->moveCharacter(play->getCampaignMap(currentMap), 'R'))
							{
								play->getCampaignMap(currentMap)->showMap();
								maps[currentMap].at(currentPositionX + currentPositionY * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getGroundTexture());
								maps[currentMap].at(currentPositionX + 1 + currentPositionY * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getPlayerTexture());
								currentPositionX++;
								Combat::activateNPC(play->getCampaignMap(currentMap), play->getCharacter());
							}
						}
				}
			}



			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && event.KeyReleased)
			{
				if (currentPositionY > 0)
				{
					if (play->getCampaignMap(currentMap)->getTile(currentPositionX, currentPositionY - 1) == 'D')
					{
						play->setCurrentMap(play->getCurrentMap() + 1);
						currentMap = play->getCurrentMap();
						subject->Detach(this);
						if (play->getCurrentMap() < play->getCampaignSize()) {
							subject = play->getCampaignMap(currentMap); // For Observer pattern
							subject->Attach(this);
						}
						if (play->getCurrentMap() >= play->getCampaignSize())
						{
							play->levelUpCharacter();
							play->setCurrentMap(0);
							currentMap = play->getCurrentMap();
							subject->Detach(this);
							subject = play->getCampaignMap(currentMap); // For observer pattern
							subject->Attach(this);
							cout << "Completed the campaign" << endl;
							state.setLaunchState(LaunchState::MENU);
							return;
						}
						play->levelUpCharacter();
						play->placeCharacterOnMap(play->getCampaignMap(currentMap));
						for (int i = 0; i < play->getCampaignMap(currentMap)->getMapY(); i++)
							for (int j = 0; j < play->getCampaignMap(currentMap)->getMapX(); j++)
								if (play->getCampaignMap(currentMap)->getTile(j, i) == 'P')
								{
									currentPositionX = j;
									currentPositionY = i;
								}
					}
					else if (play->getCampaignMap(currentMap)->getTile(currentPositionX, currentPositionY - 1) == 'E')
					{
						// If it's an enemy, you don't move and start combat mode
						Map* map = play->getCampaignMap(currentMap);
						int j = currentPositionX;
						int i = currentPositionY;
						MapObject* player = play->getCharacter();
						MapObject* enemy = map->getObjectTile(j, i-1);
						Combat::startCombat(map, player, enemy);

						if (static_cast<Character*>(player)->getHitPoints() <= 0) {
							cout << "Played is defeated." << endl;
							play->setCurrentMap(0);
							currentMap = play->getCurrentMap();
							subject->Detach(this);
							subject = play->getCampaignMap(currentMap); // For observer pattern
							subject->Attach(this);
							state.setLaunchState(LaunchState::MENU);
							return;
						}
						else
						{
							cout << "Enemy is defeated." << endl;
							int i = enemy->getMapY();
							int j = enemy->getMapX();
							int iPlayer = player->getMapY();
							int jPlayer = player->getMapX();
							// Take all the fallen items
							delete enemy;
							map->movePlayer(j, i, player);
							play->getCampaignMap(currentMap)->showMap();
							currentPositionX = j;
							currentPositionY = i;
							maps[currentMap].at(jPlayer + iPlayer * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getGroundTexture());
							maps[currentMap].at(currentPositionX + currentPositionY * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getPlayerTexture());
							Combat::activateNPC(map, player);
						}
					}
					else if (play->getCampaignMap(currentMap)->getTile(currentPositionX, currentPositionY - 1) == 'F')
					{
						Map* map = play->getCampaignMap(currentMap);
						int j = currentPositionX;
						int i = currentPositionY;
						MapObject* player = play->getCharacter();
						MapObject* npc = map->getObjectTile(j, i - 1);
						static_cast<Character*>(npc)->executeStrategy(map, npc, player);
						if (static_cast<Character*>(player)->getHitPoints() <= 0) {
							cout << "Played is defeated." << endl;
							state.setLaunchState(LaunchState::MENU);
							return;
						}
						else if (static_cast<Character*>(npc)->getHitPoints() <= 0)
						{
							cout << "NPC is defeated." << endl;
							int i = npc->getMapY();
							int j = npc->getMapX();
							int iPlayer = player->getMapY();
							int jPlayer = player->getMapX();
							// Take all the fallen items
							delete npc;
							map->movePlayer(j, i, player);
							play->getCampaignMap(currentMap)->showMap();
							currentPositionX = j;
							currentPositionY = i;
							maps[currentMap].at(jPlayer + iPlayer * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getGroundTexture());
							maps[currentMap].at(currentPositionX + currentPositionY * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getPlayerTexture());
							Combat::activateNPC(map, player);
						}
					}
					else
						if (play->getCampaignMap(currentMap)->getTile(currentPositionX, currentPositionY - 1) != 'W')
						{
							if (play->moveCharacter(play->getCampaignMap(currentMap), 'U'))
							{
								play->getCampaignMap(currentMap)->showMap();
								maps[currentMap].at(currentPositionX + currentPositionY * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getGroundTexture());
								maps[currentMap].at(currentPositionX + (currentPositionY - 1) * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getPlayerTexture());
								currentPositionY--;
								Combat::activateNPC(play->getCampaignMap(currentMap), play->getCharacter());
							}
						}
				}
			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && event.KeyReleased)
			{
				if (currentPositionY < play->getCampaignMap(currentMap)->getMapY() - 1)
				{
					if (play->getCampaignMap(currentMap)->getTile(currentPositionX, currentPositionY + 1) == 'D')
					{
						play->setCurrentMap(play->getCurrentMap() + 1);
						currentMap = play->getCurrentMap();
						subject->Detach(this);
						if (play->getCurrentMap() < play->getCampaignSize()) {
							subject = play->getCampaignMap(currentMap); // For Observer pattern
							subject->Attach(this);
						}
						if (play->getCurrentMap() >= play->getCampaignSize())
						{
							play->levelUpCharacter();
							play->setCurrentMap(0);
							currentMap = play->getCurrentMap();
							subject->Detach(this);
							subject = play->getCampaignMap(currentMap); // For observer pattern
							subject->Attach(this);
							cout << "Completed the campaign" << endl;
							state.setLaunchState(LaunchState::MENU);
							return;
						}
						play->placeCharacterOnMap(play->getCampaignMap(currentMap));
						for (int i = 0; i < play->getCampaignMap(currentMap)->getMapY(); i++)
							for (int j = 0; j < play->getCampaignMap(currentMap)->getMapX(); j++)
								if (play->getCampaignMap(currentMap)->getTile(j, i) == 'P')
								{
									currentPositionX = j;
									currentPositionY = i;
								}
					}
					else if (play->getCampaignMap(currentMap)->getTile(currentPositionX, currentPositionY + 1) == 'E')
					{
						// If it's an enemy, you don't move and start combat mode
						Map* map = play->getCampaignMap(currentMap);
						int j = currentPositionX;
						int i = currentPositionY;
						MapObject* player = play->getCharacter();
						MapObject* enemy = map->getObjectTile(j, i + 1);
						Combat::startCombat(map, player, enemy);

						if (static_cast<Character*>(player)->getHitPoints() <= 0) {
							cout << "Played is defeated." << endl;
							play->setCurrentMap(0);
							currentMap = play->getCurrentMap();
							subject->Detach(this);
							subject = play->getCampaignMap(currentMap); // For observer pattern
							subject->Attach(this);
							state.setLaunchState(LaunchState::MENU);
							return;
						}
						else
						{
							cout << "Enemy is defeated." << endl;
							int i = enemy->getMapY();
							int j = enemy->getMapX();
							int iPlayer = player->getMapY();
							int jPlayer = player->getMapX();
							// Take all the fallen items
							delete enemy;
							map->movePlayer(j, i, player);
							play->getCampaignMap(currentMap)->showMap();
							currentPositionX = j;
							currentPositionY = i;
							maps[currentMap].at(jPlayer + iPlayer * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getGroundTexture());
							maps[currentMap].at(currentPositionX + currentPositionY * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getPlayerTexture());
							Combat::activateNPC(map, player);
						}
					}
					else if (play->getCampaignMap(currentMap)->getTile(currentPositionX, currentPositionY + 1) == 'F')
					{
						cout << "You encountered a friend!" << endl;
						Map* map = play->getCampaignMap(currentMap);
						int j = currentPositionX;
						int i = currentPositionY;
						MapObject* player = play->getCharacter();
						MapObject* npc = map->getObjectTile(j, i + 1);
						static_cast<Character*>(npc)->executeStrategy(map, npc, player);
						if (static_cast<Character*>(player)->getHitPoints() <= 0) {
							cout << "Played is defeated." << endl;
							state.setLaunchState(LaunchState::MENU);
							return;
						}
						else if (static_cast<Character*>(npc)->getHitPoints() <= 0)
						{
							cout << "NPC is defeated." << endl;
							int i = npc->getMapY();
							int j = npc->getMapX();
							int iPlayer = player->getMapY();
							int jPlayer = player->getMapX();
							// Take all the fallen items
							delete npc;
							map->movePlayer(j, i, player);
							play->getCampaignMap(currentMap)->showMap();
							currentPositionX = j;
							currentPositionY = i;
							maps[currentMap].at(jPlayer + iPlayer * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getGroundTexture());
							maps[currentMap].at(currentPositionX + currentPositionY * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getPlayerTexture());
							Combat::activateNPC(map, player);
						}
					}
					else
						if (play->getCampaignMap(currentMap)->getTile(currentPositionX, currentPositionY + 1) != 'W')
						{
							if (play->moveCharacter(play->getCampaignMap(currentMap), 'D'))
							{
								play->getCampaignMap(currentMap)->showMap();
								maps[currentMap].at(currentPositionX + currentPositionY * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getGroundTexture());
								maps[currentMap].at(currentPositionX + (currentPositionY + 1) * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getPlayerTexture());
								currentPositionY++;
								Combat::activateNPC(play->getCampaignMap(currentMap), play->getCharacter());
							}
						}
				}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{
				for (int i = 0; i < play->getCampaignMap(currentMap)->getMapY(); i++)
				{
					for (int j = 0; j < play->getCampaignMap(currentMap)->getMapX(); j++)
					{
						if (play->getCampaignMap(currentMap)->getTile(j, i) == 'C')
						{
							if (maps[currentMap].at(j + i * play->getCampaignMap(currentMap)->getMapX()).getGlobalBounds().contains(mousePosition))
								static_cast<ItemContainer*>(play->getCampaignMap(currentMap)->getObjectTile(j, i))->displayItems();
						}

						if (play->getCampaignMap(currentMap)->getTile(j, i) == 'P')
						{
							if (maps[currentMap].at(j + i * play->getCampaignMap(currentMap)->getMapX()).getGlobalBounds().contains(mousePosition))
							{
								static_cast<Character*>(play->getCampaignMap(currentMap)->getObjectTile(j, i))->displayCharacterInfo();
								static_cast<Character*>(play->getCampaignMap(currentMap)->getObjectTile(j, i))->displayEquipment();
								static_cast<Character*>(play->getCampaignMap(currentMap)->getObjectTile(j, i))->displayBackpack();
							}
						}


						if (play->getCampaignMap(currentMap)->getTile(j, i) == 'E')
						{
							if (maps[currentMap].at(j + i * play->getCampaignMap(currentMap)->getMapX()).getGlobalBounds().contains(mousePosition))
							{
								static_cast<Character*>(play->getCampaignMap(currentMap)->getObjectTile(j, i))->displayCharacterInfo();
								static_cast<Character*>(play->getCampaignMap(currentMap)->getObjectTile(j, i))->displayEquipment();
							}
						}

						if (play->getCampaignMap(currentMap)->getTile(j, i) == 'F')
						{
							if (maps[currentMap].at(j + i * play->getCampaignMap(currentMap)->getMapX()).getGlobalBounds().contains(mousePosition))
							{
								static_cast<Character*>(play->getCampaignMap(currentMap)->getObjectTile(j, i))->displayCharacterInfo();
								static_cast<Character*>(play->getCampaignMap(currentMap)->getObjectTile(j, i))->displayEquipment();
							}
						}
					}
				}

				if (modifyButton.contains(mousePosition))
				{
					play->modifyEquipment();
				}

				if (menuButton.contains(mousePosition))
				{
					play->setCurrentMap(0);
					currentMap = play->getCurrentMap();
					subject->Detach(this);
					subject = play->getCampaignMap(currentMap); // For observer pattern
					subject->Attach(this);
					state.setLaunchState(LaunchState::MENU);
					return;
				}

				if (mapButton.contains(mousePosition))
				{
					if (!mapClicked)
					{
						mapClicked = true;
						cout << "Map info toggled" << endl;
						//Add logic here after
					}
					else
					{
						mapClicked = false;
						cout << "Map info toggled off" << endl;
					}

				}

				if (eventButton.contains(mousePosition))
				{
					if (!eventClicked)
					{
						eventClicked = true;
						cout << "Game events info toggled" << endl;
						//Add logic here after
					}
					else
					{
						eventClicked = false;
						cout << "Game events toggled off" << endl;
					}
				}

				if (combatButton.contains(mousePosition))
				{
					if (!combatClicked)
					{
						combatClicked = true;
						cout << "Combat info toggled" << endl;
						//Add logic here after
					}
					else
					{
						combatClicked = false;
						cout << "Combat info toggled off" << endl;
					}

				}

				if (diceButton.contains(mousePosition))
				{
					if (!diceClicked)
					{
						diceClicked = true;
						cout << "Dice info toggled on" << endl;
						//Add logic here after
					}
					else
					{
						diceClicked = false;
						cout << "Dice info toggled off" << endl;
					}
				}
			}

			if (modifyButton.contains(mousePosition) && !modifyClicked)
				modifyText.setFillColor(hoverColor);
			else
				if (mapButton.contains(mousePosition) && !mapClicked)
					mapText.setFillColor(hoverColor);
				else
					if (combatButton.contains(mousePosition) && !combatClicked)
						combatText.setFillColor(hoverColor);
					else
						if (eventButton.contains(mousePosition) && !eventClicked)
							eventText.setFillColor(hoverColor);
						else
							if (diceButton.contains(mousePosition) && !diceClicked)
								diceText.setFillColor(hoverColor);
							else
								if (menuButton.contains(mousePosition) && !menuClicked)
									menuText.setFillColor(hoverColor);
								else
								{
									if (!modifyClicked)
										modifyText.setFillColor(normalColor);

									if (!menuClicked)
										menuText.setFillColor(normalColor);

									if (!diceClicked)
										diceText.setFillColor(normalColor);

									if (!combatClicked)
										combatText.setFillColor(normalColor);

									if (!mapClicked)
										mapText.setFillColor(normalColor);

									if (!eventClicked)
										eventText.setFillColor(normalColor);
								}
		}

		window->clear();
		for (int i = 0; i < maps[currentMap].size(); i++)
			window->draw(maps[currentMap].at(i));
		window->draw(modifyText);
		window->draw(menuText);
		window->draw(mapText);
		window->draw(combatText);
		window->draw(eventText);
		window->draw(diceText);
		window->display();
	}
}

void PlayGUI::UpdateGUI() {
	if (subject != NULL) {
		int type;
		for (int i = 0; i < subject->getMapY(); i++)
		{
			for (int j = 0; j < subject->getMapX(); j++)
			{
				MapObject* object = subject->getObjectTile(j, i);
				if (object == NULL) {
					maps[currentMap].at(j + i * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getGroundTexture());
				}
				else
				{
					type = subject->getTile(j, i);
					if (type == 'F') {
						maps[currentMap].at(j + i * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getFriendlyTexture());
					}
					if (type == 'E') {
						maps[currentMap].at(j + i * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getEnemyTexture());
					}
					if (type == 'P') {
						maps[currentMap].at(j + i * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getPlayerTexture());
					}
					if (type == 'C') {
						maps[currentMap].at(j + i * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getTreasureTexture());
					}
				}
				
			}
		}
	}
}

PlayGUI::~PlayGUI()
{
}