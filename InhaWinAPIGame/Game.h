#pragma once

#include "framework.h"

#include "FrameTimer.h"
#include "DrawManager.h"

#include "AStarScene.h"
// Test Things

class Game
{
public:
	enum class SceneType
	{
		SceneStart,
		SceneStage,
		SceneTest,
		SceneResult
	};
public:
	Game();
	void ComposeFrame( HDC hdc );
	void UpdateModel();

	void RefreshScreen();

	Vec2<int> GetMousePos();
	void SetMousePos( const Vec2<int>& pos );

	bool IsInitialGame() const;
	bool IsGameFinished() const;
	bool IsScreenChanged() const;

public:
	RECT screenRect;
private:
	RECT oldScreenSize = screenRect;
	FrameTimer ft;
	DrawManager drawManager;
	AStarScene sceneAStar;

	bool isScreenChanged = true;
	float time = 0.0f;
	SceneType sceneType = SceneType::SceneStage;

	bool isFinishedResult = false;
	Vec2<int> mousePos;
};