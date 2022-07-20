#pragma once

#include "Scene.h"

#include "TileMap.h"

class AStarScene : public Scene
{
public:
	AStarScene();
	void Update( float dt, class Game& game ) override;
	void Draw( HDC hdc ) override;

private:

private:
	static constexpr int worldWidth = 400;
	static constexpr int worldHeight = 400;
	static constexpr int tileSize = 40;


	TileMap map;
};