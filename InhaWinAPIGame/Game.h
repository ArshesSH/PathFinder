#pragma once

#include "framework.h"

#include "Bullet.h"
#include "FrameTimer.h"
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
	Bullet testBullet;
	DrawManager dm;
};