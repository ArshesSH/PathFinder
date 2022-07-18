#pragma once

#include <cassert>
#include <vector>

namespace ArshesSH
{
	template<typename V>
	class Polygon
	{
	public:
		Polygon() {};
		Polygon( const std::vector<V>& vertices )
			:
			vertices( vertices )
		{}

		int GetSafeIndex( int i ) const
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
		bool IsHorizontal( const std::pair<Gdiplus::Point, Gdiplus::Point>& line ) const
		{
			return line.first.Y == line.second.Y;
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

		std::pair<V, V>GetLineFromIndices( const std::pair<int, int>& indices ) const
		{
			assert( indices.first >= 0 && indices.second < (int)vertices.size() );
			return { vertices[indices.first], vertices[indices.second] };
		}
		// Check each line

		template <typename V2>
		bool IsOnEdge( const V2& pos, const std::pair<V, V>& curLine ) const
		{
			if ( IsHorizontal( curLine ) )
			{
				const int left = (std::min)(curLine.first.X, curLine.second.X);
				const int right = (std::max)(curLine.first.X, curLine.second.X);

				return (pos.y == curLine.first.Y) &&
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
		template <typename V2>
		bool IsOnEdge( const V2& pos )
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

		auto size() const
		{
			return vertices.size();
		}

	public:
		std::vector<V> vertices;
	};
}