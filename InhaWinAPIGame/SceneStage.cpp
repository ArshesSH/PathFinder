#include "SceneStage.h"

#include "Game.h"
#include "UtilSH.h"

SceneStage::SceneStage()
	:
	player( { 600,600 }, { 0,0 }, 20, 20, 0 ),
	playerArea( { worldRect.X, worldRect.Y, worldWidth, worldHeight} )
{
}

void SceneStage::Update( float dt, Game& game )
{
	UpdateWorldRect( game );

	playerArea.MoveToRelativeCoord( worldChangPosAmount );
	player.Update( dt, *this );
}

void SceneStage::Draw( HDC hdc )
{
	surf.DrawRect( hdc, Gdiplus::Color( 255, 255, 0, 255 ), worldBorderThick,
		{ worldRect.X - worldBorderThick * 0.5f, worldRect.Y - worldBorderThick * 0.5f,worldWidth + worldBorderThick, worldHeight + worldBorderThick }
	);
	surf.DrawImageNonChroma( hdc, pBackImage.get(), worldTopLeft, worldBottomRight, { 0,0 }, imageEnd );
	
	playerArea.Draw(hdc);
	player.Draw( hdc );
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