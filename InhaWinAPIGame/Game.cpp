#include "Game.h"

#include "Vec2.h"
#include "Surface.h"


Game::Game()
{
	//arrows.emplace_back( Arrow(L"Images/awsom.bmp", { 200.0f,0.0f }, { 0.0f, 100.0f }, 20, 100, 1) );
	//arrows.emplace_back( Arrow( L"Images/awsom.bmp", { 500.0f,0.0f }, { 0.0f, 100.0f }, 20, 100, 1 ) );
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
	//for ( auto& a : arrows )
	//{
	//	a.Update( dt, screenRect );
	//}
	mainGame.Update(dt, screenRect);
}