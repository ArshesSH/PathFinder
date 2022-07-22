#include "TileMap.h"

 TileMap::TileMap( int tileSize, int tileRow, int tileCol )
	:
	tileSize( tileSize ),
	tileRow( tileRow ),
	tileCol( tileCol ),
	width( tileSize* tileRow ),
	height( tileSize* tileCol ),
	aStar( tileRow, tileCol, AStar::FindMode::Diagonal )
{
}

 void TileMap::Update( const Vec2<int>& mousePos_in, const Vec2<int>& sceneTopLeft_in, float dt )
{
	mousePos = mousePos_in;
	sceneTopLeft = sceneTopLeft_in;

	if ( GetAsyncKeyState( VK_RETURN ) )
	{
		aStar.ResetNodes();
	}

	if ( GetAsyncKeyState( VK_LSHIFT ) )
	{
		aStar.ResetExceptObstacles();
	}
}

 bool TileMap::FindPathOnce()
{
	return aStar.FindPathOnce();
}

 bool TileMap::CanTracking() const
{
	return aStar.CanTracking();
}

 void TileMap::SetFindStart()
{
	isFindStart = true;
}

 std::vector<Vec2<int>> TileMap::GetRoute()
{
	return aStar.GetRoute();
}

 void TileMap::Draw( Gdiplus::Graphics& gfx )
{
	for ( int i = 0; i < (int)aStar.Size(); ++i )
	{
		const int x = i % tileRow;
		const int y = i / tileRow;
		Gdiplus::Color c;
		switch ( aStar.GetNodeState( i ) )
		{
		case AStar::Node::NodeState::Empty:
			{
				c = White;
			}
			break;
		case AStar::Node::NodeState::Opened:
			{
				c = Green;
			}
			break;
		case AStar::Node::NodeState::Closed:
			{
				c = Red;
			}
			break;
		case AStar::Node::NodeState::Obstacle:
			{
				c = Gray;
			}
			break;
		case AStar::Node::NodeState::Source:
			{
				c = Blue;
			}
			break;
		case AStar::Node::NodeState::Dest:
			{
				c = Purple;
			}
			break;
		case AStar::Node::NodeState::Route:
			{
				c = LightPink;
			}
			break;
		}
		const int xPos = (x * tileSize) + sceneTopLeft.x;
		const int yPos = (y * tileSize) + sceneTopLeft.y;
		DrawRect( gfx, xPos, yPos, c );

		const auto gh = aStar.GetGH( i );
		DrawInforms( gfx, xPos, yPos, gh.first, gh.second, gh.first + gh.second );
	}

	const std::wstring guideStr =
		L"LButton: Src Pos\nRButton: Dest Pos\nMButton: Obstacle\nSpaceBar: Find Path\nEnter: Remove All\nShift: Remove Except Obstacles\nSetting Src or Dest can remove Obstacles";
	Surface::DrawString( gfx, guideStr, { 10,40 }, White, 15 );

	// Debug Things
	const auto pos = FindTileFromPos();
	const std::wstring posStr = L"Coord : (" + std::to_wstring( pos.x ) + L"," + std::to_wstring( pos.y ) + L")";
	Surface::DrawString( gfx, posStr, { 0,0 }, White );
}

 void TileMap::SetSrcPos()
{
	const auto tilePos = FindTileFromPos();
	if ( tilePos != Vec2<int>{-1, -1} )
	{
		aStar.SetSrcPos( tilePos );
	}
}

 void TileMap::SetDestPos()
{
	const auto tilePos = FindTileFromPos();
	if ( tilePos != Vec2<int>{-1, -1} )
	{
		aStar.SetDestPos( tilePos );
	}
}

 void TileMap::SetObstaclePos()
{
	const auto tilePos = FindTileFromPos();
	if ( tilePos != Vec2<int>{-1, -1} )
	{
		aStar.SetObstaclePos( tilePos );
	}
}

 std::vector<Vec2<int>> TileMap::GetRawPath() const
{
	return path;
}

 bool TileMap::IsSrcSet() const
{
	return aStar.IsSrcSet();
}

 Vec2<int> TileMap::GetSrcTilePos() const
{
	return GridToTile( aStar.GetSrcPos() );
}

 void TileMap::DrawRect( Gdiplus::Graphics& gfx, int x, int y, Gdiplus::Color innerColor )
 {
	 Surface::DrawFillRect( gfx, innerColor, x + 1, y + 1, tileSize - 1, tileSize - 1 );
	 Surface::DrawRect( gfx, Black, 1, x, y, tileSize, tileSize );
 }

 void TileMap::DrawInforms( Gdiplus::Graphics& gfx, int x, int y, int g, int h, int f )
 {
	 const std::wstring strGH = std::to_wstring( g ) + L"  " + std::to_wstring( h );
	 Surface::DrawString( gfx, strGH, (float)x, (float)y, Black, 10 );

	 const std::wstring strF = std::to_wstring( f );
	 Surface::DrawString( gfx, strF, (float)x + tileSize / 2.0f, (float)y + tileSize - 10, Black, 10 );
 }

 Vec2<int> TileMap::FindTileFromPos()
 {
	 const auto movedPos = mousePos - sceneTopLeft;
	 if ( IsInsideTileMap( movedPos ) )
	 {
		 return movedPos / tileSize;
	 }
	 return { -1,-1 };
 }

 bool TileMap::IsInsideTileMap( const Vec2<int>& pos ) const
 {
	 return pos.x >= 0 && pos.x < width&& pos.y >= 0 && pos.y < height;
 }

 Vec2<int> TileMap::GridToTile( const Vec2<int>& pos ) const
 {
	 return pos * tileSize;
 }