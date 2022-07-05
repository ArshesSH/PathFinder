#include "Arrow.h"

#include "Scene.h"

Arrow::Arrow( const std::wstring& imagename, const Vec2<float>& pos, const Vec2<float>& vel, float width, float height, int id )
	:
	pImage( ImageCodex::Retrieve( imagename ) ),
	rigidBody( PhysicsEntity::Type::Rect, pos, id, width, height, vel, 0.0f, 0.0f, 0 )
{}

void Arrow::Update( float dt, Scene& scene )
{
	rigidBody.Update( dt );
	RECT r = scene.GetSceneRECT();
	if ( CheckFloor( r ) )
	{
		shouldDestroy = true;
		scene.FinishScene();
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

	return !(curPos.y + height <= screenRect.bottom);
}

bool Arrow::isOverlapWith( RECT other )
{
	const Vec2<float> curPos = rigidBody.GetCenter();
	const float width = rigidBody.GetWidth() * 0.5f;
	const float height = rigidBody.GetHeight() * 0.5f;

	return curPos.x + width > other.left && curPos.x - width < other.right
		&& curPos.y + height > other.top && curPos.y - height < other.bottom;
}

void Arrow::AddPos( const Vec2<float> addPos )
{
	rigidBody.SetCenter( rigidBody.GetCenter() + addPos );
}
