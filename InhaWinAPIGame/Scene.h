#pragma once

#include "framework.h"

class Scene
{
public:
	virtual ~Scene() {}
	virtual void Update(float dt, const class Game& game) = 0;
	virtual void Draw( HDC hdc ) = 0;
};

