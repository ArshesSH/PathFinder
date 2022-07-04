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

public:
	RECT screenRect;
private:
	FrameTimer ft;
	SceneMainGame mainGame;
	DrawManager drawManager;

	float time = 0.0f;
};