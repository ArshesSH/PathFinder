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
			Dest,
			Route
		};
	public:
		void ResetNode()
		{
			state = NodeState::Empty;
			parentIdx = { -1, -1 };
			gVal = 0;
			hVal = 0;
			fVal = 0;
		}
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
		nodes[GetIndexFromVec2( pos )].ResetNode();
	}
	void ResetNodes()
	{
		for ( auto& n : nodes )
		{
			n.ResetNode();
		}
		opendPosList.clear();
		closedPosList.clear();
		isSrcSet = false;
		isDestSet = false;
		isInited = false;
	}

	void ResetExceptObstacles()
	{
		for ( auto& n : nodes )
		{
			if ( n.state != Node::NodeState::Obstacle )
			{
				n.ResetNode();
			}
		}
		opendPosList.clear();
		closedPosList.clear();
		isSrcSet = false;
		isDestSet = false;
		isInited = false;
	}

	std::vector<Vec2<int>> FindRoute()
	{
		if ( isSrcSet && isDestSet )
		{
			opendPosList.push_back( srcPos );
			auto& startNode = nodes[GetIndexFromVec2( srcPos )];
			startNode.hVal = CalcH( srcPos, destPos );
			startNode.fVal = startNode.hVal;
			startNode.state = Node::NodeState::Opened;
			
			for ( Vec2<int> curPos = opendPosList[0]; !opendPosList.empty(); )
			{
				Node curNode = nodes[GetIndexFromVec2( opendPosList[0] )];
				auto it = std::find_if( opendPosList.begin(), opendPosList.end(),
					[&]( const Vec2<int>& pos )
					{
						const auto& itNode = nodes[GetIndexFromVec2( pos )];
						if ( itNode.fVal <= curNode.fVal && itNode.hVal <= curNode.hVal )
						{
							curNode = itNode;
							return true;
						}
						return false;
					}
				);
				if ( it != opendPosList.end() )
				{
					curPos = *it;
					UtilSH::remove_element( opendPosList, std::distance( opendPosList.begin(), it ) );
				}
				else
				{
					UtilSH::remove_element( opendPosList, 0 );
				}

				closedPosList.push_back( curPos );
				nodes[GetIndexFromVec2( curPos )].state = Node::NodeState::Closed;

				// Finsh
				if ( curPos == destPos )
				{
					std::vector<Vec2<int>> route;
					nodes[GetIndexFromVec2( destPos )].state = Node::NodeState::Dest;
					for ( Vec2<int> curPos = destPos; curPos != srcPos; curPos = nodes[GetIndexFromVec2(curPos)].parentIdx )
					{
						route.push_back(curPos);
						nodes[GetIndexFromVec2( curPos )].state = Node::NodeState::Route;
					}
					nodes[GetIndexFromVec2( srcPos )].state = Node::NodeState::Source;
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


	bool FindRouteOnce()
	{
		if ( isSrcSet && isDestSet )
		{
			if ( isInited == false )
			{
				opendPosList.push_back( srcPos );
				auto& startNode = nodes[GetIndexFromVec2( srcPos )];
				startNode.hVal = CalcH( srcPos, destPos );
				startNode.fVal = startNode.hVal;
				startNode.state = Node::NodeState::Opened;

				isInited = true;
			}

			curPos = opendPosList[0];
			curNode = nodes[GetIndexFromVec2( opendPosList[0] )];

			int idx = 0;
			for ( int i = 0; i < (int)opendPosList.size() - 1; i++ )
			{
				const auto& curOpenNode = nodes[GetIndexFromVec2( opendPosList[i] )];
				if ( curOpenNode.fVal <= curNode.fVal && curOpenNode.hVal <= curNode.hVal )
				{
					curNode = curOpenNode;
					curPos = opendPosList[i];
					idx = i;
				}
			}
			UtilSH::remove_element( opendPosList, idx );

			closedPosList.push_back( curPos );
			nodes[GetIndexFromVec2( curPos )].state = Node::NodeState::Closed;

			// Finsh
			if ( curPos == destPos )
			{
				std::vector<Vec2<int>> route;
				for ( Vec2<int> curPos = destPos; curPos != srcPos; curPos = nodes[GetIndexFromVec2( curPos )].parentIdx )
				{
					route.push_back( curPos );
					nodes[GetIndexFromVec2( curPos )].state = Node::NodeState::Route;
				}
				nodes[GetIndexFromVec2( destPos )].state = Node::NodeState::Dest;
				nodes[GetIndexFromVec2( srcPos )].state = Node::NodeState::Source;
				route.push_back( srcPos );
				std::reverse( route.begin(), route.end() );

				return true;
			}

			// Do perpendicular
			FindRouteAtDirs( curPos, perpendicularDirs );

			// Do Diagnoal
			if ( findMode == FindMode::Diagonal )
			{
				FindRouteAtDirs( curPos, diagonalDirs );
			}
			return false;
		}
		return true;
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
				Node newNode = CalcValAtNode( curPos, dir, nextPos );
				const auto& curNode = nodes[GetIndexFromVec2( curPos )];
				const int dist = curNode.gVal + GetDirWeight( dir );
				const auto it = std::find( opendPosList.cbegin(), opendPosList.cend(), nextPos );
				const auto nextIdx = GetIndexFromVec2( nextPos );

				if ( dist < nodes[nextIdx].gVal )
				{
					nodes[nextIdx] = newNode;
					if ( it != opendPosList.cend() )
					{
						opendPosList[it - opendPosList.begin()] = nextPos;
					}
					else
					{
						opendPosList.push_back( nextPos );
					}
				}
				else if ( it == opendPosList.cend() )
				{
					nodes[nextIdx] = newNode;
					opendPosList.push_back( nextPos );
				}


				//if( dist < nodes[nextIdx].gVal || it == opendPosList.cend() )
				//{
				//	nodes[nextIdx] = newNode;
				//	opendPosList.push_back( nextPos );
				//}
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
		return canMove;
	}

	int CalcG( const Vec2<int>& pos, const Vec2<int>& dir ) const
	{
		return nodes[GetIndexFromVec2( pos )].gVal + GetDirWeight(dir);
	}

	int CalcH( const Vec2<int>& pos, const Vec2<int>& dest ) const
	{
		int heuristic = -1;
		auto distVec = (dest - pos);
		
		switch ( findMode )
		{
		case AStar::FindMode::Perpendicular:
			{
				heuristic = (std::abs( distVec.x ) + std::abs( distVec.y )) * perpendicularWeight;
			}
			break;
		case AStar::FindMode::Diagonal:
			{
				const int distVecX = std::abs( distVec.x );
				const int distVecY = std::abs( distVec.y );

				int maxVal;
				int minVal;
				if ( distVecX > distVecY )
				{
					maxVal = distVecX;
					minVal = distVecY;
				}
				else
				{
					maxVal = distVecY;
					minVal = distVecX;
				}
				
				heuristic = (std::abs(maxVal - minVal) * perpendicularWeight) + (minVal * diagonalWeight);


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
		//return (int)(Vec2<float>( dir ).GetLength() * perpendicularWeight);
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


	bool isInited = false;
	Vec2<int> curPos;
	Node curNode;
};