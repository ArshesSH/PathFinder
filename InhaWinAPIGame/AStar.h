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
		Node() {}
		Node(const NodeState& state, const Vec2<int>& parentIdx, int gVal, int hVal)
			:
			state(state),
			parentIdx(parentIdx),
			gVal(gVal),
			hVal(hVal)
		{}

		void ResetNode()
		{
			state = NodeState::Empty;
			parentIdx = { -1, -1 };
			gVal = 0;
			hVal = 0;
		}

		int GetG() const
		{
			return gVal;
		}
		int GetH() const
		{
			return hVal;
		}
		int GetF() const
		{
			return gVal + hVal;
		}
		Vec2<int> GetParentIdx() const
		{
			return parentIdx;
		}
		NodeState GetState() const
		{
			return state;
		}

		void SetG(int v)
		{
			gVal = v;
		}
		void SetH( int v )
		{
			hVal = v;
		}
		void SetParentIdx( const Vec2<int>& idx )
		{
			parentIdx = idx;
		}
		void SetStateEmpty()
		{
			state = NodeState::Empty;
		}
		void SetStateOpened()
		{
			state = NodeState::Opened;
		}
		void SetStateClosed()
		{
			state = NodeState::Closed;
		}
		void SetStateObstacle()
		{
			state = NodeState::Obstacle;
		}
		void SetStateSource()
		{
			state = NodeState::Source;
		}
		void SetStateDest()
		{
			state = NodeState::Dest;
		}
		void SetStateRoute()
		{
			state = NodeState::Route;
		}

		bool IsEmpty() const
		{
			return state == NodeState::Empty;
		}
		bool IsOpened() const
		{
			return state == NodeState::Opened;
		}
		bool IsClosed() const
		{
			return state == NodeState::Closed;
		}
		bool IsObstacle() const
		{
			return state == NodeState::Obstacle;
		}
		bool IsSource() const
		{
			return state == NodeState::Source;
		}
		bool IsDest() const
		{
			return state == NodeState::Dest;
		}
		bool IsRoute() const
		{
			return state == NodeState::Route;
		}

	private:
		NodeState state = NodeState::Empty;
		Vec2<int> parentIdx = {-1, -1};
		int gVal = 0;
		int hVal = 0;
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
		{
			if ( IsInside( lastPos ) )
			{
				SetToEmpty( lastPos );
			}
			nodes[idx].SetStateSource();
			isSrcSet = true;
		}
	}
	void SetDestPos( const Vec2<int>& destPos_in )
	{
		const auto lastPos = destPos;
		destPos = destPos_in;

		const auto idx = GetIndexFromVec2( destPos );
		{
			if ( IsInside( lastPos ) )
			{
				SetToEmpty( lastPos );
			}
			nodes[idx].SetStateDest();
			isDestSet = true;
		}
	}
	void SetObstaclePos(const Vec2<int>& pos)
	{
		const auto idx = GetIndexFromVec2( pos );
		{
			nodes[idx].SetStateObstacle();
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
		openedPosList.clear();
		closedPosList.clear();
		isSrcSet = false;
		isDestSet = false;
		isInited = false;
	}

	void ResetExceptObstacles()
	{
		for ( auto& n : nodes )
		{
			if ( !n.IsObstacle() )
			{
				n.ResetNode();
			}
		}
		openedPosList.clear();
		closedPosList.clear();
		isSrcSet = false;
		isDestSet = false;
		isInited = false;
	}

	void ResetExceptObstacleAndPos()
	{
		for ( auto& n : nodes )
		{
			if (n.IsObstacle() && n.IsSource() && n.IsDest() )
			{
				n.ResetNode();
			}
		}
		openedPosList.clear();
		closedPosList.clear();
		isSrcSet = false;
		isDestSet = false;
		isInited = false;
	}

	//std::vector<Vec2<int>> FindPath()
	//{
	//	// Initilize First
	//	openedPosList.push_back( srcPos );
	//	const int srcIdx = GetIndexFromVec2( srcPos );
	//	nodes[srcIdx].SetStateOpened();
	//	nodes[srcIdx].SetH( CalcH( srcPos, destPos ) );

	//	// Start Find Path
	//	for ( ; !openedPosList.empty(); )
	//	{
	//		auto curPos = openedPosList[0];
	//		

	//		int opendIdx = 0;
	//		auto curIdx = GetIndexFromVec2( curPos );
	//		for ( int i = 1; i < openedPosList.size(); ++i )
	//		{
	//			const auto& node = nodes[GetIndexFromVec2( openedPosList[i] )];
	//			if ( node.GetF() < nodes[curIdx].GetF() ||
	//				(node.GetF() == nodes[curIdx].GetF() &&
	//					node.GetH() < nodes[curIdx].GetH()) )
	//			{
	//				curPos = openedPosList[i];
	//				opendIdx = i;
	//			}
	//		}
	//		curIdx = GetIndexFromVec2( curPos );
	//		UtilSH::remove_element( openedPosList, opendIdx );
	//		
	//		AddToClosedList( curPos, curIdx );

	//		if ( curPos == destPos )
	//		{
	//			std::vector<Vec2<int>> route;

	//			nodes[GetIndexFromVec2( destPos )].SetStateDest();
	//			for ( Vec2<int> curPos = destPos; curPos != srcPos; curPos = nodes[GetIndexFromVec2( curPos )].GetParentIdx() )
	//			{
	//				route.push_back( curPos );
	//				nodes[GetIndexFromVec2( curPos )].SetStateRoute();
	//			}
	//			nodes[GetIndexFromVec2( srcPos )].SetStateSource();
	//			route.push_back( srcPos );
	//			std::reverse( route.begin(), route.end() );
	//			return route;
	//		}

	//		FindPathAtDirs( curPos, perpendicularDirs );

	//		if ( findMode == FindMode::Diagonal )
	//		{
	//			FindPathAtDirs( curPos, diagonalDirs );
	//		}
	//	}
	//}

	bool FindPathOnce()
	{
		if ( !isInited )
		{
			// Initilize First
			openedPosList.push_back( srcPos );
			const int srcIdx = GetIndexFromVec2( srcPos );
			nodes[srcIdx].SetStateOpened();
			nodes[srcIdx].SetH( CalcH( srcPos, destPos ) );

			isInited = true;
		}

		// Start Find Path
		if ( !openedPosList.empty() )
		{
			auto curPos = openedPosList[0];
			int opendIdx = 0;
			auto curIdx = GetIndexFromVec2( curPos );
			for ( int i = 1; i < openedPosList.size(); ++i )
			{
				const auto& node = nodes[GetIndexFromVec2( openedPosList[i] )];
				if ( node.GetF() < nodes[curIdx].GetF() ||
					(node.GetF() == nodes[curIdx].GetF() &&
						node.GetH() < nodes[curIdx].GetH()) )
				{
					curPos = openedPosList[i];
					opendIdx = i;
				}
			}
			curIdx = GetIndexFromVec2( curPos );
			UtilSH::remove_element( openedPosList, opendIdx );

			AddToClosedList( curPos, curIdx );

			if ( curPos == destPos )
			{
				for ( Vec2<int> curPos = destPos; curPos != srcPos; curPos = nodes[GetIndexFromVec2( curPos )].GetParentIdx() )
				{
					route.push_back( curPos );
					nodes[GetIndexFromVec2( curPos )].SetStateRoute();
				}
				nodes[GetIndexFromVec2( srcPos )].SetStateSource();
				nodes[GetIndexFromVec2( destPos )].SetStateDest();
				route.push_back( srcPos );
				std::reverse( route.begin(), route.end() );
				return true;
			}

			FindPathAtDirs( curPos, perpendicularDirs );

			if ( findMode == FindMode::Diagonal )
			{
				FindPathAtDirs( curPos, diagonalDirs );
			}
			return false;
		}
		return false;
	}
	std::vector<Vec2<int>> GetRoute() const
	{
		return route;
	}

	auto Size() const
	{
		return nodes.size();
	}
	auto GetNodeState(int i) const
	{
		return nodes[i].GetState();
	}

	std::pair<int, int> GetGH( int i )
	{
		const auto& node = nodes[i];
		return { node.GetG(), node.GetG() };
	}

	Vec2<int> CurClosedParentPos() const
	{
		return *(closedPosList.begin() + closedPosList.size() - 1);
	}

private:
	void AddToClosedList( const Vec2<int>& pos, int i )
	{
		closedPosList.push_back( pos );
		nodes[i].SetStateClosed();
	}
	void AddToOpenedList( const Vec2<int>& pos, int i )
	{
		openedPosList.push_back( pos );
		nodes[i].SetStateOpened();
	}

	void FindPathAtDirs( const Vec2<int>& curPos, const std::vector<Vec2<int>>& dirs )
	{
		for ( const auto& dir : dirs )
		{
			const auto& nextPos = curPos + dir;
			if ( IsInside( nextPos ) && CanMove( nextPos ) )
			{
				const auto& curNode = nodes[GetIndexFromVec2( curPos )];
				const auto& nextIdx = GetIndexFromVec2( nextPos );
				const auto& nextNode = nodes[nextIdx];
				const int distance = curNode.GetG() + GetDistance( curPos, nextPos );

				if ( distance < nextNode.GetG() ||
					!(IsContain( openedPosList, nextPos )) )
				{
					nodes[nextIdx].SetG( distance );
					nodes[nextIdx].SetH( GetDistance( nextPos, destPos ) );
					nodes[nextIdx].SetParentIdx( curPos );

					if ( !(IsContain( openedPosList, nextPos )) )
					{
						AddToOpenedList( nextPos, nextIdx );
					}
				}
			}
		}
	}

	bool IsContain( const std::vector<Vec2<int>>& container, const Vec2<int>& pos ) const
	{
		return std::find( openedPosList.begin(), openedPosList.end(), pos ) != openedPosList.end();
	}

	int GetDistance( const Vec2<int>& srcPos, const Vec2<int>& destPos )
	{
		int distX = std::abs( srcPos.x - destPos.x );
		int distY = std::abs( srcPos.y - destPos.y );
		if ( distX > distY )
		{
			return diagonalWeight * distY + perpendicularWeight * (distX - distY);
		}
		return  diagonalWeight * distX + perpendicularWeight * (distY - distX);
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

	bool CanMove( const Vec2<int>& pos ) const
	{
		const int idx = GetIndexFromVec2( pos );
		bool canMove = IsInside( pos ) &&
			!(nodes[idx].IsObstacle() || nodes[idx].IsClosed());
		return canMove;
	}

	int CalcH( const Vec2<int>& curPos, const Vec2<int>& dest ) const
	{
		int heuristic = -1;
		auto distVec = (dest - curPos);
		
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
	std::vector<Vec2<int>> openedPosList;
	std::vector<Vec2<int>> closedPosList;
	std::vector<Vec2<int>> route;

	bool isInited = false;
	Vec2<int> curPos;
	Node curNode;
};