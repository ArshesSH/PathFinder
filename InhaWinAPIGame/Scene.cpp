#include "Scene.h"

#include "Game.h"

void Scene::UpdateSceneRect( Game& game )
{
	sceneTopLeft = { (game.screenRect.right - sceneWidth) * 0.5f, (game.screenRect.bottom - sceneHeight) * 0.5f };
	sceneBottomRight = { sceneTopLeft.x + sceneWidth, sceneTopLeft.y + sceneHeight };
	sceneRect = { (long)sceneTopLeft.x, (long)sceneTopLeft.y, (long)sceneBottomRight.x, (long)sceneBottomRight.y };
}
