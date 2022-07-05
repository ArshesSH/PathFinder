#pragma once

#include "Actor.h"
#include "PhysicsEntity.h"

class Bullet : public Actor
{
public:
	Bullet( const std::wstring& imagename, const Vec2<float>& pos, const Vec2<float>& vel, float width, float height, int id );
	~Bullet() {}

	Bullet( const Bullet& ) = default;
	Bullet( Bullet&& ) = default;
	Bullet& operator=( const Bullet& ) = default;
	Bullet& operator=( Bullet&& ) noexcept = default;

	void Update( float dt, class Scene& scene ) override;
	void Draw( HDC hdc ) override;
	RECT GetRECT() const;

	void AddPos( const Vec2<float> addPos );

private:
	bool CheckBorder( RECT screenRect ) const;
private:
	std::shared_ptr<Gdiplus::Image> pImage;
	PhysicsEntity rigidBody;
	Vec2<int> imageEnd = { pImage->GetWidth(), pImage->GetHeight() };
};

