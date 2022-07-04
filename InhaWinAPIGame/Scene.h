#pragma once

#include "framework.h"

class Scene
{
public:
	virtual ~Scene() {}
	virtual void Update(float dt, RECT screenRect) = 0;
	virtual void Draw( HDC hdc ) = 0;
	virtual RECT GetSceneRECT() const = 0;
};

