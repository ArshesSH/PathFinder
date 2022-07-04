#pragma once

#include <string>
#include "Vec2.h"
#include "PhysicsEntity.h"
#include "ImageCodex.h"
#include "Surface.h"

class Actor
{
public:
	Actor( const std::wstring& imagename, const Vec2<float>& pos, const Vec2<float>& vel, float width, float height,
		PhysicsEntity::Type collisionType, int id )
		:
		pImage( ImageCodex::Retrieve( imagename ) ),
		rigidBody( collisionType, pos, id, width, height, vel, 0.0f, 0.0f, 0 )
	{
	}
	virtual ~Actor() {}
	virtual void Update( float dt, RECT screenRect ) = 0;
	virtual void Draw( HDC hdc ) = 0;
protected:
	Gdiplus::Image* pImage;
	PhysicsEntity rigidBody;
	Surface surface;
	bool shouldDestroy = false;
};