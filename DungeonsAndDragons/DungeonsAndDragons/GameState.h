#pragma once


enum class MapEditorState {
	MAP_EDITOR_MENU, SIZE_SELECTION, MAP_SELECTION, MAP_VIEW
};

enum class CampaignEditorState {
	CAMPAIGN_EDITOR_MENU, CAMPAIGN_SELECTION, MAPLIST_SELECTION, CAMPAIGN_VIEW
};

enum class EditorState
{
	MENU, MAP_EDITOR, CAMPAIGN_EDITOR
};

enum class LaunchState
{
	MENU, PLAY, EDITOR
};

enum class PlayState
{
	CHARACTER_SELECTION, CAMPAIGN_SELECTION, MAP_VIEW
};

class GameState
{
private:
	static MapEditorState mapEditorState;
	static CampaignEditorState campaignEditorState;
	static EditorState editorState;
	static LaunchState launchState;
	static PlayState playState;
	static bool gameIsActive;

public:
	const static int WINDOW_SCALE = 800;
	GameState();

	void setMapEditorState(MapEditorState state);
	void setCampaignEditorState(CampaignEditorState state);
	void setEditorState(EditorState state);
	void setLaunchState(LaunchState state);
	void setActive(bool active);
	void setPlayState(PlayState state);
	
	MapEditorState getMapEditorState();
	CampaignEditorState getCampaignEditorState();
	EditorState getEditorState();
	LaunchState getLaunchState();
	PlayState getPlayState();
	bool isActive();

	~GameState();
};

