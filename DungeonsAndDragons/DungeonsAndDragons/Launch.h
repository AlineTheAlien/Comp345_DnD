//! @file 
//! @brief Cpp file for Launch class
#pragma once
#include "EditorGUI.h"
#include "PlayGUI.h"
#include "GameState.h"
class Launch
{
private:
	EditorGUI* editorGUI;
	PlayGUI* playGUI;
	sf::RenderWindow* window;
	GameState state;
public:

	Launch();
	void openMenuView();
	void Update();
	void Display();
	void Start();
	~Launch();
};
