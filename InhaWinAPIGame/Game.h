#pragma once

#include "framework.h"

#include "FrameTimer.h"
#include "SceneStage.h"
#include "DrawManager.h"
#include "FileManager.h"
#include <map>
class Game
{
public:
	enum class SceneType
	{
		SceneStart,
		SceneMainGame,
		SceneStage,
		SceneResult
	};
public:
	Game();
	void ComposeFrame( HDC hdc );
	void UpdateModel();

	void RefreshScreen();

	unsigned long long GetCurScore();
	std::wstring GetCurUserId();
	void AddScore();
	bool IsInitialGame() const;
	bool IsGameFinished() const;
	void StartMainGame();
	void SetUserID( const std::wstring& id );
	std::wstring GetUserID() const;
	auto GetScoreMap()
	{
		return scoreMap;
	}
	void GetScoreMapFromData();
	void SaveDataFromScoreMap();
	bool IsScreenChanged() const;

public:
	RECT screenRect;
private:
	static constexpr wchar_t dataDir[] = L"Data/Score.txt";

	RECT oldScreenSize = screenRect;
	FileManager fileManager;
	FrameTimer ft;
	SceneStage stage;
	DrawManager drawManager;
	Surface surf;

	bool isScreenChanged = true;
	float time = 0.0f;
	SceneType sceneType = SceneType::SceneStage;

	std::wstring userId;
	unsigned long long playerScore = 0;
	bool isFinishedResult = false;

	std::map<unsigned long long, std::vector<std::wstring>> scoreMap;
};