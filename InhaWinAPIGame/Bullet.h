#pragma once

#include "Vec2.h"
#include "PhysicsEntity.h"
#include "ImageCodex.h"
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
		RECT r = rigidBody.GetRECT();
		Surface a;
		a.DrawImageChroma( hdc, pImage, { r.left,r.top }, { r.right,r.bottom }, { 0,0 }, { 20,20 } );
	}
private:
	Gdiplus::Image* pImage = ImageCodex::Retrieve( L"Images/awsom.bmp" );
	PhysicsEntity rigidBody;
};