#include "PanicPlayer.h"

#include "Scene.h"

PanicPlayer::PanicPlayer( const Vec2<float> pos, const Vec2<float> vel, float width, float height, int id )
	:
	DynamicActor( imageName, pos, vel, width, height, id )
{
}

void PanicPlayer::Update( float dt, Scene& scene )
{
	MoveObjectToRelativeCoord( scene.GetSceneTopLeft() );
	KbdInput(dt, scene);
}

void PanicPlayer::Draw( Gdiplus::Graphics& gfx )
{
	Surface::DrawImageChroma( gfx, pImage.get(), relativeTopLeft, relativeBottomRight, { 0,0 }, imageEnd );
}

void PanicPlayer::KbdInput(float dt, Scene& scene)
{
	if ( GetAsyncKeyState( VK_LEFT ) & 0x8001 )
	{
		MovePos( dt, dirLeft, scene );
	}
	else if ( GetAsyncKeyState( VK_RIGHT ) & 0x8001 )
	{
		MovePos( dt, dirRight, scene );
	}
	else if ( GetAsyncKeyState( VK_UP ) & 0x8001 )
	{
		MovePos( dt, dirUp, scene );
	}
	else if ( GetAsyncKeyState( VK_DOWN ) & 0x8001 )
	{
		MovePos( dt, dirDown, scene );
	}
}

void PanicPlayer::MovePos( float dt, const Vec2<float>& dir, Scene& scene )
{
	switch ( moveMode )
	{
	case PanicPlayer::MoveMode::Edge:
		{
			// Check can Move
			const Vec2<float> vel = dir * speed * dt;
			const Vec2<float> nextPos = rigidBody.GetCenter() + vel;
				
		}
		break;
	case PanicPlayer::MoveMode::OutSide:
		break;
	}
	 
	const Vec2<float> vel = dir * speed * dt;
	const Vec2<float> nextPos = rigidBody.GetCenter() + vel;
	rigidBody.SetCenter( rigidBody.GetCenter() + vel );
}

void PanicPlayer::MoveObjectToRelativeCoord( const Vec2<float> amount )
{
	relativeTopLeft = rigidBody.GetLeftTop() + amount;
	relativeBottomRight = rigidBody.GetRightBottom() + amount;
}

bool PanicPlayer::CanMove( const Vec2<float> nextPos, const Scene& scene ) const
{
	return false;
}
