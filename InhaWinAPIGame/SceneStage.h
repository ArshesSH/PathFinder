#pragma once

#include "Scene.h"

#include "Vec2.h"
#include "Surface.h"
#include "PanicPlayer.h"
#include "PlayerArea.h"

class SceneStage : public Scene
{
public:
	SceneStage();
	
	void Update( float dt, class Game& game ) override;
	void Draw( HDC hdc ) override;

private:
	static constexpr float worldWidth = 700.0f;
	static constexpr float worldHeight = 960.0f;
	static constexpr float worldBorderThick = 20.0f;

	std::shared_ptr<Gdiplus::Image> pBackImage =  ImageCodex::Retrieve( L"Images/¼öÁö.bmp");
	Vec2<int> imageEnd = { pBackImage->GetWidth(), pBackImage->GetHeight() };
	
	// PlayerArea Setting
	static constexpr float areaPadding = worldBorderThick * 0.5f;
	PlayerArea playerArea;
	
	// Player Setting
	PanicPlayer player;

};