#pragma once

#include "Actor.h"
#include "PhysicsEntity.h"

class Brick : public Actor
{
public:
	Brick( const Vec2<float>& pos, const Vec2<float>& vel, float width, float height, int id );

	~Brick() {}
	Brick( const Brick& ) = default;
	Brick( Brick&& ) = default;
	Brick& operator=( const Brick& ) = default;
	Brick& operator=( Brick&& ) noexcept = default;

	void Update( float dt, const class Scene& scene ) override;
	void Draw( HDC hdc ) override;
	RECT GetRECT() const
	{
		return rigidBody.GetRECT();
	}
	void ReduceHealth()
	{
		health = --health;
	}
private:
	static constexpr int maxHealth = 2;

	PhysicsEntity rigidBody;
	Vec2<int> imageEnd = { pImage->GetWidth(), pImage->GetHeight() };
	
	Gdiplus::Color color;
	int health = maxHealth;
};

