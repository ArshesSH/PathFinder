#include "Game.h"

#include "Vec2.h"
#include "Surface.h"


Game::Game()
{
}

void Game::ComposeFrame(HDC hdc)
{
	mainGame.Draw( hdc );
}

void Game::UpdateModel()
{
	float dt = ft.Mark();
	time += dt;
	if ( time >= 1.0f )
	{
		std::random_device rd;
		std::mt19937 rng( rd() );
		std::uniform_real_distribution<float> arrowXGen( arrowGenXPadding, (float)screenRect.right - arrowGenXPadding );
		//arrows.push_back( Arrow( { arrowXGen( rng ), 0.0f },{ 0.0f, arrowSpeed }, arrowWidth, arrowHeight, arrows.size() ) );
		//arrows.emplace_back( L"Images/awsom.bmp", Vec2<float>{ arrowXGen( rng ), 0.0f }, Vec2<float>{ 0.0f, arrowSpeed }, arrowWidth, arrowHeight, arrows.size() );
	}
}