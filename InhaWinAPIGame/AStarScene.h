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
	static constexpr int worldWidth = 1000;
	static constexpr int worldHeight = 800;
	static constexpr int tileSize = 50;

	TileMap map;
};