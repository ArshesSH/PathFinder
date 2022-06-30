#pragma once

#include "framework.h"
#include "SpriteManager.h"

class Game
{
public:
	Game();

	void ComposeFrame( HDC hdc );
	void UpdateModel();

public:


private:
	HDC hdc;
	SpriteManager spriteManager;
};