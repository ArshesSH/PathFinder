#include "Game.h"


Game::Game()
{
}

void Game::ComposeFrame(HDC hdc)
{
	test.DrawDoubleBuffering( hdc, screenRect );
}

void Game::UpdateModel()
{

}