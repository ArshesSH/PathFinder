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
	AStar( int width, int height, FindMode findMode );
	
	void SetSrcPos( const Vec2<int>& srcPos_in );
	void SetDestPos( const Vec2<int>& destPos_in );
	void SetObstaclePos( const Vec2<int>& pos );

	void SetToEmpty( const Vec2<int>& pos );
	void ResetNodes();
	void ResetExceptObstacles();
	void ResetExceptObstacleAndPos();
	bool CanTracking() const;
	bool IsSrcSet() const;
	Vec2<int> GetSrcPos() const;
	bool FindPathOnce();
	std::vector<Vec2<int>> GetRoute() const;
	size_t Size() const;
	Node::NodeState GetNodeState( int i ) const;
	std::pair<int, int> GetGH( int i );
	Vec2<int> CurClosedParentPos() const;

private:
	inline void AddToClosedList( const Vec2<int>& pos, int i );
	inline void AddToOpenedList( const Vec2<int>& pos, int i );
	inline void FindPathAtDirs( const Vec2<int>& curPos, const std::vector<Vec2<int>>& dirs );
	inline bool IsContain( const std::vector<Vec2<int>>& container, const Vec2<int>& pos ) const;
	inline int GetDistance( const Vec2<int>& srcPos, const Vec2<int>& destPos );
	inline int GetIndexFromVec2( const Vec2<int>& pos ) const;
	inline bool IsInside( const Vec2<int>& pos ) const;
	inline bool CanMove( const Vec2<int>& pos ) const;
	inline int CalcH( const Vec2<int>& curPos, const Vec2<int>& dest ) const;
	inline bool IsPerpendicular( const Vec2<int>& dir ) const;
	inline int GetDirWeight( const Vec2<int>& dir ) const;

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
	Vec2<int> curPos;

	bool isSrcSet = false;
	bool isDestSet = false;
	bool isInited = false;

	FindMode findMode = FindMode::Diagonal;
	
	std::vector<Node> nodes;
	std::vector<Vec2<int>> openedPosList;
	std::vector<Vec2<int>> closedPosList;
	std::vector<Vec2<int>> route;
};