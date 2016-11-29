//! @file 
//! @brief Header file for PlayGUI class
#pragma once
#include "Play.h"
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "GameState.h"
#include "Observer.h"
class Launch;

class PlayGUI : public Observer
{
private:
	Play* play;
	//!GUI textures
	Resources textures;
	Launch* launch;
	sf::RenderWindow *window;
	GameState state;
	Map* subject;
	vector<vector<sf::Sprite>> maps; // for the observer...
	int currentMap = 0;
public:
	PlayGUI();
	PlayGUI(sf::RenderWindow &window);
	void openLoadCampaignWindow();
	void openLoadCharacterWindow();
	void openMapView();
	void Update();
	void Display();
	void Start();
	void UpdateGUI();
	~PlayGUI();
};

