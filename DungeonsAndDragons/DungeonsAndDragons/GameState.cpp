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

void GameState::setMapEditorState(MapEditorState state)
{
	mapEditorState = state;
}

void GameState::setCampaignEditorState(CampaignEditorState state)
{
	campaignEditorState = state;
}

void GameState::setEditorState(EditorState state)
{
	editorState = state;
}

void GameState::setLaunchState(LaunchState state)
{
	launchState = state;
}

void GameState::setActive(bool active)
{
	gameIsActive = active;
}

void GameState::setPlayState(PlayState state)
{
	playState = state;
}

MapEditorState GameState::getMapEditorState()
{
	return mapEditorState;
}

CampaignEditorState GameState::getCampaignEditorState()
{
	return campaignEditorState;
}

EditorState GameState::getEditorState()
{
	return editorState;
}

LaunchState GameState::getLaunchState()
{
	return launchState;
}

PlayState GameState::getPlayState()
{
	return playState;
}

bool GameState::isActive()
{
	return gameIsActive;
}

GameState::~GameState()
{
}
