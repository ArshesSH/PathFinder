#pragma once

#include "framework.h"

#include "FrameTimer.h"
#include "SceneMainGame.h"

//#include <vector>
//#include "DrawManager.h"
//#include "Arrow.h"

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

	//std::vector<Arrow> arrows;

	float time = 0.0f;
};