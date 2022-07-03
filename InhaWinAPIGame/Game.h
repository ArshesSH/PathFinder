#pragma once

#include "framework.h"

#include <vector>
#include "Codex.h"
#include "Surface.h"
#include "TestGDI.h"

class Game
{
public:
	Game();

	void ComposeFrame( HDC hdc );
	void UpdateModel();

public:
	RECT screenRect;
private:
	TestGDI test;

	// scene
};