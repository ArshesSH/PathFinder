#pragma once

#include "framework.h"

#include "FrameTimer.h"
#include "SceneMainGame.h"
#include "DrawManager.h"


class Game
{
public:
	enum class SceneType
	{
		SceneStart,
		SceneMainGame,
		SceneResult
	};
public:
	Game();
	void ComposeFrame( HDC hdc );
	void UpdateModel();

	Vec2<int> GetMousePos();
	void SetMousePos( const Vec2<int>& pos );
	Vec2<float> GetScreenChangeAmount() const;
	void AddScore()
	{
		playerScore += 100;
	}
	bool IsInitialGame() const
	{
		return sceneType == SceneType::SceneStart;
	}
	bool IsGameFinished() const
	{
		return sceneType == SceneType::SceneResult;
	}
	
	void StartMainGame()
	{
		sceneType = SceneType::SceneMainGame;
	}
	void SetUserID( const std::wstring& id )
	{
		userId = id;
	}
	std::wstring GetUserID() const
	{
		return userId;
	}

private:

public:
	RECT screenRect;
private:
	RECT oldScreenSize = screenRect;
	bool isScreenChanged = true;
	FrameTimer ft;
	SceneMainGame mainGame;
	DrawManager drawManager;
	Surface surf;

	Vec2<int> mousePos;
	Vec2<float> screenChangeAmount = {0.0f,0.0f};
	float time = 0.0f;
	SceneType sceneType = SceneType::SceneStart;
	std::wstring userId;
	unsigned long long playerScore = 0;
	bool isFinishedResult = false;
};