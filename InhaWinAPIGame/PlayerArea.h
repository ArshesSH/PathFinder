#pragma once

#include "Actor.h"

#include <vector>
#include "MathSH.h"

class PlayerArea : public Actor
{
public:
	PlayerArea( const std::vector<Gdiplus::Point>& vertices );
	PlayerArea( const Gdiplus::Rect& rect );

	void Update( float dt, class Scene& scene ) override;
	void Draw( Gdiplus::Graphics& gfx )override;
	void MoveToRelativeCoord( const Vec2<int>& amount );
	std::pair<Gdiplus::Point, Gdiplus::Point> GetLineFromIndices( const std::pair<int, int>& indices ) const;

	//bool IsOnEdge( const Vec2<float>& pos, const std::pair<int, int>& indices ) const
	bool IsOnEdge( const Vec2<int>& pos, const std::pair<Gdiplus::Point, Gdiplus::Point>& curLine ) const
	{
		//const auto& curLine = GetLineFromIndices( indices );
		if ( IsHorizontal( curLine ) )
		{
			return (pos.y == curLine.first.Y ) &&
				pos.x >= curLine.first.X &&
				pos.x <= curLine.second.X;
		}
		else
		{
			return pos.x == curLine.first.X &&
				pos.y >= curLine.first.Y &&
				pos.y <=curLine.second.Y;
		}
	}
	void ChangeIndicesOnVertices( const Vec2<int>& pos, std::pair<int, int>& indices )
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
	bool IsOnFirstVertex( const Vec2<int>& pos, const std::pair<Gdiplus::Point, Gdiplus::Point>& curLine ) const
	{
		//return (MathSH::Compare( pos.x, curLine.first.X ) && MathSH::Compare( pos.y, curLine.first.Y ));

		return ((int)pos.x == (int)curLine.first.X) && ((int)pos.y == (int)curLine.first.Y);
	}
	bool IsOnSecondVertex( const Vec2<int>& pos, const std::pair<Gdiplus::Point, Gdiplus::Point>& curLine ) const
	{
		//return (MathSH::Compare( pos.x, curLine.second.X ) && MathSH::Compare( pos.y, curLine.second.Y ));
		return ((int)pos.x == (int)curLine.second.X) && ((int)pos.y == (int)curLine.second.Y);
	}


	bool IsHorizontal( const std::pair<Gdiplus::Point, Gdiplus::Point>& line ) const
	{
		return MathSH::Compare( line.first.Y, line.second.Y );
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

private:
	const Gdiplus::Color color{ 255, 0, 255, 0 };
	std::vector<Gdiplus::Point> vertices;
	std::vector<Gdiplus::Point> drawVertices;
};