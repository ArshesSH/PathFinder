#pragma once
#include "Actor.h"
class Shooter : public Actor 
{
public:
	enum class State
	{
		CanFire,
		Fire,
		FireCooldown
	};
public:
	Shooter( const std::wstring& imagename, const Vec2<float>& size );
	Shooter( const std::wstring& imagename, const Vec2<float>& center, const Vec2<float>& size, const Vec2<float> rotateCenter );

	void Update( float dt, class Scene& scene ) override;
	void Draw( HDC hdc ) override;
	void SetCenter( const Vec2<float>& v );
	void SetRotateCenter( const Vec2<float>& v );
	Vec2<float> GetShootPos() const;
	Vec2<float> GetShootDir() const;
	void SetStateFireCooldown();
	
	Shooter::State GetState();
private:
	void KbdInput( float dt );

private:
	static constexpr float fireInterval = 2.0f;
	static constexpr float rotateSpeed = 100.0f;
	static constexpr float angleLimit = 60.0f;
	std::shared_ptr<Gdiplus::Image> pImage;
	float angle = 0.0f;
	float fireTime = fireInterval;
	const Vec2<int> imageEnd = {200,400};
	Vec2<float> center;
	Vec2<float> rotateCenter;
	Vec2<float> shootPos;
	const Vec2<float> size;
	
	State state = State::CanFire;
};

