#pragma once

#include <vector>
#include <queue>
#include <map>
#include <cassert>
#include "Vec2.h"
#include "UtilSH.h"

class AStar
{
public:
	class Node
	{
	public:
		enum class NodeState
		{
			Empty,
			Opened,
			Closed,
			Obstacle,
			Source,
			Dest
		};

	public:
		NodeState state = NodeState::Empty;
		Vec2<int> parentIdx = {-1, -1};
		int gVal = 0;
		int hVal = 0;
		int fVal = 0;
	};

public:
	enum class FindMode
	{
		Perpendicular,
		Diagonal
	};

public:
	AStar( int width, int height, FindMode findMode )
		:
		width( width ),
		height( height ),
		findMode( findMode ),
		nodes(width * height)
	{}
	
	void SetSrcPos( const Vec2<int>& srcPos_in )
	{
		const auto lastPos = srcPos;
		srcPos = srcPos_in;

		const auto idx = GetIndexFromVec2( srcPos );
		if ( nodes[idx].state == Node::NodeState::Source )
		{
			SetToEmpty( srcPos );
			isSrcSet = false;
		}
		else
		{
			if ( IsInside( lastPos ) )
			{
				SetToEmpty( lastPos );
			}
			nodes[idx].state = Node::NodeState::Source;
			isSrcSet = true;
		}

	}
	void SetDestPos( const Vec2<int>& destPos_in )
	{
		const auto lastPos = destPos;
		destPos = destPos_in;

		const auto idx = GetIndexFromVec2( destPos );
		if ( nodes[idx].state == Node::NodeState::Dest )
		{
			SetToEmpty( destPos );
			isDestSet = false;
		}
		else
		{
			if ( IsInside( lastPos ) )
			{
				SetToEmpty( lastPos );
			}
			nodes[idx].state = Node::NodeState::Dest;
			isDestSet = true;
		}
	}
	void SetObstaclePos(const Vec2<int>& pos)
	{
		const auto idx = GetIndexFromVec2( pos );
		if ( nodes[idx].state == Node::NodeState::Obstacle )
		{
			SetToEmpty( pos );
		}
		else
		{
			nodes[idx].state = Node::NodeState::Obstacle;
		}
	}
	void SetToEmpty( const Vec2<int>& pos )
	{
		nodes[GetIndexFromVec2( pos )].state = Node::NodeState::Empty;
	}
	void ResetNodes()
	{
		for ( auto n : nodes )
		{
			n.state = Node::NodeState::Empty;
		}
		isSrcSet = false;
		isDestSet = false;
	}
	
	std::vector<Vec2<int>> FindRoute()
	{
		if ( isSrcSet && isDestSet )
		{
			opendPosList.push_back( srcPos );
			auto& startNode = nodes[GetIndexFromVec2( srcPos )];
			startNode.hVal = CalcH( srcPos, destPos );
			startNode.fVal = startNode.hVal;
			
			for ( Vec2<int> curPos = opendPosList[0]; !opendPosList.empty(); )
			{
				Node curNode = nodes[GetIndexFromVec2( curPos )];
				//auto it = std::find_if( opendPosList.begin(), opendPosList.end(),
				//	[&]( const Vec2<int>& pos )
				//	{
				//		const auto& itNode = nodes[GetIndexFromVec2( pos )];
				//		return itNode.fVal <= curNode.fVal && itNode.hVal <= curNode.hVal;
				//	}
				//);
				//curPos = *it;
				//UtilSH::remove_element( opendPosList, std::distance( opendPosList.begin(), it ) );

				for ( int i = 1; i < (int)opendPosList.size(); ++i )
				{
					const auto& openNode = nodes[GetIndexFromVec2( opendPosList[i] )];
					if ( openNode.fVal <= curNode.fVal && openNode.hVal <= curNode.hVal )
					{
						curNode = openNode;
						curPos = opendPosList[i];
					}
				}

				closedPosList.push_back( curPos );
				nodes[GetIndexFromVec2( curPos )].state = Node::NodeState::Closed;

				// Finsh
				if ( curPos == destPos )
				{
					std::vector<Vec2<int>> route;
					for ( Vec2<int> curPos = destPos; curPos != srcPos; curPos = nodes[GetIndexFromVec2(curPos)].parentIdx )
					{
						route.push_back(curPos);
					}
					route.push_back( srcPos );
					std::reverse( route.begin(), route.end() );
					return route;
				}

				// Do perpendicular
				FindRouteAtDirs( curPos, perpendicularDirs );

				// Do Diagnoal
				if ( findMode == FindMode::Diagonal)
				{
					FindRouteAtDirs( curPos, diagonalDirs );
				}
			}
		}
	}

	auto Size() const
	{
		return nodes.size();
	}
	auto GetNodeState(int i) const
	{
		return nodes[i].state;
	}

