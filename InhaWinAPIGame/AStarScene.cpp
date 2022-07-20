#include "AStarScene.h"
#include "Game.h"

AStarScene::AStarScene()
	:
	Scene( worldWidth, worldHeight ),
	map( tileSize, 20, 16 )
{}

void AStarScene::Update( float dt, Game& game )
{
	UpdateSceneRect( game );
	map.Update( game.GetMousePos(), sceneTopLeft );

	if ( game.IsLeftClicked() )
	{
		map.SetSrcPos();
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
}