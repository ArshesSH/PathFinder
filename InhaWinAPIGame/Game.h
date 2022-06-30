#pragma once

#include "framework.h"

class Game
{
public:
	void ComposeFrame( HDC hdc );
	void UpdateModel();
private:

private:
	HDC hdc;
};

