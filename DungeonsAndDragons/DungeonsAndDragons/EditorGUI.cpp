//! @file 
//! @brief Implementation file for EditorGUI class

#include "stdafx.h"
#include "EditorGUI.h"

EditorGUI::EditorGUI()
{
	window = new sf::RenderWindow(sf::VideoMode(EditorGUI::WINDOW_SCALE, EditorGUI::WINDOW_SCALE), "Map Editor", sf::Style::Titlebar | sf::Style::Close);
	mapEditor = new MapEditor();
	campaignEditor = new CampaignEditor();
}

//! Implementation of non default constructor for EditorGUI class
//! @param newWindow : a reference to a RenderWindow value
//! @param newMapEditor : pointer to a newMapEditor object 
//! @param newCampaignEditor : pointer 
EditorGUI::EditorGUI(sf::RenderWindow &newWindow)
{
	mapEditor = new MapEditor();
	campaignEditor = new CampaignEditor();
	window = &newWindow;
}

//! Implementation of Start to initialize the editor to the first state and the first view
void EditorGUI::Start()
{
	state.setActive(true);
	state.setEditorState(EditorState::MENU);
	Update();
}

//! Implementation of Update to change the state of the editor
void EditorGUI::Update()
{
	while (state.isActive())
	{
		string currentEditorState = "";
		string currentState = "";

		if (state.getEditorState() == EditorState::MENU)
			currentEditorState = "EDITOR_MENU";

		if (state.getEditorState() == EditorState::CAMPAIGN_EDITOR)
		{
			currentEditorState = "CAMPAIGN_EDITOR";
			if (state.getCampaignEditorState() == CampaignEditorState::CAMPAIGN_EDITOR_MENU)
				currentState = "CAMPAIN_EDITOR_MENU";
			if (state.getCampaignEditorState() == CampaignEditorState::CAMPAIGN_SELECTION)
				currentState = "CAMPAIGN_SELECTION";
			if (state.getCampaignEditorState() == CampaignEditorState::MAPLIST_SELECTION)
				currentState = "MAPLIST_SELECTION";
			if (state.getCampaignEditorState() == CampaignEditorState::CAMPAIGN_VIEW)
				currentState = "CAMPAIGN_VIEW";
		}

		if (state.getEditorState() == EditorState::MAP_EDITOR)
		{
			currentEditorState = "MAP_EDITOR";
			if (state.getMapEditorState() == MapEditorState::MAP_EDITOR_MENU)
				currentState = "MAP_EDITOR_MENU";
			if (state.getMapEditorState() == MapEditorState::MAP_SELECTION)
				currentState = "SIZE_SELECTION";
			if (state.getMapEditorState() == MapEditorState::MAP_SELECTION)
				currentState = "MAP_SELECTION";
			if (state.getMapEditorState() == MapEditorState::MAP_VIEW)
				currentState = "MAP_VIEW";
		}

		if (state.getLaunchState() == LaunchState::MENU)
			return;

		cout << "The edtior has changed state to : " << currentEditorState << " : " << currentState << endl;

		Display();
	}
}

//! Implementation of Display to change the view according to the current state
void EditorGUI::Display()
{
	if (state.getEditorState() == EditorState::MENU)
		openEditorWindow();
	else
		if (state.getEditorState() == EditorState::MAP_EDITOR)
		{
			if (state.getMapEditorState() == MapEditorState::MAP_EDITOR_MENU)
				openMapEditorWindow();
			else
				if (state.getMapEditorState() == MapEditorState::SIZE_SELECTION)
					openNewMapWindow();
				else
					if (state.getMapEditorState() == MapEditorState::MAP_SELECTION)
						openLoadMapWindow();
					else
						if (state.getMapEditorState() == MapEditorState::MAP_VIEW)
							openMapView();
		}
		else
			if (state.getEditorState() == EditorState::CAMPAIGN_EDITOR)
			{
				if (state.getCampaignEditorState() == CampaignEditorState::CAMPAIGN_EDITOR_MENU)
					openCampaignEditorWindow();
				else
					if (state.getCampaignEditorState() == CampaignEditorState::MAPLIST_SELECTION)
						openMapListSelectionWindow();
					else
						if (state.getCampaignEditorState() == CampaignEditorState::CAMPAIGN_SELECTION)
							openLoadCampaignWindow();
						else
							if (state.getCampaignEditorState() == CampaignEditorState::CAMPAIGN_VIEW)
								openCampaignView();
			}

}

//Editor view

