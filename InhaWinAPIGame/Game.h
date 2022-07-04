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

private:

public:
	RECT screenRect;
private:
	RECT oldScreenSize = screenRect;
	bool isScreenChanged = true;
	FrameTimer ft;
	SceneMainGame mainGame;
	DrawManager drawManager;

	Vec2<int> mousePos;
	Vec2<float> screenChangeAmount = {0.0f,0.0f};
	float time = 0.0f;
	SceneType sceneType = SceneType::SceneStart;
};