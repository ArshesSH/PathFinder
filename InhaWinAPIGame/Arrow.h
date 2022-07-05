#pragma once

#include "Actor.h"

#include "PhysicsEntity.h"

class Arrow : public Actor
{
public:
	Arrow( const Vec2<float>& pos, const Vec2<float>& vel, float width, float height, int id );

	~Arrow() {}
	Arrow( const Arrow& ) = default;
	Arrow( Arrow&& ) = default;
	Arrow& operator=( const Arrow& ) = default;
	Arrow& operator=( Arrow&& ) noexcept = default;

	void Update( float dt, class Scene& scene ) override;
	void Draw( HDC hdc ) override;
	bool isOverlapWith( RECT other );

	void AddPos( const Vec2<float> addPos );

private:
	bool CheckFloor( RECT screenRect );

private:
	static constexpr wchar_t imagename[] = L"Images/Rocket.png";
	std::shared_ptr<Gdiplus::Image> pImage;
	PhysicsEntity rigidBody;
	Vec2<int> imageEnd = { pImage->GetWidth(), pImage->GetHeight() };
};