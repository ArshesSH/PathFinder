#include "Game.h"

#include "Vec2.h"

Game::Game()
	:
	testBullet( { 500,500 }, { 0,-100 }, 100, 1 )
{
	
}

void Game::ComposeFrame(HDC hdc)
{
	dm.DrawMain( hdc, screenRect );
}

void Game::UpdateModel()
{
	float dt = ft.Mark();
	testBullet.Update(dt);
	dm.Update(dt);
}