//!Implementation of openEditorWindow to allow selection of map editor or campaign editor
void EditorGUI::openEditorWindow()
{

	sf::FloatRect mapEditorButton;
	sf::FloatRect campaignEditorButton;
	sf::FloatRect nextButton;
	sf::FloatRect backButton;

	sf::Text mapEditorText;
	sf::Text campaignEditorText;
	sf::Text nextText;
	sf::Text backText;

	sf::Font textFont;
	sf::Color normalColor = sf::Color::White;
	sf::Color hoverColor = sf::Color::Yellow;
	sf::Color clickedColor = sf::Color::Yellow;
	bool mapEditorClicked = false;
	bool campaignEditorClicked = false;
	bool nextClicked = false;
	bool backClicked = false;

	if (!textFont.loadFromFile("Fonts/OldSchool.ttf"))
	{
		// error...
	}


	mapEditorText.setString("Map Editor");
	mapEditorText.setFont(textFont);
	mapEditorText.setStyle(sf::Text::Italic);
	mapEditorText.setCharacterSize(20);

	campaignEditorText.setString("Campaign Editor");
	campaignEditorText.setFont(textFont);
	campaignEditorText.setStyle(sf::Text::Italic);
	campaignEditorText.setCharacterSize(20);

	nextText.setString("Next");
	nextText.setFont(textFont);
	nextText.setStyle(sf::Text::Italic);
	nextText.setCharacterSize(15);

	backText.setString("Back");
	backText.setFont(textFont);
	backText.setStyle(sf::Text::Italic);
	backText.setCharacterSize(15);

	mapEditorText.setPosition(sf::Vector2f(300, 200));
	campaignEditorText.setPosition(sf::Vector2f(260, 400));
	nextText.setPosition(sf::Vector2f(WINDOW_SCALE - 150, WINDOW_SCALE - 100));
	backText.setPosition(sf::Vector2f(150, WINDOW_SCALE - 100));


	mapEditorButton = mapEditorText.getGlobalBounds();
	campaignEditorButton = campaignEditorText.getGlobalBounds();
	nextButton = nextText.getGlobalBounds();
	backButton = backText.getGlobalBounds();

	window->setKeyRepeatEnabled(false);
	window->setFramerateLimit(60);
	window->setVerticalSyncEnabled(true);
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

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{

				// hit test
				if (mapEditorButton.contains(mousePosition))
				{
					mapEditorText.setFillColor(clickedColor);
					campaignEditorText.setFillColor(normalColor);
					mapEditorClicked = true;
					campaignEditorClicked = false;
				}

				if (campaignEditorButton.contains(mousePosition))
				{
					mapEditorText.setFillColor(normalColor);
					campaignEditorText.setFillColor(clickedColor);
					mapEditorClicked = false;
					campaignEditorClicked = true;
				}

				if (backButton.contains(mousePosition))
				{
					state.setLaunchState(LaunchState::MENU);
					return;
				}

				if (nextButton.contains(mousePosition))
				{
					if (mapEditorClicked)
					{
						state.setEditorState(EditorState::MAP_EDITOR);
						return;
					}
					if (campaignEditorClicked)
					{
						state.setEditorState(EditorState::CAMPAIGN_EDITOR);
						return;
					}
				}
			}

			if (mapEditorButton.contains(mousePosition) && !mapEditorClicked)
				mapEditorText.setFillColor(hoverColor);
			else
				if (campaignEditorButton.contains(mousePosition) && !campaignEditorClicked)
					campaignEditorText.setFillColor(hoverColor);
				else
					if (nextButton.contains(mousePosition) && !nextClicked)
						nextText.setFillColor(hoverColor);
					else
						if (backButton.contains(mousePosition) && !backClicked)
							backText.setFillColor(hoverColor);
					else
					{
						if (!campaignEditorClicked)
							campaignEditorText.setFillColor(normalColor);

						if (!mapEditorClicked)
							mapEditorText.setFillColor(normalColor);

						if (!nextClicked)
							nextText.setFillColor(normalColor);

						if (!backClicked)
							backText.setFillColor(normalColor);
					}
		}

		window->clear();
		window->draw(backText);
		window->draw(mapEditorText);
		window->draw(campaignEditorText);
		window->draw(nextText);
		window->display();
	}
}

//Map Editor views

