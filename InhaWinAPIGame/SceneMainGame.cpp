#include "SceneMainGame.h"

#include "Game.h"
#include "UtilSH.h"
#include <random>

void SceneMainGame::Update( float dt, const Game& game )
{
	time += dt;
	if ( time >= arrowGenTime )
	{
		std::random_device rd;
		std::mt19937 rng( rd() );
		std::uniform_real_distribution<float> arrowXGen( arrowGenXPadding, (float)game.screenRect.right - arrowGenXPadding );
		arrows.emplace_back(
			Arrow( L"Images/awsom.bmp", Vec2<float>{ arrowXGen( rng ), 0.0f }, Vec2<float>{ 0.0f, arrowSpeed }, arrowWidth, arrowHeight, arrows.size() )
		);
		time = 0.0f;
	}

	for ( auto& arrow : arrows )
	{
		arrow.Update( dt, game );
	}

	UtilSH::remove_erase_if( arrows,
		[]( const Arrow& arrow )
		{
			return arrow.ShouldDestroy();
		}
	);
}

void SceneMainGame::Draw( HDC hdc )
{
	for ( auto& arrow : arrows )
	{
		arrow.Draw( hdc );
	}

	// debug
	std::wstring curArrowCountStr = L"Cur Arrows count : " + std::to_wstring( arrows.size() );
	Surface a;
	a.DrawString( hdc, curArrowCountStr, { 300.0f,300.0f }, Gdiplus::Color( 255, 255, 0, 0 ) );
}
