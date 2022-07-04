#include "Game.h"

#include "Vec2.h"
#include "Surface.h"


Game::Game()
{
}

void Game::ComposeFrame(HDC hdc)
{
	switch ( sceneType )
	{
	case Game::SceneType::SceneStart:
		{

		}
		break;
	case Game::SceneType::SceneMainGame:
		{
			drawManager.DrawMain( hdc, screenRect, isScreenChanged,
				[this]( HDC hdc )
				{
					mainGame.Draw( hdc );

					std::wstring scoreStr = L"Score : " + std::to_wstring( playerScore );
					
					surf.DrawString( hdc, scoreStr, { float(screenRect.right * 0.5 - ((scoreStr.size() + 1) * 10)) ,0 }, Gdiplus::Color( 255, 255, 0, 255 ) );
				}
			);
			if ( isScreenChanged )
			{
				isScreenChanged = false;
			}
		}
		break;
	case Game::SceneType::SceneResult:
		{

		}
		break;
	}
}

void Game::UpdateModel()
{
	switch ( sceneType )
	{
	case Game::SceneType::SceneStart:
		{

		}
		break;
	case Game::SceneType::SceneMainGame:
		{
			float dt = ft.Mark();

			if ( screenRect.right != oldScreenSize.right || screenRect.bottom != oldScreenSize.bottom )
			{
				isScreenChanged = true;

				screenChangeAmount = { float( screenRect.right - oldScreenSize.right ), float( screenRect.bottom - oldScreenSize.bottom ) };

				oldScreenSize.left = screenRect.left;
				oldScreenSize.top = screenRect.top;
				oldScreenSize.right = screenRect.right;
				oldScreenSize.bottom = screenRect.bottom;
			}
			mainGame.Update( dt, *this );
			if ( mainGame.isSceneFinshed() )
			{
				sceneType = SceneType::SceneResult;
			}
		}
		break;
	case Game::SceneType::SceneResult:
		{
			// Do Once
			if ( !isFinishedResult )
			{
				isFinishedResult = true;
			}
		}
		break;
	}



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
