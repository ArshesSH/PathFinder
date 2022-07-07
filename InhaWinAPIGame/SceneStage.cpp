#include "SceneStage.h"

#include "Game.h"
#include "UtilSH.h"

SceneStage::SceneStage()
	:
	player( { 600,600 }, { 0,0 }, 20, 20, 0 )
{
	points.emplace_back( 500, 500 );
	points.emplace_back( 600, 500 );
	points.emplace_back( 600, 600 );
	points.emplace_back( 500, 600 );
}

void SceneStage::Update( float dt, Game& game )
{
	UpdateWorldRect( game );

	player.Update( dt, *this );
}

void SceneStage::Draw( HDC hdc )
{
	surf.DrawRect( hdc, Gdiplus::Color( 255, 255, 0, 255 ), worldBorderThick,
		{ worldRect.X - worldBorderThick, worldRect.Y - worldBorderThick,worldWidth + worldBorderThick, worldHeight + worldBorderThick }
	);
	surf.DrawImageNonChroma( hdc, pBackImage.get(), worldTopLeft, worldBottomRight, { 0,0 }, imageEnd );
	
	player.Draw( hdc );
	surf.DrawFillPolygon( hdc, Gdiplus::Color( 255, 255, 0, 255 ), points[0], points.size() );
}

RECT SceneStage::GetSceneRECT() const
{
	const LONG worldLeft = (LONG)worldRect.X;
	const LONG worldTop = (LONG)worldRect.Y;
	return { worldLeft, worldTop, worldLeft + (LONG)worldWidth, worldTop + (LONG)worldHeight };
}

inline void SceneStage::UpdateWorldRect( Game& game )
{
	const Gdiplus::PointF topLeft = { (game.screenRect.right - worldWidth) * 0.5f, (game.screenRect.bottom - worldHeight) * 0.5f };
	worldRect = { topLeft,{ worldWidth, worldHeight } };
	worldTopLeft = { worldRect.X, worldRect.Y };
	worldBottomRight = { worldRect.X + worldWidth, worldRect.Y + worldHeight };
	worldChangPosAmount = { worldRect.X - lastRect.X, worldRect.Y - lastRect.Y };
}