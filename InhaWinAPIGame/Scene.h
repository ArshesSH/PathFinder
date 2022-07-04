#pragma once

#include "framework.h"

class Scene
{
public:
	virtual ~Scene() {}
	virtual void Update(float dt, class Game& game ) = 0;
	virtual void Draw( HDC hdc ) = 0;
	virtual RECT GetSceneRECT() const = 0;
	bool isSceneFinshed() const
	{
		return isSceneFinish;
	}
	void FinishScene()
	{
		isSceneFinish = true;
	}
protected:
	bool isSceneFinish = false;
};

