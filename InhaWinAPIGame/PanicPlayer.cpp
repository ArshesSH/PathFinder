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
}

void PanicPlayer::Draw( Gdiplus::Graphics& gfx )
{
	Surface::DrawImageChroma( gfx, pImage.get(), relativeTopLeft, relativeBottomRight, { 0,0 }, imageEnd );
}


void PanicPlayer::ControlPlayer(float dt, const PlayerArea& area)
{
	if ( GetAsyncKeyState( VK_LEFT ) & 0x8001 )
	{
		MovePos( dt, dirLeft, area );
	}
	else if ( GetAsyncKeyState( VK_RIGHT ) & 0x8001 )
	{
		MovePos( dt, dirRight, area );
	}
	else if ( GetAsyncKeyState( VK_UP ) & 0x8001 )
	{
		MovePos( dt, dirUp, area );
	}
	else if ( GetAsyncKeyState( VK_DOWN ) & 0x8001 )
	{
		MovePos( dt, dirDown, area );
	}

}

void PanicPlayer::MoveObjectToRelativeCoord( const Vec2<float> amount )
{
	relativeTopLeft = rigidBody.GetLeftTop() + amount;
	relativeBottomRight = rigidBody.GetRightBottom() + amount;
}

void PanicPlayer::MovePos( float dt, const Vec2<float>& dir, const PlayerArea& area )
{
	switch ( moveMode )
	{
	case PanicPlayer::MoveMode::Edge:
		{
			const Vec2<float> vel = dir * speed * dt;
			const Vec2<float> nextPos = rigidBody.GetCenter() + vel;
			if ( area.IsOnEdge( nextPos, curLineIndices ) )
			{
				rigidBody.SetCenter( nextPos );
			}
		}
		break;
	case PanicPlayer::MoveMode::OutSide:
		break;
	}
}
