#pragma once

#include "Actor.h"
#include "PhysicsEntity.h"

class Brick : public Actor
{
public:
	Brick( const Vec2<float>& pos, float width, float height, int id );

	~Brick() {}
	Brick( const Brick& ) = default;
	Brick( Brick&& ) = default;
	Brick& operator=( const Brick& ) = default;
	Brick& operator=( Brick&& ) noexcept = default;

	void Update( float dt, class Scene& scene ) override;
	void Draw( HDC hdc ) override;
	RECT GetRECT() const
	{
		return rigidBody.GetRECT();
	}
	void ReduceHealth()
	{
		health = --health;
	}
	void AddCenter( const Vec2<float> addPos )
	{
		rigidBody.SetCenter( initPos + addPos );
	}
private:
	static constexpr int maxHealth = 2;

	PhysicsEntity rigidBody;
	Vec2<float> initPos;
	Gdiplus::Color color;
	int health = maxHealth;
};

