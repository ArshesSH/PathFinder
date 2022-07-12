#pragma once

#include "Actor.h"

#include <string>
#include "ImageCodex.h"
//#include "PhysicsEntity.h"
#include "Rect.h"

template<typename T>
class DynamicActor : public Actor
{
public:
	DynamicActor( const std::wstring imageName, const Vec2<float>& pos, const Vec2<float>& vel, float width, float height, int id )
		:
		pImage( ImageCodex::Retrieve( imageName ) ),
		collisionRect(pos, width, height)
	{}
	virtual ~DynamicActor() {}
	DynamicActor( const DynamicActor& ) = default;
	DynamicActor( DynamicActor&& ) = default;
	DynamicActor& operator=( const DynamicActor& ) = default;
	DynamicActor& operator=( DynamicActor&& ) noexcept = default;

	virtual void Update( float dt, class Scene& scene ) = 0;
	virtual void Draw( Gdiplus::Graphics& gfx ) = 0;
	virtual bool isOverlapWith( RECT other )
	{
		const Vec2<float> curPos = rigidBody.GetCenter();
		const float width = rigidBody.GetWidth() * 0.5f;
		const float height = rigidBody.GetHeight() * 0.5f;

		return curPos.x + width > other.left && curPos.x - width < other.right
			&& curPos.y + height > other.top && curPos.y - height < other.bottom;
	}
	virtual void AddPos( const Vec2<float> addPos )
	{
		//rigidBody.SetCenter( rigidBody.GetCenter() + addPos );
	}

protected:
	std::shared_ptr<Gdiplus::Image> pImage;
	Vec2<int> imageEnd = { pImage->GetWidth(), pImage->GetHeight() };
	Rect<T> collisionRect;
	Vec2<T> vel;

	//PhysicsEntity rigidBody;
};