//! Implementation of openMapEditorWindow to initialize map editor
void EditorGUI::openMapEditorWindow()
{
	sf::FloatRect newMapButton;
	sf::FloatRect loadMapButton;
	sf::FloatRect nextButton;
	sf::FloatRect backButton;
	sf::Text newMapText;
	sf::Text loadMapText;
	sf::Text nextText;
	sf::Text backText;
	sf::Font textFont;
	sf::Color normalColor = sf::Color::White;
	sf::Color hoverColor = sf::Color::Yellow;
	sf::Color clickedColor = sf::Color::Yellow;
	bool newMapClicked = false;
	bool loadMapClicked = false;
	bool nextClicked = false;
	bool backClicked = false;
	if (!textFont.loadFromFile("Fonts/OldSchool.ttf"))
	{
		// error...
	}

	newMapText.setString("New map");
	newMapText.setFont(textFont);
	newMapText.setStyle(sf::Text::Italic);
	newMapText.setCharacterSize(30);

	loadMapText.setString("Load map");
	loadMapText.setFont(textFont);
	loadMapText.setStyle(sf::Text::Italic);
	loadMapText.setCharacterSize(30);

	nextText.setString("Next");
	nextText.setFont(textFont);
	nextText.setStyle(sf::Text::Italic);
	nextText.setCharacterSize(15);

	backText.setString("Back");
	backText.setFont(textFont);
	backText.setStyle(sf::Text::Italic);
	backText.setCharacterSize(15);


	newMapText.setPosition(sf::Vector2f(300, 200));
	loadMapText.setPosition(sf::Vector2f(300, 400));
	nextText.setPosition(sf::Vector2f(WINDOW_SCALE - 150, WINDOW_SCALE - 100));
	backText.setPosition(sf::Vector2f(100, WINDOW_SCALE - 100));

	newMapButton = newMapText.getGlobalBounds();
	loadMapButton = loadMapText.getGlobalBounds();
	nextButton = nextText.getGlobalBounds();
	backButton = backText.getGlobalBounds();

	window->setKeyRepeatEnabled(false);
	window->setFramerateLimit(60);
	window->setVerticalSyncEnabled(true);
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

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{

				// hit test
				if (newMapButton.contains(mousePosition))
				{
					newMapText.setFillColor(clickedColor);
					loadMapText.setFillColor(normalColor);
					newMapClicked = true;
					loadMapClicked = false;
				}

				if (loadMapButton.contains(mousePosition))
				{
					newMapText.setFillColor(normalColor);
					loadMapText.setFillColor(clickedColor);
					newMapClicked = false;
					loadMapClicked = true;
				}

				if (nextButton.contains(mousePosition))
				{
					if (newMapClicked)
					{
						state.setMapEditorState(MapEditorState::SIZE_SELECTION);
						return;
					}
					if (loadMapClicked)
					{
						state.setMapEditorState(MapEditorState::MAP_SELECTION);
						mapEditor->setAvailableMaps();
						return;
					}
				}

				if (backButton.contains(mousePosition))
				{
					state.setMapEditorState(MapEditorState::MAP_EDITOR_MENU);
					state.setEditorState(EditorState::MENU);
					return;
				}
			}

			if (newMapButton.contains(mousePosition) && !newMapClicked)
				newMapText.setFillColor(hoverColor);
			else
				if (loadMapButton.contains(mousePosition) && !loadMapClicked)
					loadMapText.setFillColor(hoverColor);
				else
					if (nextButton.contains(mousePosition) && !nextClicked)
						nextText.setFillColor(hoverColor);
					else
						if (backButton.contains(mousePosition) && !backClicked)
							backText.setFillColor(hoverColor);
						else
						{
							if (!loadMapClicked)
								loadMapText.setFillColor(normalColor);

							if (!newMapClicked)
								newMapText.setFillColor(normalColor);

							if (!nextClicked)
								nextText.setFillColor(normalColor);

							if (!backClicked)
								backText.setFillColor(normalColor);
						}
		}

		window->clear();
		window->draw(newMapText);
		window->draw(loadMapText);
		window->draw(nextText);
		window->draw(backText);
		window->display();
	}
}

