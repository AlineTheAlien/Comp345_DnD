//! @file 
//! @brief Implementation file for the Launch class  
//!
#include "stdafx.h"
#include "Launch.h"


Launch::Launch()
{
	window = new sf::RenderWindow(sf::VideoMode(GameState::WINDOW_SCALE,GameState::WINDOW_SCALE), "DUNGEONS AND DRAGONS", sf::Style::Titlebar | sf::Style::Close);
	editorGUI = new EditorGUI(*window);
	playGUI = new PlayGUI(*window);
}


void Launch::Start()
{
	state.setLaunchState(LaunchState::MENU);
	state.setActive(true);
	Update();
}

//! Implementation of Update to change the state of the editor
void Launch::Update()
{
	while (state.isActive())
	{
		string currentState;

		if (state.getLaunchState() == LaunchState::MENU)
			currentState = "MENU";

		if (state.getLaunchState() == LaunchState::EDITOR)
			currentState = "EDITOR";

		if (state.getLaunchState() == LaunchState::PLAY)
			currentState = "PLAY";

		cout << "The launcher has changed state to : " << currentState << endl;

		Display();
	}
}

//! Implementation of Display to change the view according to the current state
void Launch::Display()
{
	if (state.getLaunchState() == LaunchState::MENU)
		openMenuView();
	else
		if (state.getLaunchState() == LaunchState::PLAY)
			playGUI->Start();
		else
			if (state.getLaunchState() == LaunchState::EDITOR)
				editorGUI->Start();
}


void Launch::openMenuView()
{
	sf::FloatRect editorButton;
	sf::FloatRect playButton;
	sf::FloatRect nextButton;

	sf::Text editorText;
	sf::Text playText;
	sf::Text nextText;

	sf::Font textFont;
	sf::Color normalColor = sf::Color::White;
	sf::Color hoverColor = sf::Color::Yellow;
	sf::Color clickedColor = sf::Color::Yellow;
	bool editorClicked = false;
	bool playClicked = false;
	bool nextClicked = false;

	if (!textFont.loadFromFile("Fonts/OldSchool.ttf"))
	{
		// error...
	}


	editorText.setString("Editor");
	editorText.setFont(textFont);
	editorText.setStyle(sf::Text::Italic);
	editorText.setCharacterSize(20);

	playText.setString("Play");
	playText.setFont(textFont);
	playText.setStyle(sf::Text::Italic);
	playText.setCharacterSize(20);

	nextText.setString("Next");
	nextText.setFont(textFont);
	nextText.setStyle(sf::Text::Italic);
	nextText.setCharacterSize(15);

	editorText.setPosition(sf::Vector2f(350, 400));
	playText.setPosition(sf::Vector2f(350, 200));
	nextText.setPosition(sf::Vector2f(GameState::WINDOW_SCALE - 150, GameState::WINDOW_SCALE - 100));

	editorButton = editorText.getGlobalBounds();
	playButton = playText.getGlobalBounds();
	nextButton = nextText.getGlobalBounds();


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
				if (editorButton.contains(mousePosition))
				{
					editorText.setFillColor(clickedColor);
					playText.setFillColor(normalColor);
					editorClicked = true;
					playClicked = false;
				}

				if (playButton.contains(mousePosition))
				{
					editorText.setFillColor(normalColor);
					playText.setFillColor(clickedColor);
					editorClicked = false;
					playClicked = true;
				}

				if (nextButton.contains(mousePosition))
				{
					if (editorClicked)
					{
						state.setLaunchState(LaunchState::EDITOR);
						return;
					}
					if (playClicked)
					{
						state.setLaunchState(LaunchState::PLAY);
						return;
					}
				}
			}

			if (editorButton.contains(mousePosition) && !editorClicked)
				editorText.setFillColor(hoverColor);
			else
				if (playButton.contains(mousePosition) && !playClicked)
					playText.setFillColor(hoverColor);
				else
					if (nextButton.contains(mousePosition) && !nextClicked)
						nextText.setFillColor(hoverColor);
					else
					{
						if (!playClicked)
							playText.setFillColor(normalColor);

						if (!editorClicked)
							editorText.setFillColor(normalColor);

						if (!nextClicked)
							nextText.setFillColor(normalColor);
					}
		}

		window->clear();
		window->draw(editorText);
		window->draw(playText);
		window->draw(nextText);
		window->display();
	}
}

Launch::~Launch()
{
}
