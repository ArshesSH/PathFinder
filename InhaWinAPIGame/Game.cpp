#include "Game.h"

#include "Vec2.h"
#include "Surface.h"


Game::Game()
{
}

void Game::ComposeFrame(HDC hdc)
{
	drawManager.DrawMain( hdc, screenRect,
		[this]( HDC hdc )
		{
			mainGame.Draw( hdc );
		}
	);


}

void Game::UpdateModel()
{
	float dt = ft.Mark();
	mainGame.Update(dt, *this);
}