//! @file 
//! @brief Header file for PlayGUI class
#pragma once
#include "Play.h"
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "GameState.h"
class Launch;

class PlayGUI
{
private:
	Play* play;
	//!GUI textures
	Resources textures;
	Launch* launch;
	sf::RenderWindow *window;
	GameState state;
	bool combatOn;
public:
	PlayGUI();
	PlayGUI(sf::RenderWindow &window);
	void openLoadCampaignWindow();
	void openLoadCharacterWindow();
	void openMapView();
	void Update();
	void Display();
	void Start();
	~PlayGUI();
};

