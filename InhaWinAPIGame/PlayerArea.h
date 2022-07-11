#pragma once

#include "Actor.h"

#include <vector>
#include <list>

class PlayerArea : public Actor
{
public:
	PlayerArea( const std::vector<Gdiplus::PointF>& vertices );
	PlayerArea( const Gdiplus::RectF& rect );

	void Update( float dt, class Scene& scene ) override;
	void Draw( Gdiplus::Graphics& gfx )override;
	void MoveToRelativeCoord( const Vec2<float>& amount );
	const std::pair<Gdiplus::PointF, Gdiplus::PointF>& GetLineFromIndices( const std::pair<int, int>& indices ) const;

	bool IsOnEdge( const Vec2<float> pos, const std::pair<int, int>& indices ) const
	{
		const auto& curLine = GetLineFromIndices( indices );
		if ( IsHorizontal( curLine ) )
		{
			return ((int)pos.y == (int)curLine.first.Y) &&
				((int)pos.x >= (int)curLine.first.X && (int)pos.y <= (int)curLine.second.X);
		}
		return (int)pos.x == (int)curLine.first.X;
	}

	bool IsHorizontal( const std::pair<Gdiplus::PointF, Gdiplus::PointF>& line ) const
	{
		if ( (int)line.first.Y - (int)line.second.Y == 0 )
		{
			return true;
		}
		return false;
	}
private:

private:
	const Gdiplus::Color color{ 255, 0, 255, 0 };
	std::vector<Gdiplus::PointF> vertices;
	std::vector<Gdiplus::PointF> drawVertices;
};