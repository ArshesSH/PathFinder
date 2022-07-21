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
	static constexpr int tileRow = 14;
	static constexpr int tileCol = 14;
	TileMap map;
};