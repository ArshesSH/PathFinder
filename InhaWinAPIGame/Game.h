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
	enum class MouseInputType
	{
		NoInput,
		LeftClicked,
		RightClicked,
		MiddleClicked
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

	void SetLeftClick()
	{
		mouseInputType = MouseInputType::LeftClicked;
	}
	void SetRightClick()
	{
		mouseInputType = MouseInputType::RightClicked;
	}
	void SetMiddleClick()
	{
		mouseInputType = MouseInputType::MiddleClicked;
	}
	void SetNoClick()
	{
		mouseInputType = MouseInputType::NoInput;
	}

	bool IsLeftClicked()
	{
		return mouseInputType == MouseInputType::LeftClicked;
	}
	bool IsRightClicked()
	{
		return mouseInputType == MouseInputType::RightClicked;
	}
	bool IsMiddleClicked()
	{
		return mouseInputType == MouseInputType::MiddleClicked;
	}

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
	MouseInputType mouseInputType = MouseInputType::NoInput;
};