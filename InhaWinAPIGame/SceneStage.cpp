#include "SceneStage.h"

#include "Game.h"
#include "UtilSH.h"

SceneStage::SceneStage()
	:
	Scene((int)worldWidth, (int)worldHeight),
	player( { 0,0 }, { 0,0 }, 20, 20, 0 ),
	playerArea( { (float)sceneRect.left,  (float)sceneRect.right, worldWidth, worldHeight} )
{
}

void SceneStage::Update( float dt, Game& game )
{
	UpdateSceneRect( game );

	playerArea.Update( dt, *this );
	player.Update( dt, *this );
}

void SceneStage::Draw( HDC hdc )
{
	Surface::DrawRect( hdc, Gdiplus::Color( 255, 255, 0, 255 ), worldBorderThick,
		{ sceneRect.left - worldBorderThick * 0.5f,
		sceneRect.top - worldBorderThick * 0.5f,
		worldWidth + worldBorderThick,
		worldHeight + worldBorderThick }
	);
	Surface::DrawImageNonChroma( hdc, pBackImage.get(), sceneTopLeft, sceneBottomRight, { 0,0 }, imageEnd );
	
	playerArea.Draw(hdc);
	player.Draw( hdc );
}