//! Implementation of openNewMapWindow to select the size of the new map
void EditorGUI::openNewMapWindow()
{
	vector<sf::FloatRect> buttons;
	vector<sf::Text> texts;
	vector<bool> clicked;

	sf::FloatRect size1Button;
	sf::FloatRect size2Button;
	sf::FloatRect size3Button;
	sf::FloatRect size4Button;
	sf::FloatRect nextButton;
	sf::FloatRect backButton;

	sf::Text size1Text;
	sf::Text size2Text;
	sf::Text size3Text;
	sf::Text size4Text;
	sf::Text nextText;
	sf::Text backText;

	sf::Font textFont;
	sf::Color normalColor = sf::Color::White;
	sf::Color hoverColor = sf::Color::Yellow;
	sf::Color clickedColor = sf::Color::Yellow;

	bool size1Clicked = false;
	bool size2Clicked = false;
	bool size3Clicked = false;
	bool size4Clicked = false;
	bool nextClicked = false;
	bool backClicked = false;

	if (!textFont.loadFromFile("Fonts/OldSchool.ttf"))
	{
		// error...
	}

	size1Text.setString("10 x 10");
	size1Text.setFont(textFont);
	size1Text.setStyle(sf::Text::Italic);
	size1Text.setCharacterSize(30);

	size2Text.setString("20 x 20");
	size2Text.setFont(textFont);
	size2Text.setStyle(sf::Text::Italic);
	size2Text.setCharacterSize(30);

	size3Text.setString("10 x 15");
	size3Text.setFont(textFont);
	size3Text.setStyle(sf::Text::Italic);
	size3Text.setCharacterSize(30);

	size4Text.setString("15 x 20");
	size4Text.setFont(textFont);
	size4Text.setStyle(sf::Text::Italic);
	size4Text.setCharacterSize(30);

	nextText.setString("Next");
	nextText.setFont(textFont);
	nextText.setStyle(sf::Text::Italic);
	nextText.setCharacterSize(15);

	backText.setString("Back");
	backText.setFont(textFont);
	backText.setStyle(sf::Text::Italic);
	backText.setCharacterSize(15);

	size1Text.setPosition(sf::Vector2f(300, 100));
	size2Text.setPosition(sf::Vector2f(300, 200));
	size3Text.setPosition(sf::Vector2f(300, 300));
	size4Text.setPosition(sf::Vector2f(300, 400));
	nextText.setPosition(sf::Vector2f(WINDOW_SCALE - 150, WINDOW_SCALE - 100));
	backText.setPosition(sf::Vector2f(100, WINDOW_SCALE - 100));

	size1Button = size1Text.getGlobalBounds();
	size2Button = size2Text.getGlobalBounds();
	size3Button = size3Text.getGlobalBounds();
	size4Button = size4Text.getGlobalBounds();
	nextButton = nextText.getGlobalBounds();
	backButton = backText.getGlobalBounds();

	buttons.push_back(size1Button);
	buttons.push_back(size2Button);
	buttons.push_back(size3Button);
	buttons.push_back(size4Button);

	texts.push_back(size1Text);
	texts.push_back(size2Text);
	texts.push_back(size3Text);
	texts.push_back(size4Text);

	clicked.push_back(size1Clicked);
	clicked.push_back(size2Clicked);
	clicked.push_back(size3Clicked);
	clicked.push_back(size4Clicked);

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
					if (clicked.at(0))
					{
						mapEditor->newMap(10, 10);
						state.setMapEditorState(MapEditorState::MAP_VIEW);
						return;
					}
					else
						if (clicked.at(1))
						{
							mapEditor->newMap(20, 20);
							state.setMapEditorState(MapEditorState::MAP_VIEW);
							return;
						}
						else
							if (clicked.at(2))
							{
								mapEditor->newMap(10, 15);
								state.setMapEditorState(MapEditorState::MAP_VIEW);
								return;
							}
							else
								if (clicked.at(3))
								{
									mapEditor->newMap(15, 20);
									state.setMapEditorState(MapEditorState::MAP_VIEW);
									return;
								}
					//Change state
				}

				if (backButton.contains(mousePosition))
				{
					state.setMapEditorState(MapEditorState::MAP_EDITOR_MENU);
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

//! Implementation of openLoadMapWindow to select the map to load and edit
void EditorGUI::openLoadMapWindow()
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
	for (int i = 0; i < mapEditor->getAvailableMapsSize(); i++)
	{
		texts.push_back(sf::Text());
		texts.back().setString(mapEditor->getAvailableMap(i));
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

	nextText.setPosition(sf::Vector2f(WINDOW_SCALE - 150, WINDOW_SCALE - 100));
	nextText.setString("Next");
	nextText.setFont(textFont);
	nextText.setStyle(sf::Text::Italic);
	nextText.setCharacterSize(15);
	nextButton = nextText.getGlobalBounds();

	backText.setPosition(sf::Vector2f(100, WINDOW_SCALE - 100));
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
				window->close();
				state.setActive(false);
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
							mapEditor->loadMap(mapEditor->getAvailableMap(i));
							state.setMapEditorState(MapEditorState::MAP_VIEW);
							return;
						}
					//Change state
				}

				if (backButton.contains(mousePosition))
				{
					state.setMapEditorState(MapEditorState::MAP_EDITOR_MENU);
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

//! Implementation of openMapView to see and edit a map
void EditorGUI::openMapView()
{
	char selectedTile = NULL;
	vector<sf::Sprite> mapTiles;
	vector<sf::FloatRect> buttons;
	vector<sf::Text> texts;
	vector<bool> clicked;


	sf::FloatRect groundButton;
	sf::FloatRect wallButton;
	sf::FloatRect playerButton;
	sf::FloatRect doorButton;
	sf::FloatRect treasureButton;
	sf::FloatRect enemyButton;
	sf::FloatRect friendButton;
	sf::FloatRect saveButton;
	sf::FloatRect backButton;

	sf::Text groundText;
	sf::Text wallText;
	sf::Text playerText;
	sf::Text doorText;
	sf::Text treasureText;
	sf::Text enemyText;
	sf::Text friendText;
	sf::Text saveText;
	sf::Text backText;

	sf::Font textFont;
	sf::Color normalColor = sf::Color::White;
	sf::Color hoverColor = sf::Color::Yellow;
	sf::Color clickedColor = sf::Color::Yellow;

	bool groundClicked = false;
	bool wallClicked = false;
	bool playerClicked = false;
	bool doorClicked = false;
	bool treasureClicked = false;
	bool enemyClicked = false;
	bool friendClicked = false;
	bool saveClicked = false;
	bool backClicked = false;

	if (!textFont.loadFromFile("Fonts/OldSchool.ttf"))
	{
		// error...
	}

	groundText.setString("Ground");
	groundText.setFont(textFont);
	groundText.setStyle(sf::Text::Italic);
	groundText.setCharacterSize(15);

	playerText.setString("Player");
	playerText.setFont(textFont);
	playerText.setStyle(sf::Text::Italic);
	playerText.setCharacterSize(15);

	wallText.setString("Wall");
	wallText.setFont(textFont);
	wallText.setStyle(sf::Text::Italic);
	wallText.setCharacterSize(15);

	treasureText.setString("Treasure");
	treasureText.setFont(textFont);
	treasureText.setStyle(sf::Text::Italic);
	treasureText.setCharacterSize(15);

	doorText.setString("Door");
	doorText.setFont(textFont);
	doorText.setStyle(sf::Text::Italic);
	doorText.setCharacterSize(15);

	enemyText.setString("Enemy");
	enemyText.setFont(textFont);
	enemyText.setStyle(sf::Text::Italic);
	enemyText.setCharacterSize(15);

	friendText.setString("Friend");
	friendText.setFont(textFont);
	friendText.setStyle(sf::Text::Italic);
	friendText.setCharacterSize(15);

	saveText.setString("Save");
	saveText.setFont(textFont);
	saveText.setStyle(sf::Text::Italic);
	saveText.setCharacterSize(15);

	backText.setString("Menu");
	backText.setFont(textFont);
	backText.setStyle(sf::Text::Italic);
	backText.setCharacterSize(15);

	groundText.setPosition(sf::Vector2f(50, 700));
	playerText.setPosition(sf::Vector2f(180, 700));
	enemyText.setPosition(sf::Vector2f(300, 700));
	doorText.setPosition(sf::Vector2f(400, 700));
	wallText.setPosition(sf::Vector2f(500, 700));
	treasureText.setPosition(sf::Vector2f(600, 700));
	friendText.setPosition(sf::Vector2f(300, 750));
	saveText.setPosition(sf::Vector2f(670, 300));
	backText.setPosition(sf::Vector2f(670, 400));

	wallButton = wallText.getGlobalBounds();
	groundButton = groundText.getGlobalBounds();
	playerButton = playerText.getGlobalBounds();
	enemyButton = enemyText.getGlobalBounds();
	treasureButton = treasureText.getGlobalBounds();
	friendButton = friendText.getGlobalBounds();
	doorButton = doorText.getGlobalBounds();
	saveButton = saveText.getGlobalBounds();
	backButton = backText.getGlobalBounds();

	buttons.push_back(groundButton);
	buttons.push_back(playerButton);
	buttons.push_back(enemyButton);
	buttons.push_back(doorButton);
	buttons.push_back(wallButton);
	buttons.push_back(treasureButton);
	buttons.push_back(friendButton);

	texts.push_back(groundText);
	texts.push_back(playerText);
	texts.push_back(enemyText);
	texts.push_back(doorText);
	texts.push_back(wallText);
	texts.push_back(treasureText);
	texts.push_back(friendText);

	clicked.push_back(groundClicked);
	clicked.push_back(playerClicked);
	clicked.push_back(enemyClicked);
	clicked.push_back(doorClicked);
	clicked.push_back(wallClicked);
	clicked.push_back(treasureClicked);
	clicked.push_back(friendClicked);


	cout << "Map View " << endl;
	for (int i = 0; i < mapEditor->getMapSizeY(); i++)
	{
		for (int j = 0; j < mapEditor->getMapSizeX(); j++)
		{
			mapTiles.push_back(sf::Sprite());
			if (mapEditor->getTile(j, i) == 'X')
				mapTiles.back().setTexture(textures.getGroundTexture());
			if (mapEditor->getTile(j, i) == 'P')
				mapTiles.back().setTexture(textures.getPlayerTexture());
			if (mapEditor->getTile(j, i) == 'D')
				mapTiles.back().setTexture(textures.getDoorTexture());
			if (mapEditor->getTile(j, i) == 'C')
				mapTiles.back().setTexture(textures.getTreasureTexture());
			if (mapEditor->getTile(j, i) == 'W')
				mapTiles.back().setTexture(textures.getWallTexture());
			if (mapEditor->getTile(j, i) == 'E')
				mapTiles.back().setTexture(textures.getEnemyTexture());
			if (mapEditor->getTile(j, i) == 'F')
				mapTiles.back().setTexture(textures.getFriendlyTexture());
			mapTiles.back().setPosition(j * mapTiles.back().getLocalBounds().width, i * mapTiles.back().getLocalBounds().height);
			//mapTiles.back().setOrigin(mapTiles.back().getLocalBounds().width / 2, mapTiles.back().getLocalBounds().height / 2);
			cout << mapEditor->getTile(j, i) << " ";
		}
		cout << endl;
	}

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
				state.setActive(false);
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

						if (clicked.at(0))
							selectedTile = 'X';
						if (clicked.at(1))
							selectedTile = 'P';
						if (clicked.at(2))
							selectedTile = 'E';
						if (clicked.at(3))
							selectedTile = 'D';
						if (clicked.at(4))
							selectedTile = 'W';
						if (clicked.at(5))
							selectedTile = 'C';
						if (clicked.at(6))
							selectedTile = 'F';

						cout << "Current Tile Selection : " << selectedTile << endl;
					}


				}

				if (saveButton.contains(mousePosition))
				{
					string name;
					string empty;
					cout << "Enter file name for the map" << endl;
					getline(cin, name);
					mapEditor->saveMap(name);
				}

				if (backButton.contains(mousePosition))
				{
					state.setMapEditorState(MapEditorState::MAP_EDITOR_MENU);
					return;
				}


				for (int i = 0; i < mapEditor->getMapSizeY(); i++)
				{
					for (int j = 0; j < mapEditor->getMapSizeX(); j++)
					{
						int index = j + i * mapEditor->getMapSizeX();
						sf::FloatRect tileBounds = mapTiles.at(index).getGlobalBounds();
						if (tileBounds.contains(mousePosition))
						{
							if (selectedTile == 'X')
							{
								mapTiles.at(index).setTexture(textures.getGroundTexture());
								MapObject* ground = NULL;
								mapEditor->setTile(j, i, ground);
							}
							if (selectedTile == 'W')
							{
								mapTiles.at(index).setTexture(textures.getWallTexture());
								MapObject* wall = new MapObject('W');
								mapEditor->setTile(j, i, wall);
							}
							if (selectedTile == 'E')
							{
								mapTiles.at(index).setTexture(textures.getEnemyTexture());
								MapObject* enemy = new Character();
								ItemContainer* backpack = UserDrivenEditor::createBackpack();
								static_cast<Character*>(enemy)->setBackpack(backpack);
								enemy->setObjectType('E');
								mapEditor->setTile(j, i, enemy);
							}
							if (selectedTile == 'F')
							{
								mapTiles.at(index).setTexture(textures.getFriendlyTexture());
								MapObject* newFriend = new Character();
								ItemContainer* backpack = UserDrivenEditor::createBackpack();
								static_cast<Character*>(newFriend)->setBackpack(backpack);
								newFriend->setObjectType('F');
								mapEditor->setTile(j, i, newFriend);
							}
							if (selectedTile == 'C')
							{
								mapTiles.at(index).setTexture(textures.getTreasureTexture());
								MapObject* newChest = UserDrivenEditor::createChest();
								newChest->setObjectType('C');
								mapEditor->setTile(j, i, newChest);
							}
							if (selectedTile == 'D')
							{
								for (int k = 0; k < mapEditor->getMapSizeY(); k++)
									for (int l = 0; l < mapEditor->getMapSizeX(); l++)
									{
										int indexD = l + k * mapEditor->getMapSizeX();
										if (mapEditor->getTile(l, k) == 'D')
											mapTiles.at(indexD).setTexture(textures.getGroundTexture());
									}

								mapTiles.at(index).setTexture(textures.getDoorTexture());
								MapObject* newDoor = new MapObject('D');
								mapEditor->setTile(j, i, newDoor);
							}
							if (selectedTile == 'P')
							{
								for (int k = 0; k < mapEditor->getMapSizeY(); k++)
									for (int l = 0; l < mapEditor->getMapSizeX(); l++)
									{
										int indexD = l + k * mapEditor->getMapSizeX();
										if (mapEditor->getTile(l, k) == 'P')
											mapTiles.at(indexD).setTexture(textures.getGroundTexture());
									}
								mapTiles.at(index).setTexture(textures.getPlayerTexture());
								MapObject* character = new MapObject('P');
								mapEditor->setTile(j, i, character);
							}
						}
					}
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

					if (!saveClicked)
						saveText.setFillColor(normalColor);

					if (!backClicked)
						backText.setFillColor(normalColor);
				}
			}

			if (saveButton.contains(mousePosition) && !saveClicked)
				saveText.setFillColor(hoverColor);

			if (backButton.contains(mousePosition) && !backClicked)
				backText.setFillColor(hoverColor);
		}

		window->clear();
		for (int i = 0; i < mapTiles.size(); i++)
			window->draw(mapTiles.at(i));
		for (int i = 0; i < texts.size(); i++)
			window->draw(texts.at(i));
		window->draw(backText);
		window->draw(saveText);
		window->display();
	}
}

