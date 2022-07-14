#include "PanicPlayer.h"

#include "Scene.h"
#include <string>

PanicPlayer::PanicPlayer( const Vec2<int> pos, int width, int height )
	:
	pImage( ImageCodex::Retrieve( imageName ) ),
	collisionRect(pos, width, height)
{
}

void PanicPlayer::Update( float dt, Scene& scene )
{
	MoveObjectToRelativeCoord( (Vec2<int>)scene.GetSceneTopLeft() );
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
	const std::wstring playerPosStr = L"PlayerPos: {" + std::to_wstring( collisionRect.GetCenterX() ) + L", " + std::to_wstring( collisionRect.GetCenterY() ) + L"}";
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

void PanicPlayer::MoveObjectToRelativeCoord( const Vec2<int> amount )
{
	relativeTopLeft = collisionRect.GetLeftTop() + amount;
	relativeBottomRight = collisionRect.GetRightBottom() + amount;
}

void PanicPlayer::MovePos( float dt, const Vec2<int>& dir, PlayerArea& area )
{
	moveTime += dt;
	switch ( moveMode )
	{
	case PanicPlayer::MoveMode::Edge:
		{
			if ( moveTime >= movePeriod )
			{
				moveTime = 0.0f;
				const Vec2<int> vel = dir * speed;
				const Vec2<int> nextPos = collisionRect.GetCenter() + vel;
				auto curLine = area.GetLineFromIndices( curLineIndices );
				curVertices = curLine;
				//if ( area.IsOnEdge( nextPos, curLine ) )
				{
					collisionRect.SetCenter( nextPos );
					area.ChangeIndicesOnVertices( collisionRect.GetCenter(), curLineIndices );
				}
			}

		}
		break;
	case PanicPlayer::MoveMode::OutSide:
		break;
	}
}
