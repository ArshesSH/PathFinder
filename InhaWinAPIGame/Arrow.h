#pragma once

#include "Actor.h"

#include "PhysicsEntity.h"

class Arrow : public Actor
{
public:
	Arrow( const std::wstring& imagename, const Vec2<float>& pos, const Vec2<float>& vel, float width, float height, int id );

	~Arrow() {}
	Arrow( const Arrow& ) = default;
	Arrow( Arrow&& ) = default;
	Arrow& operator=( const Arrow& ) = default;
	Arrow& operator=( Arrow&& ) noexcept = default;

	void Update( float dt, const class Game& game ) override;
	void Draw( HDC hdc ) override;

private:
	bool CheckFloor( RECT screenRect );

private:
	PhysicsEntity rigidBody;
	Vec2<int> imageEnd = { pImage->GetWidth(), pImage->GetHeight() };
};