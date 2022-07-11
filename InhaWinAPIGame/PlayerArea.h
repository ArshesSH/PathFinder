#pragma once

#include "Actor.h"

#include <vector>
#include "PanicPlayer.h"

class PlayerArea : public Actor
{
public:
	PlayerArea( const std::vector<Gdiplus::PointF>& vertices );
	PlayerArea( const Gdiplus::RectF& rect );

	void Update( float dt, class Scene& scene ) override;
	void Draw( Gdiplus::Graphics& gfx )override;

	std::pair<Gdiplus::PointF, Gdiplus::PointF> GetLineFromIndices( const std::pair<int, int>& indices );

	bool IsOnEdge( const Vec2<float>& pos, const std::pair<int, int>& indices ) const
	{
		const auto& curLine = GetLine( indices );
		if ( IsHorizontal( curLine ) )
		{
			return (int)pos.y == (int)curLine.first.Y;
		}
		else
		{
			return ( int )pos.x == (int)curLine.first.X;
		}
	}
	
	bool IsHorizontal( const std::pair<Gdiplus::PointF, Gdiplus::PointF>& line ) const
	{
		return line.first.Y - line.second.Y == 0;
	}

private:
	void MoveToRelativeCoord( const Vec2<float>& amount );
	const std::pair<Gdiplus::PointF, Gdiplus::PointF>& GetLine( const std::pair<int, int>& indices ) const
	{
		return { vertices[indices.first], vertices[indices.second] };
	}
private:
	const Gdiplus::Color color{ 255, 0, 255, 0 };
	std::vector<Gdiplus::PointF> vertices;
	std::vector<Gdiplus::PointF> drawVertices;

	PanicPlayer player;
};