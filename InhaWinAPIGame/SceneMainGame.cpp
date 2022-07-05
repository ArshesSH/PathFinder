#include "SceneMainGame.h"

#include "Game.h"
#include "UtilSH.h"
#include <random>

SceneMainGame::SceneMainGame()
	:
	shooter( { shooterImageWidth, shooterImageHeight }, {shooterFrameWidth, shooterFrameHeight} ),
	pBackImage(ImageCodex::Retrieve( backImageName ))
{
	for ( int i = 1; i <= 6; ++i )
	{
		const float brickPosX = worldRect.X + (i * brickWidth) - brickHalfWidth;
		bricks.emplace_back( Vec2<float>{brickPosX, brickPosY}, brickWidth - 1, brickheight, bricks.size() );
	}
}

void SceneMainGame::Update( float dt, Game& game )
{
	if ( isStart )
	{
		time += dt;
		bulletGenTime += dt;

		playerScore = game.GetCurScore();

		UpdateWorldRect(game);

		UpdateShooter(dt);
		UpdateBullet( dt, game );
		GenerateArrows();
		UpdateArrows( dt, game );
		UpdateBricks( dt, game );

		RefreshLastRect( game );
		DestroyObjects();
	}
	else
	{
		// Wait Screen
		UpdateWorldRect( game );

		if ( GetAsyncKeyState( VK_RETURN ) & 0x8000 )
		{
			isStart = true;
			playerName = game.GetUserID();
			RefreshLastRect( game );
		}
	}
}

void SceneMainGame::Draw( HDC hdc )
{
	if ( isStart )
	{
		surf.DrawImageNonChroma( hdc, pBackImage.get(), worldTopLeft,
			worldBottomRight, { 0,0 }, backImageEnd );
		 
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
		shooter.Draw( hdc );

		// Draw World Rect
		surf.DrawRect( hdc, Gdiplus::Color( 255, 56, 56, 68 ), boarderThick, worldRect );

		// Draw Player Name
		std::wstring playerNameStr = L"Player: " + playerName;
		surf.DrawString( hdc, playerNameStr, { worldRect.X, worldTopLeft.y - 60 },
			Gdiplus::Color( 255, 255, 255, 255 ), 24.0f, L"Consolas", Gdiplus::FontStyleBold );

		std::wstring scoreStr = L"Score : " + std::to_wstring( playerScore );
		surf.DrawString( hdc, scoreStr,
			{ float( (worldRect.X + worldWidth) * 0.5 + scoreStr.size() * 8 ), worldTopLeft.y - 60 },
			Gdiplus::Color( 255, 255, 10, 255 ), 24.0f, L"Consolas", Gdiplus::FontStyleBold );

		// debug
		/*
		Surface a;
		std::wstring curArrowCountStr = L"Cur Arrows count : " + std::to_wstring( arrows.size() );
		a.DrawString( hdc, curArrowCountStr, { 0.0f,0.0f }, Gdiplus::Color( 255, 255, 0, 0 ) );
		*/
		/*
		std::wstring worldRectStr = L"worldRect : left=" + std::to_wstring( worldRect.X ) + L" top=" + std::to_wstring( worldRect.Y )
			+ L" right=" + std::to_wstring( worldRect.X + worldWidth ) + L" bottom=" + std::to_wstring( worldRect.Y + worldHeight );
		a.DrawString( hdc, worldRectStr, { 0.0f,80.0f }, Gdiplus::Color( 255, 255, 0, 0 ) );
		*/
	}
	else
	{
		std::wstring startStr = L"Press Enter to Start ";
		const float strStartPosX = (worldRect.X + worldRect.Width - (startStr.size() * 4)) * 0.5f ;
		const float strStartPosY = (worldRect.Y + worldRect.Height) * 0.5f;
		surf.DrawString( hdc, startStr, { strStartPosX ,strStartPosY }, Gdiplus::Color( 255, 255, 0, 255 ) );
	}
}

RECT SceneMainGame::GetSceneRECT() const
{
	const LONG worldLeft = (LONG)worldRect.X;
	const LONG worldTop = (LONG)worldRect.Y;
	return { worldLeft, worldTop, worldLeft + (LONG)worldWidth, worldTop + (LONG)worldHeight };
}

inline void SceneMainGame::UpdateWorldRect( Game& game )
{
	const Gdiplus::PointF topLeft = { (game.screenRect.right - worldWidth) / 2.0f, (game.screenRect.bottom - worldHeight) / 2.0f };
	worldRect = { topLeft,{ worldWidth, worldHeight } };
	worldTopLeft = { worldRect.X, worldRect.Y };
	worldBottomRight = { worldRect.X + worldWidth, worldRect.Y + worldHeight };
	worldChangPosAmount = { worldRect.X - lastRect.X, worldRect.Y - lastRect.Y };
}

inline void SceneMainGame::UpdateShooter(float dt)
{
	const Vec2<float> shooterPos = { worldRect.X + halfWidth, worldRect.Y + worldHeight - shooterImageHeight - shooterImageDistFromRotate };
	shooter.SetCenter( shooterPos );
	shooter.SetRotateCenter( shooterPos + Vec2<float>{0.0f, shooterImageHeight} );
	shooter.Update( dt, *this );

	GenerateBullet();
}

inline void SceneMainGame::GenerateBullet()
{
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
}

inline void SceneMainGame::UpdateBullet( float dt, Game& game )
{
	for ( auto& bullet : bullets )
	{
		bullet.Update( dt, *this );
		if ( game.IsScreenChanged() )
		{
			bullet.AddPos( worldChangPosAmount );
		}
	}
}

inline void SceneMainGame::GenerateArrows()
{
	if ( time >= arrowGenTime )
	{
		std::random_device rd;
		std::mt19937 rng( rd() );
		std::uniform_real_distribution<float> arrowXGen( worldRect.X + boarderThick, worldRect.X + worldWidth - boarderThick );
		arrows.emplace_back(
			Arrow( Vec2<float>{ arrowXGen( rng ), worldRect.Y + arrowHalfHeight }, Vec2<float>{ 0.0f, arrowSpeed }, arrowWidth, arrowHeight, arrows.size() )
		);
		time = 0.0f;
	}
}

inline void SceneMainGame::UpdateArrows( float dt, Game& game )
{
	for ( auto& arrow : arrows )
	{
		arrow.Update( dt, *this );

		if ( game.IsScreenChanged() )
		{
			arrow.AddPos( worldChangPosAmount );
		}

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
}

inline void SceneMainGame::UpdateBricks( float dt, Game& game )
{
	if ( bricks.size() == 0 )
	{
		isSceneFinish = true;
	}

	for ( auto& brick : bricks )
	{
		brick.AddCenter( { worldRect.X, worldRect.Y } );
		brick.Update( dt, *this );
	}
}

inline void SceneMainGame::RefreshLastRect( Game& game )
{
	if ( game.IsScreenChanged() )
	{
		lastRect = worldRect;
	}
}

inline void SceneMainGame::DestroyObjects()
{
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
