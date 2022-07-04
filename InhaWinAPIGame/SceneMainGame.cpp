#include "SceneMainGame.h"

#include "Game.h"
#include "UtilSH.h"
#include <random>

SceneMainGame::SceneMainGame()
	:
	shooter( L"Images/testCannon.png", { shooterImageWidth, shooterImageHeight } )
{}

void SceneMainGame::Update( float dt, RECT screenRect )
{
	time += dt;

	const Gdiplus::PointF topLeft = { (screenRect.right - worldWidth) / 2.0f, (screenRect.bottom - worldHeight) / 2.0f };
	worldRect = { topLeft,{worldWidth, worldHeight}};

	const Vec2<float> shooterPos = { worldRect.X + halfWidth, worldRect.Y + worldHeight - shooterImageHeight - shooterImageDistFromRotate };
	shooter.SetCenter( shooterPos );
	shooter.SetRotateCenter( shooterPos + Vec2<float>{0.0f, shooterImageHeight} );

	shooter.Update( dt, *this );

	if ( time >= arrowGenTime )
	{
		std::random_device rd;
		std::mt19937 rng( rd() );
		std::uniform_real_distribution<float> arrowXGen( worldRect.X + arrowGenXPadding, worldRect.X + worldWidth - arrowGenXPadding );
		arrows.emplace_back(
			Arrow( L"Images/awsom.bmp", Vec2<float>{ arrowXGen( rng ), worldRect.Y }, Vec2<float>{ 0.0f, arrowSpeed }, arrowWidth, arrowHeight, arrows.size() )
		);
		time = 0.0f;
	}

	for ( auto& arrow : arrows )
	{
		arrow.Update( dt, *this );
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
	shooter.Draw( hdc );
	for ( auto& arrow : arrows )
	{
		arrow.Draw( hdc );
	}

	// debug
	std::wstring curArrowCountStr = L"Cur Arrows count : " + std::to_wstring( arrows.size() );
	Surface a;
	a.DrawString( hdc, curArrowCountStr, { 0.0f,0.0f }, Gdiplus::Color( 255, 255, 0, 0 ) );

	a.DrawRect( hdc, Gdiplus::Color( 255, 255, 0, 255 ), 25, worldRect );
}

RECT SceneMainGame::GetSceneRECT() const
{
	const LONG worldLeft = (LONG)worldRect.X;
	const LONG worldTop = (LONG)worldRect.Y;
	return { worldLeft, worldTop, worldLeft + (LONG)worldWidth, worldTop + (LONG)worldHeight };
}
