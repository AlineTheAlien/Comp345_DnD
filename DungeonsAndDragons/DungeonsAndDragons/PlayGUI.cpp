#include "stdafx.h"
#include "PlayGUI.h"


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
					for (int j = 0; j < buttons.size(); j++) {
						newCharacterClicked = true;
						clicked.at(j) = false;
					}
				}

				if (nextButton.contains(mousePosition))
				{
					for (int i = 0; i < clicked.size(); i++)
						if (clicked.at(i))
						{
							if(play->loadCharacter(play->getAvailableCharacters(i)))
							{
								state.setPlayState(PlayState::CAMPAIGN_SELECTION);
								return;
							}
						}

					if (newCharacterClicked)
					{
						play->createNewCharacter();
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
					if (!nextClicked)
						nextText.setFillColor(normalColor);
					if (!backClicked)
						backText.setFillColor(normalColor);
					if (!newCharacterClicked)
						newCharacterText.setFillColor(normalColor);
				}
			}

			if (nextButton.contains(mousePosition) && !nextClicked)
				nextText.setFillColor(hoverColor);

			if (newCharacterButton.contains(mousePosition) && !newCharacterClicked)
				newCharacterText.setFillColor(hoverColor);

			if (backButton.contains(mousePosition) && !backClicked)
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
	vector<vector<sf::Sprite>> maps;
	int currentMap = 0;

	sf::Text nextText;
	sf::Text backText;
	sf::Text menuText;
	sf::FloatRect nextButton;
	sf::FloatRect backButton;
	sf::FloatRect menuButton;
	sf::Font textFont;
	sf::Color normalColor = sf::Color::White;
	sf::Color hoverColor = sf::Color::Yellow;
	sf::Color clickedColor = sf::Color::Yellow;
	bool nextClicked = false;
	bool backClicked = false;
	bool menuClicked = false;


	if (!textFont.loadFromFile("Fonts/OldSchool.ttf"))
	{
		// error...
	}

	nextText.setString("Next");
	nextText.setFont(textFont);
	nextText.setStyle(sf::Text::Italic);
	nextText.setCharacterSize(15);

	backText.setString("Back");
	backText.setFont(textFont);
	backText.setStyle(sf::Text::Italic);
	backText.setCharacterSize(15);

	menuText.setString("Menu");
	menuText.setFont(textFont);
	menuText.setStyle(sf::Text::Italic);
	menuText.setCharacterSize(15);

	nextText.setPosition(sf::Vector2f(500, GameState::WINDOW_SCALE - 100));
	backText.setPosition(sf::Vector2f(300, GameState::WINDOW_SCALE - 100));
	menuText.setPosition(sf::Vector2f(700, 300));

	nextButton = nextText.getGlobalBounds();
	backButton = backText.getGlobalBounds();
	menuButton = menuText.getGlobalBounds();

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
				mapTiles.back().setPosition(k * mapTiles.back().getLocalBounds().width, j * mapTiles.back().getLocalBounds().height);
				//mapTiles.back().setOrigin(mapTiles.back().getLocalBounds().width / 2, mapTiles.back().getLocalBounds().height / 2);
				cout << currentTile << " ";
			}
			cout << endl;
		}
		cout << endl;
		maps.push_back(mapTiles);
	}

	play->placeCharacterOnMap(play->getCampaignMap(currentMap));
	int currentPositionX;
	int currentPositionY;

	for (int i = 0; i < play->getCampaignMap(currentMap)->getMapY(); i++)
	{
		for (int j = 0; j < play->getCampaignMap(currentMap)->getMapX(); j++)
		{
			if (play->getCampaignMap(currentMap)->getTile(j, i) == 'P')
			{
				currentPositionX = j;
				currentPositionY = i;
			}

		}
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
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && event.KeyReleased &&
					!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					if (currentPositionX > 0)
					if (play->getCampaignMap(currentMap)->getObjectTile(currentPositionX - 1, currentPositionY) == NULL)
						if (play->moveCharacter(play->getCampaignMap(currentMap), 'L'))
						{
							play->getCampaignMap(currentMap)->showMap();
							maps[currentMap].at(currentPositionX + currentPositionY * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getGroundTexture());
							maps[currentMap].at(currentPositionX - 1 + currentPositionY * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getPlayerTexture());
							currentPositionX--;
						}

				}
				else
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && event.KeyReleased
					&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))

				{
					if (currentPositionX < play->getCampaignMap(currentMap)->getMapX() - 1)
					if (play->getCampaignMap(currentMap)->getObjectTile(currentPositionX + 1, currentPositionY) == NULL)
						if (play->moveCharacter(play->getCampaignMap(currentMap), 'R'))
						{
							play->getCampaignMap(currentMap)->showMap();
							maps[currentMap].at(currentPositionX + currentPositionY * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getGroundTexture());
							maps[currentMap].at(currentPositionX + 1 + currentPositionY * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getPlayerTexture());
							currentPositionX++;
						}
				}
				else
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && event.KeyReleased
					&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					if (currentPositionY > 0)
					if (play->getCampaignMap(currentMap)->getObjectTile(currentPositionX, currentPositionY - 1) == NULL)				
						if (play->moveCharacter(play->getCampaignMap(currentMap), 'U'))
						{
							play->getCampaignMap(currentMap)->showMap();
							maps[currentMap].at(currentPositionX + currentPositionY * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getGroundTexture());
							maps[currentMap].at(currentPositionX + (currentPositionY - 1) * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getPlayerTexture());
							currentPositionY--;
						}			
				}
				else
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && event.KeyReleased
					&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					if (currentPositionY < play->getCampaignMap(currentMap) -> getMapY() - 1)
					if (play->getCampaignMap(currentMap)->getObjectTile(currentPositionX, currentPositionY + 1) == NULL)
						if (play->moveCharacter(play->getCampaignMap(currentMap), 'D'))
						{
							play->getCampaignMap(currentMap)->showMap();
							maps[currentMap].at(currentPositionX + currentPositionY * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getGroundTexture());
							maps[currentMap].at(currentPositionX + (currentPositionY + 1) * play->getCampaignMap(currentMap)->getMapX()).setTexture(textures.getPlayerTexture());
							currentPositionY++;
						}
				}
		
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{


				for (int i = 0; i <  play->getCampaignMap(currentMap)->getMapY(); i++)
				{
					for (int j = 0; j < play->getCampaignMap(currentMap)->getMapX(); j++)
					{
						if (play->getCampaignMap(currentMap)->getTile(j, i) == 'C')
						{
							if (maps[currentMap].at(j + i * play->getCampaignMap(currentMap)->getMapX()).getGlobalBounds().contains(mousePosition))
							{
								static_cast<ItemContainer*>(play->getCampaignMap(currentMap)->getObjectTile(j, i))->displayItems();
							}
						
						}

						if (play->getCampaignMap(currentMap)->getTile(j, i) == 'P')
						{
							if (maps[currentMap].at(j + i * play->getCampaignMap(currentMap)->getMapX()).getGlobalBounds().contains(mousePosition))
							{
								static_cast<Character*>(play->getCampaignMap(currentMap)->getObjectTile(j, i))->displayCharacterInfo();
								static_cast<Character*>(play->getCampaignMap(currentMap)->getObjectTile(j, i))->displayEquipment();
							}
						}

					}
				}

				// hit test
				if (nextButton.contains(mousePosition))
				{
					if (currentMap < maps.size() - 1)
					{
						currentMap++;
						play->placeCharacterOnMap(play->getCampaignMap(currentMap));
					}
				}

				if (backButton.contains(mousePosition))
				{
					if (currentMap > 0)
					{
						currentMap--;
						play->placeCharacterOnMap(play->getCampaignMap(currentMap));
					}
				}

				if (menuButton.contains(mousePosition))
				{
					state.setLaunchState(LaunchState::MENU);
					return;
				}
			}

			if (nextButton.contains(mousePosition) && !nextClicked)
				nextText.setFillColor(hoverColor);
			else
				if (backButton.contains(mousePosition) && !backClicked)
					backText.setFillColor(hoverColor);
				else
					if (menuButton.contains(mousePosition) && !menuClicked)
						menuText.setFillColor(hoverColor);
					else
					{
						if (!nextClicked)
							nextText.setFillColor(normalColor);

						if (!backClicked)
							backText.setFillColor(normalColor);

						if (!menuClicked)
							menuText.setFillColor(normalColor);
					}
		}

		window->clear();
		for (int i = 0; i < maps[currentMap].size(); i++)
			window->draw(maps[currentMap].at(i));
		window->draw(nextText);
		window->draw(backText);
		window->draw(menuText);
		window->display();
	}
}

PlayGUI::~PlayGUI()
{
}
