#pragma once

#include "Actor.h"

#include <vector>
#include "Rect.h"
#include "PlayerArea.h"

class PanicPlayer : public Actor
{

public:
	enum class MoveMode
	{
		Edge,
		Inside
	};

public:
	PanicPlayer( const Vec2<int> pos, int width, int height );

	void Update( float dt, class Scene& scene ) override;
	void Draw( Gdiplus::Graphics& gfx ) override;
	void ControlPlayer( float dt, PlayerArea& area );

private:
	void MoveObjectToRelativeCoord( const Vec2<int> amount );
	void MovePos( float dt, const Vec2<int>& dir, PlayerArea& area );
	void TrackingMode( const Vec2<int>& dir, const Vec2<int>& curPos, const Vec2<int>& nextPos,
		const std::pair<Gdiplus::Point, Gdiplus::Point>& curLine, PlayerArea& area )
	{
		// On Space
		if ( GetAsyncKeyState( VK_SPACE ) & 0x8001 )
		{
			if ( !isStartTracking )
			{
				if ( area.polygon.IsOnEdge( curPos, curLine ) &&
					area.polygon.IsOnInside( dir, curLine ) )
				{
					isStartTracking = true;
					moveMode = MoveMode::Inside;
					trackingVertices.vertices.push_back( { curPos.x, curPos.y } );
					trackingStartIndices = curLineIndices;
				}
			}
			else
			{
				auto IsPointEqual = []( Gdiplus::Point a, Gdiplus::Point b ) { return a.X == b.X && a.Y == b.Y; };
				// Finish Tracking when hit edge
				if ( area.polygon.IsOnEdge( nextPos, trackingEndIndices, IsPointEqual ) )
				{
					isStartTracking = false;
					trackingVertices.vertices.push_back( { nextPos.x, nextPos.y } );
					FinishTracking(area.polygon);
					area.polygon.IsOnEdge( curPos, curLineIndices, IsPointEqual );
					moveMode = MoveMode::Edge;
				}
				else if ( trackingVertices.IsOnPath( nextPos ) )
				{
					isStartTracking = false;
					BreakTracking();
				}
				else
				{
					//Tracking
					Tracking( dir, curPos );
				}
			}
		}
	}

	void Tracking( const Vec2<int>& curDir, const Vec2<int>& curPos)
	{
		if ( lastDir != curDir )
		{
			trackingVertices.vertices.push_back( { curPos.x, curPos.y } );
		}
	}
	void FinishTracking( ArshesSH::Polygon<Gdiplus::Point>& areaPoly )
	{
		const auto finalPos = trackingVertices.vertices.size() - 1;
		const Vec2<int> v0 = { trackingVertices.vertices[0].X, trackingVertices.vertices[0].Y };
		const Vec2<int> v1 = { trackingVertices.vertices[1].X, trackingVertices.vertices[1].Y };
		const Vec2<int> v2 = { trackingVertices.vertices[finalPos].X, trackingVertices.vertices[finalPos].Y };

		const auto n = Vec2<int>::GetCrossProduct( (v1 - v0), (v2 - v0) );
		if ( n > 0 )
		{
			const auto reversedVertices = trackingVertices.GetReversed();
			trackingVertices = reversedVertices;
			std::swap( trackingStartIndices, trackingEndIndices );
		}
		areaPoly.InsertAt( trackingStartIndices, trackingEndIndices, trackingVertices );
		trackingVertices.vertices.clear();
	}
	void BreakTracking()
	{
		collisionRect.SetCenter( { trackingVertices.vertices[0].X, trackingVertices.vertices[0].Y } );
		trackingVertices.vertices.clear();
		moveMode = MoveMode::Edge;
	}
	void GoBack()
	{

	}
	void GoToStartPos()
	{
		collisionRect.SetCenter( { trackingVertices.vertices[0].X, trackingVertices.vertices[0].Y } );
	}


	const Vec2<int>& GetOppositeDir( const Vec2<int>& dir )
	{
		if ( dir == dirUp )
		{
			return dirDown;
		}
		else if ( dir == dirDown )
		{
			return dirUp;
		}
		else if ( dir == dirRight )
		{
			return dirLeft;
		}
		else if ( dir == dirLeft )
		{
			return dirRight;
		}
		return noDir;
	}
private:
	// Image Setting
	static constexpr wchar_t imageName[] = L"Images/awsom.bmp";
	static constexpr float movePeriod = 0.01f;
	std::shared_ptr<Gdiplus::Image> pImage;
	Vec2<int> imageEnd = { pImage->GetWidth(), pImage->GetHeight() };

	// Move Dir Setting
	const Vec2<int> noDir = { 0, 0 };
	const Vec2<int> dirLeft = { -1,0 };
	const Vec2<int> dirUp = { 0,-1 };
	const Vec2<int> dirRight = { 1, 0 };
	const Vec2<int> dirDown = { 0, 1 };
	Vec2<int> lastDir = noDir;

	// Player status
	Vec2<int> dir;
	int speed = 2;
	Rect<int> collisionRect;
	float moveTime = 0.0f;

	// Player Move Node Setting
	MoveMode moveMode = MoveMode::Edge;
	std::pair<int, int> curLineIndices = {0,1};
	ArshesSH::Polygon<Gdiplus::Point> trackingVertices;

	bool isStartTracking = false;
	std::pair<int, int> trackingStartIndices;
	std::pair<int, int> trackingEndIndices;

	// Player Drawing Setting
	Vec2<int> sceneTopLeft;
	Vec2<int> relativeTopLeft;
	Vec2<int> relativeBottomRight;

	//Debug
	std::pair<Gdiplus::Point, Gdiplus::Point> curVertices;
};