//Campaign Editor views

//! Impelmentation of openCampaignEditorWindow to initalize campaign editor
void EditorGUI::openCampaignEditorWindow()
{
	sf::FloatRect newCampaignButton;
	sf::FloatRect loadCampaignButton;
	sf::FloatRect nextButton;
	sf::FloatRect backButton;
	sf::Text newCampaignText;
	sf::Text loadCampaignText;
	sf::Text nextText;
	sf::Text backText;
	sf::Font textFont;
	sf::Color normalColor = sf::Color::White;
	sf::Color hoverColor = sf::Color::Yellow;
	sf::Color clickedColor = sf::Color::Yellow;
	bool newCampaignClicked = false;
	bool loadCampaignClicked = false;
	bool nextClicked = false;
	bool backClicked = false;
	if (!textFont.loadFromFile("Fonts/OldSchool.ttf"))
	{
		// error...
	}

	newCampaignText.setString("New campaign");
	newCampaignText.setFont(textFont);
	newCampaignText.setStyle(sf::Text::Italic);
	newCampaignText.setCharacterSize(20);

	loadCampaignText.setString("Load campaign");
	loadCampaignText.setFont(textFont);
	loadCampaignText.setStyle(sf::Text::Italic);
	loadCampaignText.setCharacterSize(20);

	nextText.setString("Next");
	nextText.setFont(textFont);
	nextText.setStyle(sf::Text::Italic);
	nextText.setCharacterSize(15);

	backText.setString("Back");
	backText.setFont(textFont);
	backText.setStyle(sf::Text::Italic);
	backText.setCharacterSize(15);


	newCampaignText.setPosition(sf::Vector2f(300, 200));
	loadCampaignText.setPosition(sf::Vector2f(300, 400));
	nextText.setPosition(sf::Vector2f(WINDOW_SCALE - 150, WINDOW_SCALE - 100));
	backText.setPosition(sf::Vector2f(100, WINDOW_SCALE - 100));

	newCampaignButton = newCampaignText.getGlobalBounds();
	loadCampaignButton = loadCampaignText.getGlobalBounds();
	nextButton = nextText.getGlobalBounds();
	backButton = backText.getGlobalBounds();

	window->setKeyRepeatEnabled(false);
	window->setFramerateLimit(60);
	window->setVerticalSyncEnabled(true);
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

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{

				// hit test
				if (newCampaignButton.contains(mousePosition))
				{
					newCampaignText.setFillColor(clickedColor);
					loadCampaignText.setFillColor(normalColor);
					newCampaignClicked = true;
					loadCampaignClicked = false;
				}

				if (loadCampaignButton.contains(mousePosition))
				{
					newCampaignText.setFillColor(normalColor);
					loadCampaignText.setFillColor(clickedColor);
					newCampaignClicked = false;
					loadCampaignClicked = true;
				}

				if (nextButton.contains(mousePosition))
				{
					if (newCampaignClicked)
					{
						campaignEditor->newCampaign();
						campaignEditor->setAvailableMaps();
						state.setCampaignEditorState(CampaignEditorState::MAPLIST_SELECTION);
						return;
					}
					if (loadCampaignClicked)
					{
						campaignEditor->setAvailableCampaigns();
						state.setCampaignEditorState(CampaignEditorState::CAMPAIGN_SELECTION);
						return;
					}
				}

				if (backButton.contains(mousePosition))
				{
					state.setCampaignEditorState(CampaignEditorState::CAMPAIGN_EDITOR_MENU);
					state.setEditorState(EditorState::MENU);
					return;
				}
			}

			if (newCampaignButton.contains(mousePosition) && !newCampaignClicked)
				newCampaignText.setFillColor(hoverColor);
			else
				if (loadCampaignButton.contains(mousePosition) && !loadCampaignClicked)
					loadCampaignText.setFillColor(hoverColor);
				else
					if (nextButton.contains(mousePosition) && !nextClicked)
						nextText.setFillColor(hoverColor);
					else
						if (backButton.contains(mousePosition) && !backClicked)
							backText.setFillColor(hoverColor);
						else
						{
							if (!loadCampaignClicked)
								loadCampaignText.setFillColor(normalColor);

							if (!newCampaignClicked)
								newCampaignText.setFillColor(normalColor);

							if (!nextClicked)
								nextText.setFillColor(normalColor);

							if (!backClicked)
								backText.setFillColor(normalColor);
						}
		}

		window->clear();
		window->draw(newCampaignText);
		window->draw(loadCampaignText);
		window->draw(nextText);
		window->draw(backText);
		window->display();
	}
}

