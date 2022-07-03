#pragma once

#include "Vec2.h"
#include "PhysicsEntity.h"
#include <ObjIdl.h>
#include <gdiplus.h>
#include "Codex.h"
#include "Surface.h"

class Bullet
{
public:
	Bullet( const Vec2<float>& pos, const Vec2<float>& vel, int size, int id )
		:
		rigidBody(PhysicsEntity::Type::Circle, pos, id, size, vel, 0.0f, 0.0f, 0)
	{
	}
	void Update( float dt )
	{
		rigidBody.Update( dt );
	}
	void Draw(HDC hdc)
	{
		
	}
private:
	const Gdiplus::Image* sprite = Codex<Gdiplus::Image>::Retrieve(L"Images/awsom.bmp");
	PhysicsEntity rigidBody;
};