#include "AStarScene.h"
#include "Game.h"

AStarScene::AStarScene()
	:
	map( tileSize, tileRow, tileCol ),
	Scene( tileRow* tileSize, tileCol* tileSize ),
	player( { 0,0 }, playerSize, playerSize )
{}

void AStarScene::Update( float dt, Game& game )
{
	UpdateSceneRect( game );

	map.Update( game.GetMousePos(), sceneTopLeft, dt );
	player.Update( dt, *this );
	if ( map.IsSrcSet() )
	{
		if ( GetAsyncKeyState( VK_SPACE ) )
		{
			if ( map.CanTracking() )
			{
				isFindStart = true;
			}
		}

		if ( isFindStart )
		{
			time += dt;

			if ( time >= searchDrawDelay )
			{
				if ( map.FindPathOnce() )
				{
					route = map.GetRoute();
					isFindStart = false;
				}
				time = 0.0f;
			}
		}
	}

	if ( !route.empty() )
	{
		MovePlayer( dt );
	}

	if ( game.IsLeftClicked() )
	{
		map.SetSrcPos();
		player.SetPos( map.GetSrcTilePos() );
	}
	else if ( game.IsRightClicked() )
	{
		map.SetObstaclePos();
	}
	else if ( game.IsMiddleClicked() )
	{
		map.SetDestPos();
	}
}

void AStarScene::Draw( HDC hdc )
{
	Gdiplus::Graphics graphics( hdc );
	map.Draw( graphics );
	//if ( map.IsSrcSet() )
	{
		player.Draw( graphics );
	}
}

int AStarScene::GetHalfTileSize() const
{
	return halfTileSize;
}

void AStarScene::MovePlayer( float dt )
{
	const auto& tilePos = route.back() * tileSize;
	if ( player.GetPos() == tilePos )
	{
		route.pop_back();
	}
	else
	{
		player.Move( dt, tilePos );
	}
}
