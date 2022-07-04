#include "SceneMainGame.h"

#include "Game.h"
#include "UtilSH.h"
#include <random>

SceneMainGame::SceneMainGame()
	:
	shooter( L"Images/testCannon.png", { shooterImageWidth, shooterImageHeight } )
{
	for ( int i = 1; i <= 6; ++i )
	{
		const float brickPosX = worldRect.X + (i * brickWidth) - brickHalfWidth;
		bricks.emplace_back( Vec2<float>{brickPosX, brickPosY}, brickWidth - 1, brickheight, bricks.size() );
	}
}

void SceneMainGame::Update( float dt, Game& game )
{
	time += dt;
	bulletGenTime += dt;

	const Gdiplus::PointF topLeft = { (game.screenRect.right - worldWidth) / 2.0f, (game.screenRect.bottom - worldHeight) / 2.0f };
	worldRect = { topLeft,{worldWidth, worldHeight}};

	const Vec2<float> shooterPos = { worldRect.X + halfWidth, worldRect.Y + worldHeight - shooterImageHeight - shooterImageDistFromRotate };
	shooter.SetCenter( shooterPos );
	shooter.SetRotateCenter( shooterPos + Vec2<float>{0.0f, shooterImageHeight} );

	shooter.Update( dt, *this );

	if ( bulletGenTime >= bulletGenTimeLimit )
	{
		if ( GetAsyncKeyState( VK_SPACE ) & 0x8000 )
		{
			bullets.emplace_back(
				L"Images/cannonBall.png", shooter.GetShootPos(), shooter.GetShootDir() * bulletSpeed, bulletWidth, bulletHeight, bullets.size()
			);
			bulletGenTime = 0.0f;
		}
	}

	for ( auto& bullet : bullets )
	{
		bullet.Update( dt, *this );
	}

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
		
		for ( auto& bullet : bullets )
		{
			if ( arrow.isOverlapWith( bullet.GetRECT() ) )
			{
				game.AddScore();
				arrow.SetDestroy();
				bullet.SetDestroy();
			}
		}
		for ( auto& brick : bricks )
		{
			if ( arrow.isOverlapWith( brick.GetRECT() ) )
			{
				arrow.SetDestroy();
				brick.ReduceHealth();
			}
		}
	}

	if ( bricks.size() == 0 )
	{
		isSceneFinish = true;
	}

	for ( auto& brick : bricks )
	{
		brick.AddCenter( { worldRect.X, worldRect.Y } );
		brick.Update( dt, *this );
	}

	// Destroy Objects

	UtilSH::remove_erase_if( arrows,
		[]( const Arrow& arrow )
		{
			return arrow.ShouldDestroy();
		}
	);
	UtilSH::remove_erase_if( bullets,
		[]( const Bullet& bullet )
		{
			return bullet.ShouldDestroy();
		}
	);
	UtilSH::remove_erase_if( bricks,
		[]( const Brick& brick )
		{
			return brick.ShouldDestroy();
		}
	);
}

void SceneMainGame::Draw( HDC hdc )
{
	shooter.Draw( hdc );
	for ( auto& bullet : bullets )
	{
		bullet.Draw( hdc );
	}
	for ( auto& arrow : arrows )
	{
		arrow.Draw( hdc );
	}
	for ( auto& brick : bricks )
	{
		brick.Draw( hdc );
	}
	

	// debug
	Surface a;
	std::wstring curArrowCountStr = L"Cur Arrows count : " + std::to_wstring( arrows.size() );
	a.DrawString( hdc, curArrowCountStr, { 0.0f,0.0f }, Gdiplus::Color( 255, 255, 0, 0 ) );

	std::wstring worldRectStr = L"worldRect : left=" + std::to_wstring( worldRect.X ) + L" top=" + std::to_wstring( worldRect.Y )
		+ L" right=" + std::to_wstring( worldRect.X + worldWidth ) + L" bottom=" + std::to_wstring( worldRect.Y + worldHeight );
	a.DrawString( hdc, worldRectStr, { 0.0f,80.0f }, Gdiplus::Color( 255, 255, 0, 0 ) );

	// DrawRect
	a.DrawRect( hdc, Gdiplus::Color( 255, 255, 0, 255 ), 25, worldRect );

}

RECT SceneMainGame::GetSceneRECT() const
{
	const LONG worldLeft = (LONG)worldRect.X;
	const LONG worldTop = (LONG)worldRect.Y;
	return { worldLeft, worldTop, worldLeft + (LONG)worldWidth, worldTop + (LONG)worldHeight };
}