//! Implementation of openMapListSelectionWindow to select the maps to add to a campaign
void EditorGUI::openMapListSelectionWindow()
{
	vector<sf::FloatRect> buttons;
	vector<sf::Text> texts;
	vector<bool> clicked;

	sf::FloatRect addButton;
	sf::Text addText;
	bool addClicked = false;

	sf::FloatRect removeButton;
	sf::Text removeText;
	bool removeClicked = false;

	sf::FloatRect nextButton;
	sf::Text nextText;
	bool nextClicked = false;

	sf::FloatRect saveButton;
	sf::Text saveText;
	bool saveClicked = false;

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

	int currentXPosition = 350;
	int currentYPosition = 100;
	for (int i = 0; i < campaignEditor->getAvailableMapsSize(); i++)
	{
		texts.push_back(sf::Text());
		texts.back().setString(campaignEditor->getAvailableMap(i));
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

	saveText.setPosition(sf::Vector2f(350, currentYPosition + 150));
	saveText.setString("Save");
	saveText.setFont(textFont);
	saveText.setStyle(sf::Text::Italic);
	saveText.setCharacterSize(15);
	saveButton = saveText.getGlobalBounds();

	addText.setPosition(sf::Vector2f(125, currentYPosition + 75));
	addText.setString("Add selected map");
	addText.setFont(textFont);
	addText.setStyle(sf::Text::Italic);
	addText.setCharacterSize(15);
	addButton = addText.getGlobalBounds();

	removeText.setPosition(sf::Vector2f(475, currentYPosition + 75));
	removeText.setString("Remove last map");
	removeText.setFont(textFont);
	removeText.setStyle(sf::Text::Italic);
	removeText.setCharacterSize(15);
	removeButton = removeText.getGlobalBounds();

	nextText.setPosition(sf::Vector2f(WINDOW_SCALE - 275, WINDOW_SCALE - 100));
	nextText.setString("Preview campaign");
	nextText.setFont(textFont);
	nextText.setStyle(sf::Text::Italic);
	nextText.setCharacterSize(15);
	nextButton = nextText.getGlobalBounds();

	backText.setPosition(sf::Vector2f(100, WINDOW_SCALE - 100));
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
				window->close();
				state.setActive(false);
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
					if (campaignEditor->loadMaps())
					{
						state.setCampaignEditorState(CampaignEditorState::CAMPAIGN_VIEW);
						return;
					}

				}

				if (backButton.contains(mousePosition))
				{
					state.setCampaignEditorState(CampaignEditorState::CAMPAIGN_EDITOR_MENU);
					return;
				}

				if (addButton.contains(mousePosition))
				{
					for (int i = 0; i < clicked.size(); i++)
						if (clicked.at(i))
							campaignEditor->addMap(campaignEditor->getAvailableMap(i));
				}

				if (removeButton.contains(mousePosition))
					campaignEditor->removeMap();

				if (saveButton.contains(mousePosition))
				{
					string name;
					cout << "Enter name for the campaign" << endl;
					getline(cin, name);
					campaignEditor->saveCampaign(name);
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

					if (!addClicked)
						addText.setFillColor(normalColor);

					if (!removeClicked)
						removeText.setFillColor(normalColor);

					if (!saveClicked)
						saveText.setFillColor(normalColor);
				}
			}

			if (addButton.contains(mousePosition) && !addClicked)
				addText.setFillColor(hoverColor);

			if (removeButton.contains(mousePosition) && !removeClicked)
				removeText.setFillColor(hoverColor);

			if (nextButton.contains(mousePosition) && !nextClicked)
				nextText.setFillColor(hoverColor);

			if (backButton.contains(mousePosition) && !backClicked)
				backText.setFillColor(hoverColor);

			if (saveButton.contains(mousePosition) && !saveClicked)
				saveText.setFillColor(hoverColor);
		}

		window->clear();

		for (int i = 0; i < texts.size(); i++)
			window->draw(texts.at(i));

		window->draw(backText);
		window->draw(nextText);
		window->draw(saveText);
		window->draw(addText);
		window->draw(removeText);
		window->display();
	}
}

