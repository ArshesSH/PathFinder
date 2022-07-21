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
	sceneTopLeft = scene.GetSceneTopLeft();
	MoveObjectToRelativeCoord( {sceneTopLeft.x + 25, sceneTopLeft.y + 25} );
}

void PanicPlayer::Draw( Gdiplus::Graphics& gfx )
{
	Surface::DrawImageChroma( gfx, pImage.get(), relativeTopLeft, relativeBottomRight, { 0,0 }, imageEnd );
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

		TrackingMode( dir, curPos, nextPos, curLine, area );

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
				if ( dir != GetOppositeDir( lastDir ) )
				{
					collisionRect.SetCenter( nextPos );
					lastDir = dir;
				}
			}
			break;
		}
	}
}
