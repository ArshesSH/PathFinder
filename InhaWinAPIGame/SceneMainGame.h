
#pragma once

#include "Scene.h"
#include "Arrow.h"


class SceneMainGame : public Scene
{
public:
	void Update( float dt, const class Game& game ) override;
	void Draw( HDC hdc ) override;
private:
	static constexpr float arrowGenXPadding = 10.0f;
	static constexpr float arrowSpeed = 100.0f;
	static constexpr float arrowWidth = 20.0f;
	static constexpr float arrowHeight = 100.0f;
	std::vector<Arrow> arrows;
	float time = 0.0f;
	float arrowGenTime = 2.0f;
};