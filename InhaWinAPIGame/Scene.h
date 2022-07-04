#pragma once

#include "framework.h"

class Scene
{
public:
	Scene() {}
	virtual ~Scene() {}
	virtual void Update(float dt, RECT screenRect) = 0;
	virtual void Draw( HDC hdc ) = 0;
};

