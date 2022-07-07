#pragma once

#include "Scene.h"

#include "Vec2.h"
#include "Surface.h"
#include "PanicPlayer.h"
#include <list>

class SceneStage : public Scene
{
public:
	SceneStage();
	
	void Update( float dt, class Game& game ) override;
	void Draw( HDC hdc ) override;
	RECT GetSceneRECT() const override;

private:
	void UpdateWorldRect( class Game& game );

private:
	static constexpr float worldWidth = 700.0f;
	static constexpr float worldHeight = 960.0f;
	static constexpr float worldBorderThick = 20.0f;

	// World Setting
	Gdiplus::RectF worldRect;
	Gdiplus::RectF lastRect = worldRect;
	Vec2<float> worldTopLeft;
	Vec2<float> worldBottomRight;
	Vec2<float> worldChangPosAmount;
	Surface surf;
	std::shared_ptr<Gdiplus::Image> pBackImage =  ImageCodex::Retrieve( L"Images/¼öÁö.bmp");
	Vec2<int> imageEnd = { pBackImage->GetWidth(), pBackImage->GetHeight() };
	
	// Player Setting
	PanicPlayer player;

	std::vector<Gdiplus::PointF> points;
	
};