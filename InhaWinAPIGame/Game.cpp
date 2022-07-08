#include "Game.h"

#include "Vec2.h"
#include "Surface.h"



Game::Game()
	:
	fileManager( dataDir )
{
	GetScoreMapFromData();
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
					stage.Draw( hdc );
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
	case Game::SceneType::SceneStage:
		{
			float dt = ft.Mark();
			RefreshScreen();
			stage.Update( dt, *this );
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
unsigned long long Game::GetCurScore()
{
	return playerScore;
}
std::wstring Game::GetCurUserId()
{
	return userId;
}
void Game::AddScore()
{
	playerScore += 100;
}
bool Game::IsInitialGame() const
{
	return sceneType == SceneType::SceneStart;
}
bool Game::IsGameFinished() const
{
	return sceneType == SceneType::SceneResult;
}
void Game::StartMainGame()
{
	sceneType = SceneType::SceneMainGame;
}
void Game::SetUserID( const std::wstring& id )
{
	userId = id;
}
std::wstring Game::GetUserID() const
{
	return userId;
}
void Game::GetScoreMapFromData()
{
	auto lines = fileManager.GetLineVector();

	for ( auto line : lines )
	{
		auto pos = line.find( L" " );
		const unsigned long long scoreData = std::stoull( line.substr( pos, line.size() ) );
		const std::wstring nameData = line.substr( 0, pos );

		scoreMap[scoreData].push_back( nameData );
	}
}
void Game::SaveDataFromScoreMap()
{
	std::vector<std::wstring> lines;

	scoreMap[playerScore].push_back( userId );
	for ( auto rIt = scoreMap.rbegin(); rIt != scoreMap.rend(); ++rIt )
	{
		for ( auto str : rIt->second )
		{
			lines.push_back( str + L" " );
			lines.push_back( std::to_wstring( rIt->first ) + L"\n" );
		}
	}

	fileManager.SaveToFile( lines );
}
bool Game::IsScreenChanged() const
{
	return isScreenChanged;
}
