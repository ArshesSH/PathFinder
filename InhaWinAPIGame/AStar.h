#pragma once

#include <vector>
#include <cassert>
#include "Vec2.h"


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

	public:
		NodeState state;
		int gVal = 0;
		int hVal = 0;
		int fVal = 0;
	};

public:
	AStar( int width, int height )
		:
		width( width ),
		height( height )
	{}

	int GetIndexFromVec2( const Vec2<int>& pos ) const
	{
		assert( pos.y * width + pos.x < 0 || pos.y * width + pos.x > (int)nodeMap.size() );
		return pos.y * width + pos.x;
	}

	bool IsInside( const Vec2<int>& pos ) const
	{
		return pos.x >= 0 && pos.x < width&&
			pos.y >= 0 && pos.y < height;
	}

	bool CanMove( const Vec2<int>& pos ) const
	{
		return IsInside( pos ) &&
			!(nodeMap[GetIndexFromVec2( pos )].state == Node::NodeState::Obstacle ||
				nodeMap[GetIndexFromVec2( pos )].state == Node::NodeState::Closed);
	}

	int CalcG( const Vec2<int>& pos, const Vec2<int>& dir ) const
	{
		const Vec2<int> nextPos = pos + dir;

		nodeMap[GetIndexFromVec2( pos )].gVal + GetDirWeight(dir);
	}

	int CalcH( const Vec2<int>& pos, const Vec2<int>& dest ) const
	{

	}

	bool IsPerpendicular(const Vec2<int>& dir) const
	{
		return { dir.x == 0 || dir.y == 0 };
	}

	int GetDirWeight( const Vec2<int>& dir ) const
	{
		return (int)Vec2<float>{(float)dir.x, (float)dir.y }.GetLength() * dirWeightCorrection;
	}

private:
	static constexpr int dirWeightCorrection = 10;

	const Vec2<int> dirUp = { 0, -1 };
	const Vec2<int> dirDown = { 0, 1 };
	const Vec2<int> dirLeft = { -1,0 };
	const Vec2<int> dirRight = { 1, 0 };

	const int width;
	const int height;

	Vec2<int> srcPos;
	Vec2<int> destPos;

	bool isSrcSet = false;
	bool isDestSet = false;
	
	std::vector<Node> nodeMap;

};