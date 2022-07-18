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
			for ( int i = 0; i < vertices.size(); ++i )
			{
				const auto curLine = GetLineFromIndices( { GetSafeIndex( i ), GetSafeIndex( i + 1 ) } );

				if ( IsOnEdge( pos, curLine ) )
				{
					indices = GetIndicesFromLine( curLine, pred );
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

			const Vec2<int> line = { curLine.second.X - curLine.first.X, curLine.second.Y - curLine.first.Y };
			const auto crossed = Vec2<int>::GetCrossProduct( line, pos );

			if ( crossed > 0 )
			{
				return true;
			}
			return false;
		}

		bool IsPointInTrianle( const V& p, const V& a, const V& b, const V& c ) const
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
			const auto a = vertices.begin();
			const auto startIt = vertices.cbegin() + startIndices.second;
			const auto endIt = vertices.cbegin() + endIndices.second;

			//if ( startIt == endIt )
			//{
			//	vertices.erase( startIt );
			//}
			//else
			{
				vertices.erase( startIt, endIt );
			}

			vertices.insert( vertices.cbegin() + startIndices.second, insertPoly.vertices.cbegin(), insertPoly.vertices.cend() );
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

	private:
		int CrossProduct( V lhs, V rhs ) const
		{
			return (lhs.X * rhs.Y - lhs.Y * rhs.X);
		}


	public:
		std::vector<V> vertices;
	};
}