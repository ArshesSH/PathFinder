#include "Brick.h"

Brick::Brick( const Vec2<float>& pos, const Vec2<float>& vel, float width, float height, int id )
	:
	rigidBody( PhysicsEntity::Type::Rect, pos, id, width, height, vel, 0.0f, 0.0f, 0 )
{
}

void Brick::Update( float dt, const Scene& scene )
{
	switch ( health )
	{
	case 0:
		{
			shouldDestroy = true;
		}
		break;
	case 1:
		{
			color = Gdiplus::Color( 125, 255, 10, 10 );
		}
		break;
	case 2:
		{
			color = Gdiplus::Color( 255, 10, 144, 10 );
		}
		break;
	}
}

void Brick::Draw( HDC hdc )
{
	const Vec2<float> topLeft = rigidBody.GetLeftTop();
	const float width = rigidBody.GetWidth();
	const float height = rigidBody.GetHeight();
	surface.DrawFillRect( hdc, color, topLeft, width, height );
}
