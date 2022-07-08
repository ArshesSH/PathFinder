#include "PanicPlayer.h"

#include "Scene.h"

PanicPlayer::PanicPlayer( const Vec2<float> pos, const Vec2<float> vel, float width, float height, int id )
	:
	DynamicActor( imageName, pos, vel, width, height, id )
{
}

void PanicPlayer::Update( float dt, Scene& scene )
{
	MoveToRelativeCoord( scene.GetSceneTopLeft() );
	KbdInput(dt);
}

void PanicPlayer::Draw( HDC hdc )
{
	Surface::DrawImageChroma( hdc, pImage.get(), movedTopLeft, movedBottomRight, { 0,0 }, imageEnd );
}

void PanicPlayer::KbdInput(float dt)
{
	if ( GetAsyncKeyState( VK_LEFT ) & 0x8001 )
	{
		const Vec2<float> vel = dirLeft * speed * dt;
		rigidBody.SetCenter( rigidBody.GetCenter() + vel );
	}
	else if ( GetAsyncKeyState( VK_RIGHT ) & 0x8001)
	{
		const Vec2<float> vel = dirRight * speed * dt;
		rigidBody.SetCenter( rigidBody.GetCenter() + vel );
	}
	else if ( GetAsyncKeyState( VK_UP ) & 0x8001)
	{
		const Vec2<float> vel = dirUp * speed * dt;
		rigidBody.SetCenter( rigidBody.GetCenter() + vel );
	}
	else if ( GetAsyncKeyState( VK_DOWN ) & 0x8001)
	{
		const Vec2<float> vel = dirDown * speed * dt;
		rigidBody.SetCenter( rigidBody.GetCenter() + vel );
	}
}

void PanicPlayer::MoveToRelativeCoord( const Vec2<float> amount )
{
	movedTopLeft = rigidBody.GetLeftTop() + amount;
	movedBottomRight = rigidBody.GetRightBottom() + amount;
}
