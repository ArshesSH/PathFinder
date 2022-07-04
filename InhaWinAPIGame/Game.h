#pragma once

#include "framework.h"

#include "FrameTimer.h"
#include "SceneMainGame.h"
#include "DrawManager.h"


class Game
{
public:
	Game();
	void ComposeFrame( HDC hdc );
	void UpdateModel();

	Vec2<int> GetMousePos();
	void SetMousePos( const Vec2<int>& pos );

private:
	void IsScreenSizeChanged()
	{
		
	}

public:
	RECT screenRect;
private:
	RECT oldScreenSize = screenRect;
	bool isScreenChanged = true;
	FrameTimer ft;
	SceneMainGame mainGame;
	DrawManager drawManager;

	Vec2<int> mousePos;

	float time = 0.0f;
};