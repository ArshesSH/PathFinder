#include "Arrow.h"

#include "Scene.h"

Arrow::Arrow( const std::wstring& imagename, const Vec2<float>& pos, const Vec2<float>& vel, float width, float height, int id )
	:
	Actor( imagename ),
	rigidBody( PhysicsEntity::Type::Rect, pos, id, width, height, vel, 0.0f, 0.0f, 0 )
{}

void Arrow::Update( float dt, const Scene& scene )
{
	rigidBody.Update( dt );
	RECT r = scene.GetSceneRECT();
	if ( CheckFloor( r ) )
	{
		shouldDestroy = true;
	}
}

void Arrow::Draw( HDC hdc )
{
	surface.DrawImageChroma( hdc, pImage.get(), rigidBody.GetLeftTop(), rigidBody.GetRightBottom(), { 0,0 }, imageEnd );
}

inline bool Arrow::CheckFloor( RECT screenRect )
{
	const Vec2<float> curPos = rigidBody.GetCenter();
	const float width = rigidBody.GetWidth() * 0.5f;
	const float height = rigidBody.GetHeight() * 0.5f;

	return !(curPos.x - width >= screenRect.left && curPos.x + width <= screenRect.right &&
		 curPos.y + height <= screenRect.bottom);
}

bool Arrow::isOverlapWith( RECT other )
{
	const Vec2<float> curPos = rigidBody.GetCenter();
	const float width = rigidBody.GetWidth() * 0.5f;
	const float height = rigidBody.GetHeight() * 0.5f;

	return curPos.x + width > other.left && curPos.x - width < other.right
		&& curPos.y + height > other.top && curPos.y - height < other.bottom;
}
