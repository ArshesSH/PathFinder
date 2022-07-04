#pragma once
#include "Actor.h"
class Shooter : public Actor 
{
public:
	Shooter( const std::wstring& imageName, const Vec2<float>& size );
	Shooter( const std::wstring& imageName, const Vec2<float>& center, const Vec2<float>& size, const Vec2<float> rotateCenter );

	void Update( float dt, const class Game& game ) override;
	void Draw( HDC hdc ) override;
	void SetCenter( const Vec2<float>& v );
	void SetRotateCenter( const Vec2<float>& v );
private:
	void KbdInput(float dt)
	{
		fireTime += dt;

		if ( GetAsyncKeyState( VK_RIGHT ) & 0x8000 )
		{
			angle += rotateSpeed * dt;
		}
		if ( GetAsyncKeyState( VK_LEFT ) & 0x8000 )
		{
			angle -= rotateSpeed * dt;
		}

		if ( fireTime >= fireInterval )
		{
			if ( GetAsyncKeyState( VK_SPACE ) & 0x8000 )
			{

				fireTime = 0.0f;
			}
		}
	}

private:
	static constexpr float fireInterval = 2.0f;
	static constexpr float rotateSpeed = 100.0f;
	float angle = 0.0f;
	float fireTime = 0.0f;
	const Vec2<int> imageEnd = {200,400};
	Vec2<float> center;
	Vec2<float> rotateCenter;
	const Vec2<float> size;

};

