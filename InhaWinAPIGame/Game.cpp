#include "Game.h"

#include "Vec2.h"
#include "Surface.h"


Game::Game()
{
}

void Game::ComposeFrame(HDC hdc)
{
	drawManager.DrawMain( hdc, screenRect, isScreenChanged,
		[this]( HDC hdc )
		{
			mainGame.Draw( hdc );

			std::wstring mousePosDebugStr = L"MousePos = " + std::to_wstring( mousePos.x ) + L", " + std::to_wstring( mousePos.y );
			Surface a;
			a.DrawString( hdc, mousePosDebugStr, { 0,20 }, Gdiplus::Color( 255, 255, 0, 0 ) );
		}
	);
	if ( isScreenChanged )
	{
		isScreenChanged = false;
	}
}

void Game::UpdateModel()
{
	float dt = ft.Mark();
	if ( screenRect.right != oldScreenSize.right || screenRect.bottom != oldScreenSize.bottom )
	{
		isScreenChanged = true;

		screenChangeAmount = { float(screenRect.right - oldScreenSize.right), float(screenRect.bottom - oldScreenSize.bottom) };

		oldScreenSize.left = screenRect.left;
		oldScreenSize.top = screenRect.top;
		oldScreenSize.right = screenRect.right;
		oldScreenSize.bottom = screenRect.bottom;
	}
	mainGame.Update(dt, *this);
}

Vec2<int> Game::GetMousePos()
{
	return mousePos;
}

void Game::SetMousePos( const Vec2<int>& pos )
{
	mousePos = pos;
}

Vec2<float> Game::GetScreenChangeAmount() const
{
	return screenChangeAmount;
}
