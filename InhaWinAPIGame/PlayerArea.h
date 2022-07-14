#pragma once

#include "Actor.h"

#include <vector>

class PlayerArea : public Actor
{
public:
	PlayerArea( const std::vector<Gdiplus::PointF>& vertices );
	PlayerArea( const Gdiplus::RectF& rect );

	void Update( float dt, class Scene& scene ) override;
	void Draw( Gdiplus::Graphics& gfx )override;
	void MoveToRelativeCoord( const Vec2<float>& amount );
	std::pair<Gdiplus::PointF, Gdiplus::PointF> GetLineFromIndices( const std::pair<int, int>& indices ) const;

	//bool IsOnEdge( const Vec2<float>& pos, const std::pair<int, int>& indices ) const
	bool IsOnEdge( const Vec2<float>& pos, const std::pair<Gdiplus::PointF, Gdiplus::PointF>& curLine ) const
	{
		//const auto& curLine = GetLineFromIndices( indices );
		if ( IsHorizontal( curLine ) )
		{
			auto a = (int)curLine.second.X;
			return (Compare( pos.y, curLine.first.Y ) &&
				pos.x >= curLine.first.X &&
				pos.x <= curLine.second.X);
		}
		else
		{
			return (Compare( pos.x, curLine.first.X ) &&
				pos.y >= curLine.first.Y &&
				pos.y <=curLine.second.Y);
		}
	}
	void ChangeIndicesOnVertices( const Vec2<float>& pos, std::pair<int, int>& indices )
	{
		const auto& curLine = GetLineFromIndices( indices );
		if ( IsOnFirstVertex(pos, curLine))
		{
			//indices = { GetSafeIndex( indices.first - 1 ), GetSafeIndex( indices.second - 1 ) };
		}
		else if ( IsOnSecondVertex( pos, curLine ) )
		{
			indices = { GetSafeIndex( indices.first + 1 ), GetSafeIndex( indices.second + 1 ) };
		}
	}
	bool IsOnFirstVertex( const Vec2<float>& pos, const std::pair<Gdiplus::PointF, Gdiplus::PointF>& curLine ) const
	{
		return (Compare( pos.x, curLine.first.X ) && Compare( pos.y, curLine.first.Y ));

		//return ((int)pos.x == (int)curLine.first.X) && ((int)pos.y == (int)curLine.first.Y);
	}
	bool IsOnSecondVertex( const Vec2<float>& pos, const std::pair<Gdiplus::PointF, Gdiplus::PointF>& curLine ) const
	{
		return (Compare( pos.x, curLine.second.X ) && Compare( pos.y, curLine.second.Y ));
		//return ((int)pos.x == (int)curLine.second.X) && ((int)pos.y == (int)curLine.second.Y);
	}


	bool IsHorizontal( const std::pair<Gdiplus::PointF, Gdiplus::PointF>& line ) const
	{
		return Compare( line.first.Y, line.second.Y );
	}

	int GetSafeIndex(int i) const
	{
		if ( i >= (int)vertices.size() )
		{
			i %= (int)vertices.size();
		}
		else if ( i < 0 )
		{
			i = GetSafeIndex( (int)vertices.size() + i );
		}
		return i;
	}

	

private:
	bool Compare( float lhs, float rhs ) const
	{
		return std::fabs( rhs - lhs ) < areaEpsilon;
	}

private:
	static constexpr float areaEpsilon = 0.0005f;
	const Gdiplus::Color color{ 255, 0, 255, 0 };
	std::vector<Gdiplus::PointF> vertices;
	std::vector<Gdiplus::PointF> drawVertices;
};