#pragma once

#include <cassert>
#include <vector>
#include <list>
#include "IndexedLineList.h"

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
		template <typename T>
		int GetSafeIndex( int i, const std::vector<T>& v ) const
		{
			if ( i >= (int)v.size() )
			{
				i %= (int)v.size();
			}
			else if ( i < 0 )
			{
				i = GetSafeIndex( (int)v.size() + i );
			}
			return i;
		}

		bool IsHorizontal( const std::pair<V, V>& line ) const
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
		bool IsOnFirstVertex( const Vec2<int>& pos, const std::pair<V, V>& curLine ) const
		{
			return ((int)pos.x == (int)curLine.first.X) && ((int)pos.y == (int)curLine.first.Y);
		}
		bool IsOnSecondVertex( const Vec2<int>& pos, const std::pair<V, V>& curLine ) const
		{
			return ((int)pos.x == (int)curLine.second.X) && ((int)pos.y == (int)curLine.second.Y);
		}

		std::pair<V, V>GetLineFromIndices( const std::pair<int, int>& indices ) const
		{
			assert( indices.first >= 0 && indices.second < (int)vertices.size() );
			return { vertices[indices.first], vertices[indices.second] };
		}

		void GetLineInform( const Vec2<int>& pos, std::pair<int, int>& indices, std::pair<Gdiplus::Point, Gdiplus::Point>& line )
		{
			for ( int i = 0; i < vertices.size(); ++i )
			{
				const std::pair<int, int> curIdx = { GetSafeIndex( i ), GetSafeIndex( i + 1 ) };
				const auto curLine = GetLineFromIndices( curIdx );

				if ( IsOnEdge( pos, curLine ) )
				{
					indices = curIdx;
					line = curLine;
					return;
				}
			}
		}

		template <typename F>
		std::pair<int, int> GetIndicesFromLine( const std::pair<V, V>& line, F pred ) const
		{
			int first;
			int second;
			for ( int i = 0; i < vertices.size(); ++i )
			{
				if ( pred( vertices[i], line.first ) )
				{
					first = i;
				}
				if ( pred( vertices[i], line.second ) )
				{
					second = i;
				}
			}
			return { first, second };
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
		bool IsOnEdge( const V2& pos ) const
		{
			for ( int i = 0; i < vertices.size(); ++i )
			{
				const auto curLine = GetLineFromIndices( { GetSafeIndex( i ), GetSafeIndex( i + 1 ) } );

				if ( IsOnEdge( pos, curLine ) )
				{
					return true;
				}
			}
			return false;
		}

		template <typename V2, typename F>
		bool IsOnEdge( const V2& pos, std::pair<int, int>& indices, F pred )
		{
			for ( int i = 0; i < (int)vertices.size(); ++i )
			{
				const std::pair<int, int> curIdx = { GetSafeIndex( i ), GetSafeIndex( i + 1 ) };
				const auto curLine = GetLineFromIndices( curIdx );

				if ( IsOnEdge( pos, curLine ) )
				{
					indices = curIdx;
					return true;
				}
			}
			return false;
		}

		template <typename V2>
		bool IsOnPath( const V2& pos ) const
		{
			for ( int i = 1; i < vertices.size(); ++i )
			{
				const auto curLine = GetLineFromIndices( { GetSafeIndex( i - 1 ), GetSafeIndex( i ) } );

				if ( IsOnEdge( pos, curLine ) )
				{
					return true;
				}
			}
			return false;
		}

		bool IsOnInside( const Vec2<int>& pos, const std::pair<V, V>& curLine )
		{
			// Check Vectors dir
			// Check Point is on right side of vector
			const int x = (curLine.second.X - curLine.first.X);
			const int y = (curLine.second.Y - curLine.first.Y);
			const Vec2<int> line = { x, y };
			const auto crossed = Vec2<int>::GetCrossProduct( line, pos );
			if ( crossed > 0 )
			{
				return true;
			}
			return false;
		}
		bool IsOnOutside( const Vec2<int>& pos, std::pair<V, V>& curLine )
		{
			const Vec2<int> line = { curLine.second.X - curLine.first.X, curLine.second.Y - curLine.first.Y };
			const auto crossed = Vec2<int>::GetCrossProduct( line, pos );
			if ( crossed < 0 )
			{
				return true;
			}
			return false;
		}
		bool IsOnOutside( const Vec2<int>& pos )
		{
			for ( int i = 1; i < vertices.size(); ++i )
			{
				const auto curLine = GetLineFromIndices( { GetSafeIndex( i - 1 ), GetSafeIndex( i ) } );
				if ( IsOnOutside( pos, curLine ) )
				{
					return true;
				}
			}
			return false;
		}

		auto size() const
		{
			return vertices.size();
		}
		
		Polygon GetReversed() const
		{
			Polygon reversedPolygon;
			for ( auto rIt = vertices.rbegin(); rIt != vertices.rend(); ++rIt )
			{
				reversedPolygon.vertices.push_back( *rIt );
			}
			return reversedPolygon;
		}

		void InsertAt( const std::pair<int, int>& startIndices, const std::pair<int, int>& endIndices, const Polygon& insertPoly )
		{
			auto startIdx = startIndices.second;
			auto endIdx = endIndices.second;

			auto startIt = vertices.cbegin() + startIdx;
			auto endIt = vertices.cbegin() + endIdx;

			if ( startIdx > endIdx )
			{
				vertices.erase( startIt, vertices.cend() );
				vertices.erase( vertices.cbegin(), endIt );
				vertices.insert( vertices.cbegin() + endIdx, insertPoly.vertices.rbegin(), insertPoly.vertices.rend() );
			}
			else
			{
				vertices.erase( startIt, endIt );
				vertices.insert( vertices.cbegin() + startIdx, insertPoly.vertices.cbegin(), insertPoly.vertices.cend() );
			}
		}

		float GetArea()
		{
			float area = 0;
			for ( int i = 0, j = int(vertices.size() - 1); i < (int)vertices.size(); ++i )
			{
				area += CrossProduct( vertices[j], vertices[i] );
				j = i;
			}
			return area / 2;
		}

		// Abandoned
		/*
		
		bool IsPointInTriangle( const V& p, const V& a, const V& b, const V& c ) const
		{
			const auto ab = b - a;
			const auto bc = c - b;
			const auto ca = a - c;
			const auto ap = p - a;
			const auto bp = p - b;
			const auto cp = p - c;

			const auto cross1 = CrossProduct( ab, ap );
			const auto cross2 = CrossProduct( bc, bp );
			const auto cross3 = CrossProduct( ca, cp );

			if ( cross1 > 0 || cross2 > 0 || cross3 > 0 )
			{
				return false;
			}
			return true;
		}
		std::vector<int> GetTriangulateList()
		{
			std::vector<int> triangles;

			if ( !vertices.empty() && vertices.size() > 3 )
			{
				std::vector<int> indexList;
				for ( int i = 0; i < vertices.size(); ++i )
				{
					indexList.push_back( i );
				}

				const int triangleCount = (int)vertices.size() - 2;
				const int triangleIndexCount = triangleCount * 3;
				triangles.reserve( triangleIndexCount );

				int curIdx = 0;
				for ( ; indexList.size() > 3; )
				{
					for ( int i = 0; i < indexList.size(); ++i )
					{
						const int curIdx = indexList[i];
						const int prevIdx = GetSafeIndex( i - 1, indexList );
						const int nextIdx = GetSafeIndex( i + 1, indexList );

						const auto v0 = vertices[curIdx];
						const auto v1 = vertices[prevIdx];
						const auto v2 = vertices[nextIdx];

					
						//// Check if vertex is convex
						//if ( CrossProduct( v1 - v0, v2 - v0 ) < 0 )
						//{
						//	continue;
						//}

						// Check ear has any vertex
						bool isEar = true;
						for ( int j = 0; j < vertices.size(); ++j )
						{
							if ( j == curIdx || j == prevIdx || j == nextIdx )
							{
								continue;
							}

							const auto p = vertices[j];
							if ( IsPointInTrianle( p, v1, v0, v2 ) )
							{
								isEar = false;
								break;
							}
						}

						if ( isEar )
						{
							triangles.push_back( prevIdx );
							triangles.push_back( curIdx );
							triangles.push_back( nextIdx );
							indexList.erase( indexList.begin()+i );
							break;
						}
					}
				}

				triangles[curIdx++] = indexList[0];
				triangles[curIdx++] = indexList[1];
				triangles[curIdx++] = indexList[2];
			}
			return triangles;
		}
		*/

	private:
		int CrossProduct( V lhs, V rhs ) const
		{
			return (lhs.X * rhs.Y - lhs.Y * rhs.X);
		}


	public:
		std::vector<V> vertices;
	};
}