//! Implementation of openLoadCampaignWindow to display and select the available campaigns to load
void EditorGUI::openLoadCampaignWindow()
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
	for (int i = 0; i < campaignEditor->getAvailableCampaignsSize(); i++)
	{
		texts.push_back(sf::Text());
		texts.back().setString(campaignEditor->getAvailableCampaigns(i));
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

	nextText.setPosition(sf::Vector2f(WINDOW_SCALE - 150, WINDOW_SCALE - 100));
	nextText.setString("Next");
	nextText.setFont(textFont);
	nextText.setStyle(sf::Text::Italic);
	nextText.setCharacterSize(15);
	nextButton = nextText.getGlobalBounds();

	backText.setPosition(sf::Vector2f(100, WINDOW_SCALE - 100));
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
				window->close();
				state.setActive(false);
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
							if (campaignEditor->loadCampaign(campaignEditor->getAvailableCampaigns(i)))
							{
								campaignEditor->setAvailableMaps();
								state.setCampaignEditorState(CampaignEditorState::MAPLIST_SELECTION);
								return;
							}

						}
					//Change state
				}

				if (backButton.contains(mousePosition))
				{
					state.setCampaignEditorState(CampaignEditorState::CAMPAIGN_EDITOR_MENU);
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

//! Implementation of openCampaignView to preview the campaign maps
void EditorGUI::openCampaignView()
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

	nextText.setPosition(sf::Vector2f(500, WINDOW_SCALE - 100));
	backText.setPosition(sf::Vector2f(300, WINDOW_SCALE - 100));
	menuText.setPosition(sf::Vector2f(700, 300));

	nextButton = nextText.getGlobalBounds();
	backButton = backText.getGlobalBounds();
	menuButton = menuText.getGlobalBounds();

	for (int i = 0; i < campaignEditor->getCampaignSize(); i++)
	{
		vector<sf::Sprite> mapTiles;
		cout << "Map : " << campaignEditor->getMap(i) << endl;
		for (int j = 0; j < campaignEditor->getCampaignMap(i)->getMapY(); j++)
		{
			for (int k = 0; k < campaignEditor->getCampaignMap(i)->getMapX(); k++)
			{
				mapTiles.push_back(sf::Sprite());
				char currentTile = campaignEditor->getCampaignMap(i)->getTile(k, j);
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

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{

				for (int i = 0; i < campaignEditor->getCampaignMap(currentMap)->getMapY(); i++)
				{
					for (int j = 0; j < campaignEditor->getCampaignMap(currentMap)->getMapX(); j++)
					{
						if (campaignEditor->getCampaignMap(currentMap)->getTile(j, i) == 'C')
						{
							if (maps[currentMap].at(j + i * campaignEditor->getCampaignMap(currentMap)->getMapX()).getGlobalBounds().contains(mousePosition))
								static_cast<ItemContainer*>(campaignEditor->getCampaignMap(currentMap)->getObjectTile(j, i))->displayItems();
						}
						else if (campaignEditor->getCampaignMap(currentMap)->getTile(j, i) == 'E' || campaignEditor->getCampaignMap(currentMap)->getTile(j, i) == 'F') {
							if (maps[currentMap].at(j + i * campaignEditor->getCampaignMap(currentMap)->getMapX()).getGlobalBounds().contains(mousePosition)) {
								static_cast<Character*>(campaignEditor->getCampaignMap(currentMap)->getObjectTile(j, i))->getBackpack()->displayItems();
							}
						}
					}
				}

				// hit test
				if (nextButton.contains(mousePosition))
				{
					if (currentMap < maps.size() - 1)
						currentMap++;
				}

				if (backButton.contains(mousePosition))
				{
					if (currentMap > 0)
						currentMap--;
				}

				if (menuButton.contains(mousePosition))
				{
					state.setCampaignEditorState(CampaignEditorState::CAMPAIGN_EDITOR_MENU);
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

//! Implementation of default destructor
EditorGUI::~EditorGUI()
{
	delete window;
	delete mapEditor;
}
