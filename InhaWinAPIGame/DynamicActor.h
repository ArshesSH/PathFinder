#pragma once

#include "Actor.h"

#include <string>
#include "ImageCodex.h"
#include "PhysicsEntity.h"

class DynamicActor : public Actor
{
public:
	DynamicActor( const std::wstring imageName, const Vec2<float>& pos, const Vec2<float>& vel, float width, float height, int id )
		:
		pImage( ImageCodex::Retrieve( imageName ) ),
		rigidBody( PhysicsEntity::Type::Rect, pos, id, width, height, vel, 0.0f, 0.0f, 0 )
	{}
	virtual ~DynamicActor() {}
	DynamicActor( const DynamicActor& ) = default;
	DynamicActor( DynamicActor&& ) = default;
	DynamicActor& operator=( const DynamicActor& ) = default;
	DynamicActor& operator=( DynamicActor&& ) noexcept = default;

	virtual void Update( float dt, class Scene& scene ) = 0;
	virtual void Draw( HDC hdc ) = 0;
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
		rigidBody.SetCenter( rigidBody.GetCenter() + addPos );
	}


protected:
	std::shared_ptr<Gdiplus::Image> pImage;
	Vec2<int> imageEnd = { pImage->GetWidth(), pImage->GetHeight() };
	PhysicsEntity rigidBody;
};