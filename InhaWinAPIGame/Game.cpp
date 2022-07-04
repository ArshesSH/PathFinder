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

			std::wstring mousePosDebugStr = L"MousePos = " + std::to_wstring( mousePos.x ) + L", " + std::to_wstring( mousePos.y );
			Surface a;
			a.DrawString( hdc, mousePosDebugStr, { 0,20 }, Gdiplus::Color( 255, 255, 0, 0 ) );
		}
	);
}

void Game::UpdateModel()
{
	float dt = ft.Mark();
	mainGame.Update(dt, screenRect);
}

Vec2<int> Game::GetMousePos()
{
	return mousePos;
}

void Game::SetMousePos( const Vec2<int>& pos )
{
	mousePos = pos;
}
