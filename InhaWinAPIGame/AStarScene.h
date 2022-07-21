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
	static constexpr int tileSize = 50;
	static constexpr int tileRow = 10;
	static constexpr int tileCol = 8;
	TileMap map;
};