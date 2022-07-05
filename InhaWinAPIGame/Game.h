#pragma once

#include "framework.h"

#include "FrameTimer.h"
#include "SceneMainGame.h"
#include "DrawManager.h"
#include "FileManager.h"
#include <map>
class Game
{
public:
	enum class SceneType
	{
		SceneStart,
		SceneMainGame,
		SceneResult
	};
public:
	Game();
	void ComposeFrame( HDC hdc );
	void UpdateModel();

	Vec2<float> GetScreenChangeAmount() const;

	unsigned long long GetCurScore();
	std::wstring GetCurUserId()
	{
		return userId;
	}
	void AddScore()
	{
		playerScore += 100;
	}
	bool IsInitialGame() const
	{
		return sceneType == SceneType::SceneStart;
	}
	bool IsGameFinished() const
	{
		return sceneType == SceneType::SceneResult;
	}
	void StartMainGame()
	{
		sceneType = SceneType::SceneMainGame;
	}
	void SetUserID( const std::wstring& id )
	{
		userId = id;
	}
	std::wstring GetUserID() const
	{
		return userId;
	}

	auto GetScoreMap()
	{
		return scoreMap;
	}
	void GetScoreMapFromData()
	{
		auto lines = fileManager.GetLineVector();
		
		for ( auto line : lines )
		{
			auto pos = line.find( L" " );
			const unsigned long long scoreData = std::stoull( line.substr( pos, line.size() ) ) ;
			const std::wstring nameData = line.substr( 0, pos );

			scoreMap[scoreData].push_back( nameData );
		}
	}
	void SaveDataFromScoreMap()
	{
		std::vector<std::wstring> lines;

		scoreMap[playerScore].push_back( userId );
		for ( auto rIt = scoreMap.rbegin(); rIt != scoreMap.rend(); ++rIt )
		{
			for ( auto str : rIt->second )
			{
				lines.push_back( str + L" ");
				lines.push_back( std::to_wstring( rIt->first ) + L"\n");
			}
		}

		fileManager.SaveToFile( lines );
	}

private:

public:
	RECT screenRect;
private:
	static constexpr wchar_t dataDir[] = L"Data/Score.txt";

	RECT oldScreenSize = screenRect;
	FileManager fileManager;
	FrameTimer ft;
	SceneMainGame mainGame;
	DrawManager drawManager;
	Surface surf;

	bool isScreenChanged = true;
	Vec2<float> screenChangeAmount = {0.0f,0.0f};
	float time = 0.0f;
	SceneType sceneType = SceneType::SceneStart;

	std::wstring userId;
	unsigned long long playerScore = 0;
	bool isFinishedResult = false;

	std::map<unsigned long long, std::vector<std::wstring>> scoreMap;
};