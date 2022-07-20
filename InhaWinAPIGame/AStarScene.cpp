#include "AStarScene.h"

AStarScene::AStarScene()
	:
	Scene( worldWidth, worldHeight ),
	map( tileSize, 10, 10 )
{}

void AStarScene::Update( float dt, Game& game )
{

}

void AStarScene::Draw( HDC hdc )
{
	Gdiplus::Graphics graphics( hdc );
	map.Draw( graphics );
}
