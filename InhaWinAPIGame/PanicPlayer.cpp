#include "PanicPlayer.h"

#include "Scene.h"
#include <string>

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


	// Debug
	const std::wstring lineIndices = L"Indices (" + std::to_wstring( curLineIndices.first ) + L", "
		+ std::to_wstring( curLineIndices.second ) + L")";
	Surface::DrawString( gfx, lineIndices, { 0,0 }, Gdiplus::Color( 255, 255, 255, 255 ) );

	const std::wstring firstVertexStr = L"FirstVertex: {" + std::to_wstring( curVertices.first.X ) + L", " + std::to_wstring( curVertices.first.Y ) + L"}";
	const std::wstring secondVertexStr = L"SecondVertex: {" + std::to_wstring( curVertices.second.X ) + L", " + std::to_wstring( curVertices.second.Y ) + L"}";
	const std::wstring playerPosStr = L"PlayerPos: {" + std::to_wstring( rigidBody.GetCenterX() ) + L", " + std::to_wstring( rigidBody.GetCenterY() ) + L"}";
	Surface::DrawString( gfx, firstVertexStr, { 0,20 }, Gdiplus::Color( 255, 255, 255, 255 ) );
	Surface::DrawString( gfx, secondVertexStr, { 0,40 }, Gdiplus::Color( 255, 255, 255, 255 ) );
	Surface::DrawString( gfx, playerPosStr, { 0,60 }, Gdiplus::Color( 255, 255, 255, 255 ) );
}


void PanicPlayer::ControlPlayer(float dt, PlayerArea& area)
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

void PanicPlayer::MovePos( float dt, const Vec2<float>& dir, PlayerArea& area )
{
	switch ( moveMode )
	{
	case PanicPlayer::MoveMode::Edge:
		{
			const Vec2<float> vel = dir * speed * dt;
			const Vec2<float> nextPos = rigidBody.GetCenter() + vel;
			auto curLine = area.GetLineFromIndices( curLineIndices );
			curVertices = curLine;
			if ( area.IsOnEdge( nextPos, curLine ) )
			{
				rigidBody.SetCenter( nextPos );
				area.ChangeIndicesOnVertices( nextPos, curLineIndices );
			}
			
		}
		break;
	case PanicPlayer::MoveMode::OutSide:
		break;
	}
}
