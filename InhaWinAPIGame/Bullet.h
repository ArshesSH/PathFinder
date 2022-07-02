#pragma once

#include "Vec2.h"

class Bullet
{
public:
	void Update(float dt);
	void Draw();
private:
	Vec2<float> pos;
};