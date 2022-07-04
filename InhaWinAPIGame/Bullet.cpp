#include "Bullet.h"

#include "Scene.h"

Bullet::Bullet( const std::wstring& imagename, const Vec2<float>& pos, const Vec2<float>& vel, float width, float height, int id )
	:
	pImage( ImageCodex::Retrieve( imagename ) ),
	rigidBody( PhysicsEntity::Type::Rect, pos, id, width, height, vel, 0.0f, 0.0f, 0 )
{
}

void Bullet::Update( float dt, const Scene& scene )
{
	rigidBody.Update( dt );

	const RECT r = scene.GetSceneRECT();
	const Vec2<float> topLeft = { (float)r.left, (float)r.top };
	const Vec2<float> bottomRight = { (float)r.right, (float)r.bottom };
	if ( CheckBorder(scene.GetSceneRECT()) )
	{
		shouldDestroy = true;
	}
}

void Bullet::Draw( HDC hdc )
{
	surface.DrawImageNonChroma( hdc, pImage.get(), rigidBody.GetLeftTop(), rigidBody.GetRightBottom(), { 0,0 }, imageEnd );
}

RECT Bullet::GetRECT() const
{
	return rigidBody.GetRECT();
}

bool Bullet::CheckBorder( RECT screenRect ) const
{
	const Vec2<float> curPos = rigidBody.GetCenter();
	const float width = rigidBody.GetWidth() * 0.5f;
	const float height = rigidBody.GetHeight() * 0.5f;

	return !(curPos.x - width >= screenRect.left && curPos.x + width <= screenRect.right &&
		 curPos.y - height >= screenRect.top &&curPos.y + height <= screenRect.bottom);
}
