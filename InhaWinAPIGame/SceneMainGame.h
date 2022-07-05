
#pragma once

#include "Scene.h"
#include "Shooter.h"
#include "Arrow.h"
#include "Bullet.h"
#include "Brick.h"

class SceneMainGame : public Scene
{
public:
	SceneMainGame();

	void Update( float dt, class Game& game ) override;
	void Draw( HDC hdc ) override;
	RECT GetSceneRECT() const override;

private:
	void UpdateWorldRect( class Game& game );
	void UpdateShooter(float dt);
	void GenerateBullet();
	void UpdateBullet( float dt, class Game& game );
	void GenerateArrows();
	void UpdateArrows( float dt, class Game& game );
	void UpdateBricks( float dt, class Game& game );
	void RefreshLastRect( class Game& game );
	void DestroyObjects();

private:
	// Arrow Setting
	static constexpr float arrowGenXPadding = 10.0f;
	static constexpr float arrowSpeed = 100.0f;
	static constexpr float arrowWidth = 30.0f;
	static constexpr float arrowHeight = 50.0f;
	static constexpr float arrowGenTimeMax = 2.0f;
	static constexpr float arrowGenTimeMin = 0.5f;

	// Shooter Setting
	static constexpr float shooterImageWidth = 20.0f;
	static constexpr float shooterImageHeight = 50.0f;
	static constexpr float shooterImageDistFromRotate = 20.0f;
	static constexpr float shooterFrameWidth = 50.0f;
	static constexpr float shooterFrameHeight = 50.0f;

	// Bullet Setting
	static constexpr float bulletWidth = 20.0f;
	static constexpr float bulletHeight = 20.0f;
	static constexpr float bulletGenTimeLimit = 0.5f;
	static constexpr float bulletSpeed = 300.0f;

	// World
	static constexpr float worldWidth = 1280.0f;
	static constexpr float worldHeight = 720.0f;
	static constexpr float halfWidth = worldWidth * 0.5f;
	static constexpr float halfHeight = worldHeight * 0.5f;

	// Brick Setting
	static constexpr float brickWidth = worldWidth / 6.0f;
	static constexpr float brickHalfWidth = brickWidth * 0.5f;
	static constexpr float brickheight = 20.0f;
	static constexpr float brickPosY = worldHeight - 50.0f;

	Gdiplus::RectF worldRect;
	Gdiplus::RectF lastRect = worldRect;
	Vec2<float> worldChangPosAmount;
	Surface surf;
	std::wstring playerName;

	// Objects
	Shooter shooter;
	std::vector<Arrow> arrows;
	std::vector<Bullet> bullets;
	std::vector<Brick> bricks;

	float time = 0.0f;
	float bulletGenTime = bulletGenTimeLimit;
	float arrowGenTime = arrowGenTimeMax;
	bool isStart = false;
};