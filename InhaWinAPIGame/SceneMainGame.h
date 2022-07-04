
#pragma once

#include "Scene.h"
#include "Shooter.h"
#include "Arrow.h"


class SceneMainGame : public Scene
{
public:
	SceneMainGame();

	void Update( float dt, const class Game& game ) override;
	void Draw( HDC hdc ) override;
private:
	// Arrow Setting
	static constexpr float arrowGenXPadding = 10.0f;
	static constexpr float arrowSpeed = 100.0f;
	static constexpr float arrowWidth = 10.0f;
	static constexpr float arrowHeight = 50.0f;

	// Shooter Setting
	static constexpr float shooterImageWidth = 20.0f;
	static constexpr float shooterImageHeight = 50.0f;
	static constexpr float shooterImageDistFromRotate = 20.0f;

	// World
	static constexpr float worldWidth = 1280.0f;
	static constexpr float worldHeight = 720.0f;
	static constexpr float halfWidth = worldWidth / 2.0f;
	static constexpr float halfHeight = worldHeight / 2.0f;
	Gdiplus::RectF worldRect;

	// Objects
	Shooter shooter;
	std::vector<Arrow> arrows;


	float time = 0.0f;
	float arrowGenTime = 2.0f;
};