	std::pair<int, int> GetGH( int i )
	{
		const auto& node = nodes[i];
		return { node.gVal, node.hVal };
	}

private:
	inline void FindRouteAtDirs( const Vec2<int>& curPos, const std::vector<Vec2<int>>& dirs )
	{
		for ( const auto& dir : dirs )
		{
			const Vec2<int> nextPos = curPos + dir;
			if ( CanMove( nextPos, dir ) )
			{
				Node nextNode = CalcValAtNode( curPos, dir, nextPos );
				const auto& curNode = nodes[GetIndexFromVec2( curPos )];
				const int dist = curNode.gVal + GetDirWeight( dir );
				const auto it = std::find( opendPosList.cbegin(), opendPosList.cend(), nextPos );

				if( dist < nextNode.gVal || it == opendPosList.cend() )
				{
					nodes[GetIndexFromVec2( nextPos )] = nextNode;
					opendPosList.push_back( nextPos );
				}
			}
		}
	}

	inline Node CalcValAtNode( const Vec2<int>& curPos, const Vec2<int>& dir, const Vec2<int>& nextPos )
	{
		Node nextNode;
		nextNode.state = Node::NodeState::Opened;
		nextNode.gVal = CalcG( curPos, dir );
		nextNode.hVal = CalcH( nextPos, destPos );
		assert( nextNode.hVal != -1 );
		nextNode.fVal = nextNode.gVal + nextNode.hVal;
		nextNode.parentIdx = curPos;

		return nextNode;
	}

	inline int GetIndexFromVec2( const Vec2<int>& pos ) const
	{
		assert( pos.y * width + pos.x >= 0 || pos.y * width + pos.x < (int)nodes.size() );
		return pos.y * width + pos.x;
	}

	bool IsInside( const Vec2<int>& pos ) const
	{
		return pos.x >= 0 && pos.x < width&&
			pos.y >= 0 && pos.y < height;
	}

	bool CanMove( const Vec2<int>& pos, const Vec2<int>& dir ) const
	{
		const int idx = GetIndexFromVec2( pos );
		bool canMove = IsInside( pos ) &&
			!(nodes[idx].state == Node::NodeState::Obstacle ||nodes[idx].state == Node::NodeState::Closed);

		/*switch ( findMode )
		{
		case AStar::FindMode::Diagonal:
			{
				const Vec2<int> wallX = { pos.x - dir.x, pos.y };
				const Vec2<int> wallY = { pos.x, pos.y - dir.y };

				canMove |= !(nodes[GetIndexFromVec2( wallX )].state == Node::NodeState::Obstacle ||
					nodes[GetIndexFromVec2( wallY )].state == Node::NodeState::Obstacle);
			}
			break;
		}*/
		return canMove;
	}

	int CalcG( const Vec2<int>& pos, const Vec2<int>& dir ) const
	{
		return nodes[GetIndexFromVec2( pos )].gVal + GetDirWeight(dir);
	}

	int CalcH( const Vec2<int>& pos, const Vec2<int>& dest ) const
	{
		int heuristic = -1;
		auto destVec = (dest - pos) * perpendicularWeight;
		switch ( findMode )
		{
		case AStar::FindMode::Perpendicular:
			{
				heuristic = std::abs( destVec.x ) + std::abs( destVec.y );
			}
			break;
		case AStar::FindMode::Diagonal:
			{
				heuristic = destVec.GetLength();
			}
			break;
		}
		return heuristic;
	}

	bool IsPerpendicular(const Vec2<int>& dir) const
	{
		return { dir.x == 0 || dir.y == 0 };
	}

	int GetDirWeight( const Vec2<int>& dir ) const
	{
		return IsPerpendicular( dir ) ? perpendicularWeight : diagonalWeight;
	}

private:
	static constexpr int perpendicularWeight = 10;
	static constexpr int diagonalWeight = 14;

	const Vec2<int> dirUp = { 0, -1 };
	const Vec2<int> dirDown = { 0, 1 };
	const Vec2<int> dirLeft = { -1,0 };
	const Vec2<int> dirRight = { 1, 0 };

	const std::vector<Vec2<int>> perpendicularDirs = { dirRight, dirDown, dirUp, dirLeft, };
	const std::vector<Vec2<int>> diagonalDirs = {
		{dirUp + dirRight},
		{dirDown + dirRight},
		{dirDown + dirLeft},
		{dirUp + dirLeft}
	};

	const int width;
	const int height;

	Vec2<int> srcPos;
	Vec2<int> destPos;

	bool isSrcSet = false;
	bool isDestSet = false;

	FindMode findMode = FindMode::Diagonal;
	
	std::vector<Node> nodes;
	std::vector<Vec2<int>> opendPosList;
	std::vector<Vec2<int>> closedPosList;
};