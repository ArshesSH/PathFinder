#include "AStar.h"

AStar::AStar( int width, int height, FindMode findMode )
	:
	width( width ),
	height( height ),
	findMode( findMode ),
	nodes( width* height )
{}

void AStar::SetSrcPos( const Vec2<int>&srcPos_in )
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

void AStar::SetDestPos( const Vec2<int>& destPos_in )
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

void AStar::SetObstaclePos( const Vec2<int>& pos )
{
	const auto idx = GetIndexFromVec2( pos );
	{
		nodes[idx].SetStateObstacle();
	}
}

void AStar::SetToEmpty( const Vec2<int>& pos )
{
	nodes[GetIndexFromVec2( pos )].ResetNode();
}

void AStar::ResetNodes()
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

void AStar::ResetExceptObstacles()
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

void AStar::ResetExceptObstacleAndPos()
{
	for ( auto& n : nodes )
	{
		if ( n.IsObstacle() && n.IsSource() && n.IsDest() )
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

bool AStar::CanTracking() const
{
	return isSrcSet && isDestSet;
}

bool AStar::IsSrcSet() const
{
	return isSrcSet;
}

Vec2<int> AStar::GetSrcPos() const
{
	return srcPos;
}

bool AStar::FindPathOnce()
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
				curIdx = GetIndexFromVec2( curPos );
				opendIdx = i;
			}
		}
		curIdx = GetIndexFromVec2( curPos );
		UtilSH::remove_element( openedPosList, opendIdx );

		AddToClosedList( curPos, curIdx );

		if ( curPos == destPos )
		{
			route.clear();
			for ( Vec2<int> curPos = destPos; curPos != srcPos; curPos = nodes[GetIndexFromVec2( curPos )].GetParentIdx() )
			{
				route.push_back( curPos );
				nodes[GetIndexFromVec2( curPos )].SetStateRoute();
			}
			nodes[GetIndexFromVec2( srcPos )].SetStateSource();
			nodes[GetIndexFromVec2( destPos )].SetStateDest();
			route.push_back( srcPos );
			openedPosList.clear();
			closedPosList.clear();
			isSrcSet = false;
			isSrcSet = false;
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

std::vector<Vec2<int>> AStar::GetRoute() const
{
	return route;
}

size_t AStar::Size() const
{
	return nodes.size();
}

AStar::Node::NodeState AStar::GetNodeState( int i ) const
{
	return nodes[i].GetState();
}

std::pair<int, int> AStar::GetGH( int i )
{
	const auto& node = nodes[i];
	return { node.GetG(), node.GetG() };
}

Vec2<int> AStar::CurClosedParentPos() const
{
	return *(closedPosList.begin() + closedPosList.size() - 1);
}

inline void AStar::AddToClosedList( const Vec2<int>& pos, int i )
{
	closedPosList.push_back( pos );
	nodes[i].SetStateClosed();
}

inline void AStar::AddToOpenedList( const Vec2<int>& pos, int i )
{
	openedPosList.push_back( pos );
	nodes[i].SetStateOpened();
}

inline void AStar::FindPathAtDirs( const Vec2<int>& curPos, const std::vector<Vec2<int>>& dirs )
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

inline bool AStar::IsContain( const std::vector<Vec2<int>>& container, const Vec2<int>& pos ) const
{
	return std::find( openedPosList.begin(), openedPosList.end(), pos ) != openedPosList.end();
}

inline int AStar::GetDistance( const Vec2<int>& srcPos, const Vec2<int>& destPos )
{
	int distX = std::abs( srcPos.x - destPos.x );
	int distY = std::abs( srcPos.y - destPos.y );
	if ( distX > distY )
	{
		return diagonalWeight * distY + perpendicularWeight * (distX - distY);
	}
	return  diagonalWeight * distX + perpendicularWeight * (distY - distX);
}

inline int AStar::GetIndexFromVec2( const Vec2<int>& pos ) const
{
	assert( pos.y * width + pos.x >= 0 || pos.y * width + pos.x < (int)nodes.size() );
	return pos.y * width + pos.x;
}

inline bool AStar::IsInside( const Vec2<int>& pos ) const
{
	return pos.x >= 0 && pos.x < width&&
		pos.y >= 0 && pos.y < height;
}

inline bool AStar::CanMove( const Vec2<int>& pos ) const
{
	const int idx = GetIndexFromVec2( pos );
	bool canMove = IsInside( pos ) &&
		!(nodes[idx].IsObstacle() || nodes[idx].IsClosed());
	return canMove;
}

inline int AStar::CalcH( const Vec2<int>& curPos, const Vec2<int>& dest ) const
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

			heuristic = (std::abs( maxVal - minVal ) * perpendicularWeight) + (minVal * diagonalWeight);
		}
		break;
	}
	return heuristic;
}

inline bool AStar::IsPerpendicular( const Vec2<int>& dir ) const
{
	return { dir.x == 0 || dir.y == 0 };
}

inline int AStar::GetDirWeight( const Vec2<int>& dir ) const
{
	return IsPerpendicular( dir ) ? perpendicularWeight : diagonalWeight;
}
