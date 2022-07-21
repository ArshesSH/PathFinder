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
	case Game::SceneType::SceneStage:
		{
			drawManager.DrawMain( hdc, screenRect, isScreenChanged,
				[this]( HDC hdc )
				{
					sceneAStar.Draw( hdc );
				}
			);

			if ( isScreenChanged )
			{
				isScreenChanged = false;
			}
		}
		break;
	case Game::SceneType::SceneTest:
		{
			drawManager.DrawMain( hdc, screenRect, isScreenChanged,
				[this]( HDC hdc )
				{
					//sceneAStar.Draw( hdc );
				}
			);
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
	case Game::SceneType::SceneStage:
		{
			float dt = ft.Mark();
			RefreshScreen();
			sceneAStar.Update( dt, *this );
		}
		break;
	case Game::SceneType::SceneTest:
		{
			float dt = ft.Mark();
			RefreshScreen();
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
void Game::RefreshScreen()
{
	if ( screenRect.right != oldScreenSize.right || screenRect.bottom != oldScreenSize.bottom )
	{
		isScreenChanged = true;

		oldScreenSize.left = screenRect.left;
		oldScreenSize.top = screenRect.top;
		oldScreenSize.right = screenRect.right;
		oldScreenSize.bottom = screenRect.bottom;
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
bool Game::IsInitialGame() const
{
	return sceneType == SceneType::SceneStart;
}
bool Game::IsGameFinished() const
{
	return sceneType == SceneType::SceneResult;
}
bool Game::IsScreenChanged() const
{
	return isScreenChanged;
}
