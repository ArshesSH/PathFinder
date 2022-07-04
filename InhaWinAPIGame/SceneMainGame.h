
#pragma once

#include "Scene.h"
#include "DrawManager.h"
#include "Arrow.h"
#include <random>

class SceneMainGame : public Scene
{
public:
	SceneMainGame() {}
	void Update( float dt, RECT clientRect ) override
	{
		screenRect = clientRect;
		time += dt;
		if ( time >= 1.0f )
		{
			std::random_device rd;
			std::mt19937 rng( rd() );
			std::uniform_real_distribution<float> arrowXGen( arrowGenXPadding, (float)screenRect.right - arrowGenXPadding );
			//arrows.push_back( Arrow( { arrowXGen( rng ), 0.0f },{ 0.0f, arrowSpeed }, arrowWidth, arrowHeight, arrows.size() ) );
			//arrows.emplace_back( L"Images/awsom.bmp", Vec2<float>{ arrowXGen(rng), 0.0f }, Vec2<float>{ 0.0f, arrowSpeed }, arrowWidth, arrowHeight, arrows.size());
		}
	}
	void Draw( HDC hdc ) override
	{
		drawManager.DrawMain( hdc, screenRect,
			[this]( HDC hdc )
			{
				//for ( auto& arrow : arrows )
				//{
				//	arrow.Draw( hdc );
				//}
			}
		);
	}
private:
	static constexpr float arrowGenXPadding = 10.0f;
	static constexpr float arrowSpeed = 100.0f;
	static constexpr float arrowWidth = 20.0f;
	static constexpr float arrowHeight = 100.0f;
	RECT screenRect;
	DrawManager drawManager;
	std::vector<Arrow> arrows;
	float time = 0.0f;
};