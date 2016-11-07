//! @file 
//! @brief Header file for the EditorGUI class  
//! The following class implements the GUI of the Editor to allow user to use the MapEditor and CampaignEditor
//! It allows a user to modify, and create campaigns and maps
//! The user can also load previously created maps and campaigns and save new ones
//! The library used for the GUI is SFML 2.4. It was used because of its efficiency and simplicity
//! The GUI is presented in a window with multiple views. According to the state change, different
//! functions are used to display different views.

#pragma once
#include "Resources.h"
#include "Map.h"
#include "MapEditor.h"
#include "CampaignEditor.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameState.h"

using namespace std;

class EditorGUI
{
private:
	MapEditor *mapEditor;
	CampaignEditor *campaignEditor;
	sf::RenderWindow *window;
	Resources textures;
	GameState state;

public:
	const static int WINDOW_SCALE = 800;
	EditorGUI();
	EditorGUI(sf::RenderWindow &window);
	void openEditorWindow();

	//Map Editor views
	void openMapEditorWindow();
	void openNewMapWindow();
	void openLoadMapWindow();
	void openMapView();
	//Campaign Editor views
	void openCampaignEditorWindow();
	void openMapListSelectionWindow();
	void openLoadCampaignWindow();
	void openCampaignView();
	//
	void Start();
	void Update();
	void Display();
	~EditorGUI();
};

