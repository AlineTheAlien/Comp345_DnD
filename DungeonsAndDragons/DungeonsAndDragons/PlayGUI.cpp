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
				openLoadCharacterWindow();
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
					for (int j = 0; j < buttons.size(); j++)
						clicked.at(j) = false;
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
					else
					if (!nextClicked)
						nextText.setFillColor(normalColor);
					else
					if (!backClicked)
						backText.setFillColor(normalColor);
					else
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
								//campaignEditor->setState(CampaignEditorState::MAPLIST_SELECTION);
								return;
							}

						}
					//Change state
				}

				if (backButton.contains(mousePosition))
				{
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

PlayGUI::~PlayGUI()
{
}
