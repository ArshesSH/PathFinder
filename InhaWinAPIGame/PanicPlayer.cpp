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

	const int debugVal = 0;
	const std::wstring etcDebugStr = L"Desired Debug : " + std::to_wstring( debugVal );
	Surface::DrawString( gfx, etcDebugStr, { 300, 20 }, Gdiplus::Color( 255, 255, 0, 255 ) );
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

	if ( moveTime >= movePeriod )
	{
		moveTime = 0.0f;
		const Vec2<int> vel = dir * speed;
		const Vec2<int> curPos = collisionRect.GetCenter();
		const Vec2<int> nextPos = curPos + vel;
		auto curLine = area.polygon.GetLineFromIndices( curLineIndices );

		// On Space
		if ( GetAsyncKeyState( VK_SPACE ) & 0x8001 )
		{
			if ( !isStartTracking )
			{
				if ( area.polygon.IsOnEdge( curPos, curLine ) &&
					area.polygon.IsOnInside( nextPos, curLine ) )
				{
					isStartTracking = true;
					//trackingVertices.push_back( curPos );
				}
			}
			else
			{
				// If Player 
				if ( area.polygon.IsOnEdge( nextPos ) )
				{

				}
			}
		}

		switch ( moveMode )
		{
		case PanicPlayer::MoveMode::Edge:
			{
				/* Move Condition
					1. If Not on Vertex, Move by curLineIndices
					2. If on vertex, Check it's first vertex or second vertex
					3. If vertex is first vertex, Get prevLineIndex
					4. If vertex is Second vertex Get NextLineIndex
					5. If Get Two lines, Find next pos is in two lines
					6. If So, Move
					*/

				//for Debug
				curVertices = curLine;

				if ( area.polygon.IsOnFirstVertex( curPos, curLine ) )
				{
					const auto prevLineIndices = area.polygon.GetPrevIndices( curLineIndices );
					const auto prevLine = area.polygon.GetLineFromIndices( prevLineIndices );

					if ( area.polygon.IsOnEdge( nextPos, curLine ) )
					{
						collisionRect.SetCenter( nextPos );
					}
					else if ( area.polygon.IsOnEdge( nextPos, prevLine ) )
					{
						collisionRect.SetCenter( nextPos );
						curLineIndices = prevLineIndices;
					}
				}
				else if ( area.polygon.IsOnSecondVertex( curPos, curLine ) )
				{
					const auto nextLineIndices = area.polygon.GetNextIndices( curLineIndices );
					const auto nextLine = area.polygon.GetLineFromIndices( nextLineIndices );

					if ( area.polygon.IsOnEdge( nextPos, curLine ) )
					{
						collisionRect.SetCenter( nextPos );
					}
					else if ( area.polygon.IsOnEdge( nextPos, nextLine ) )
					{
						collisionRect.SetCenter( nextPos );
						curLineIndices = nextLineIndices;
					}
				}
				else if ( area.polygon.IsOnEdge( nextPos, curLine ) )
				{
					collisionRect.SetCenter( nextPos );
				}
			}
			break;

		case PanicPlayer::MoveMode::Inside:
			{
				/*
				* 1. Can't Move at Border
				* 2. Can Ride Edge
				* 3. If first time, curPos is Edge nextPos is not Edge, curPos is StartPoint, Start tracking
				* 4. If have some curve, record vector
				* 5. 
				*/

			}
			break;
		}
	}
}
