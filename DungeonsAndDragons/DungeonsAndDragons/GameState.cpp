//! @file 
//! @brief Header file for GameState class

#include "stdafx.h"
#include "GameState.h"


LaunchState GameState::launchState = LaunchState::MENU;
CampaignEditorState GameState::campaignEditorState = CampaignEditorState::CAMPAIGN_EDITOR_MENU;
MapEditorState GameState::mapEditorState = MapEditorState::MAP_EDITOR_MENU;
EditorState GameState::editorState = EditorState::MENU;
PlayState GameState::playState = PlayState::CAMPAIGN_SELECTION;
bool GameState::gameIsActive = false;

GameState::GameState()
{
}


//! Implementation of setMapEditorState
//! @param state : a mapeditorstate object
void GameState::setMapEditorState(MapEditorState state)
{
	mapEditorState = state;
}

//! Implementation of setCampaignEditorState
//! @param state : a CampaignEditorState object
void GameState::setCampaignEditorState(CampaignEditorState state)
{
	campaignEditorState = state;
}

//! Implementation of setEditorSTate
//! @param state : a setEditorState object
void GameState::setEditorState(EditorState state)
{
	editorState = state;
}

//! Implementation of setLaunchState
//! @param state : a LaunchState object
void GameState::setLaunchState(LaunchState state)
{
	launchState = state;
}

//! Implementation of setActive
//! @param active : a boolean value presenting the active state of the game
void GameState::setActive(bool active)
{
	gameIsActive = active;
}

//! Implementation of setPlayState
//! @param state : a PlayState object
void GameState::setPlayState(PlayState state)
{
	playState = state;
}

//! Implementation of getMapEditorState
//! @return : MapEditorState object
MapEditorState GameState::getMapEditorState()
{
	return mapEditorState;
}

//! Implementation of getCampaignEditorState
//! @return : CampaignEditorState object
CampaignEditorState GameState::getCampaignEditorState()
{
	return campaignEditorState;
}

//! Implementation of getEditorState
//! @return : EditorState object
EditorState GameState::getEditorState()
{
	return editorState;
}

//! Implementation of getLauchState
//! @return : LaunchState object
LaunchState GameState::getLaunchState()
{
	return launchState;
}

//! Implementation of getPlayState
//! @return : PlayState object
PlayState GameState::getPlayState()
{
	return playState;
}

//! Implementation of isActive
//! @return : a boolean value presenting the active state of the game
bool GameState::isActive()
{
	return gameIsActive;
}

GameState::~GameState()
{
}
