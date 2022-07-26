#pragma once

#include "Scene.h"

#include "TileMap.h"
#include "PanicPlayer.h"

class AStarScene : public Scene
{
public:
	AStarScene();
	void Update( float dt, class Game& game ) override;
	void Draw( HDC hdc ) override;


	int GetHalfTileSize() const;

	void MovePlayer( float dt );

private:
	static constexpr int tileSize = 50;
	static constexpr int halfTileSize = tileSize / 2;
	static constexpr int tileRow = 14;
	static constexpr int tileCol = 14;
	static constexpr float searchDrawDelay = 0.001f;
	TileMap map;

	static constexpr int playerSize = 40;
	static constexpr int halfPlayerSize = playerSize / 2;
	PanicPlayer player;
	std::vector<Vec2<int>> route;
	bool isFindStart = false;
	float time = 0.0f;
};