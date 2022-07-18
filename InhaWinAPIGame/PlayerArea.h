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

	// Check each line
	bool IsOnEdge( const Vec2<int>& pos, const std::pair<Gdiplus::Point, Gdiplus::Point>& curLine ) const
	{
		if ( IsHorizontal( curLine ) )
		{
			const int left = (std::min)( curLine.first.X, curLine.second.X );
			const int right = (std::max)(curLine.first.X, curLine.second.X);

			return (pos.y == curLine.first.Y ) &&
				pos.x >= left &&
				pos.x <= right;
		}
		else
		{
			const int top = (std::min)(curLine.first.Y, curLine.second.Y);
			const int bottom = (std::max)(curLine.first.Y, curLine.second.Y);
			return pos.x == curLine.first.X &&
				pos.y >= top &&
				pos.y <= bottom;
		}
	}
	// Check all line
	bool IsOnEdge( const Vec2<int>& pos )
	{
		for ( int i = 0; i < vertices.size(); ++i )
		{
			const auto curLine = GetLineFromIndices( { GetSafeIndex( i ), GetSafeIndex( i + 1 ) } );

			if ( !IsOnEdge( pos, curLine ) )
			{
				return false;
			}
		}
		return true;
	}
	bool IsOnInside( const Vec2<int>& pos, const std::pair<Gdiplus::Point, Gdiplus::Point>& curLine )
	{
		// Check Vectors dir
		// Check Point is on right side of vector

		const Vec2<int> line = { curLine.second.X - curLine.first.X, curLine.second.Y - curLine.first.Y };
		const auto crossed = Vec2<int>::GetCrossProduct( line, pos );
		
		if ( crossed > 0 )
		{
			return true;
		}
		return false;
	}

	std::pair<int, int> GetPrevIndices( const std::pair<int, int>& curIndices )
	{
		return { GetSafeIndex( curIndices.first - 1 ), GetSafeIndex( curIndices.second - 1 ) };
	}
	std::pair<int, int> GetNextIndices( const std::pair<int, int>& curIndices )
	{
		return { GetSafeIndex( curIndices.first + 1 ), GetSafeIndex( curIndices.second + 1 ) };
	}

	bool IsOnFirstVertex( const Vec2<int>& pos, const std::pair<Gdiplus::Point, Gdiplus::Point>& curLine ) const
	{
		return ((int)pos.x == (int)curLine.first.X) && ((int)pos.y == (int)curLine.first.Y);
	}
	bool IsOnSecondVertex( const Vec2<int>& pos, const std::pair<Gdiplus::Point, Gdiplus::Point>& curLine ) const
	{
		return ((int)pos.x == (int)curLine.second.X) && ((int)pos.y == (int)curLine.second.Y);
	}

	bool IsHorizontal( const std::pair<Gdiplus::Point, Gdiplus::Point>& line ) const
	{
		return line.first.Y == line.second.Y;
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
	const Gdiplus::Color color{ 255, 0, 255, 0 };
	std::vector<Gdiplus::Point> vertices;
	std::vector<Gdiplus::Point> drawVertices;
};