#include "Brick.h"

Brick::Brick( const Vec2<float>& pos, float width, float height, int id )
	:
	initPos(pos),
	rigidBody( PhysicsEntity::Type::Rect, pos, id, width, height, {0.0f,0.0f}, 0.0f, 0.0f, 0 )
{
}

void Brick::Update( float dt, Scene& scene )
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
			color = Gdiplus::Color( 200, 255, 10, 10 );
		}
		break;
	case 2:
		{
			color = Gdiplus::Color( 255, 10, 230, 10 );
		}
		break;
	}
}

void Brick::Draw( HDC hdc )
{
	const Vec2<float> topLeft = rigidBody.GetLeftTop();
	const float width = rigidBody.GetWidth();
	const float height = rigidBody.GetHeight();
	Surface::DrawFillRect( hdc, color, topLeft, width, height );
}
