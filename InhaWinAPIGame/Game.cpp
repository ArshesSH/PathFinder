#include "Game.h"

#include "Vec2.h"
#include "Surface.h"

Game::Game()
	:
	testBullet( { 500,500 }, { 0,-100 }, 100, 1 )
{

}

void Game::ComposeFrame(HDC hdc)
{
	dm.DrawMain( hdc, screenRect,
		[this](HDC hdc)
		{
			testBullet.Draw( hdc );
			Surface a;
			a.DrawString( hdc, L"Hello", {300,300}, { 255,255,0,0 } );
		}
		);
}

void Game::UpdateModel()
{
	float dt = ft.Mark();
	testBullet.Update(dt);
	dm.Update(dt);
}