
#pragma once

#include "Scene.h"
#include "DrawManager.h"
#include "Arrow.h"
#include "UtilSH.h"
#include <memory>
#include <random>

class SceneMainGame : public Scene
{
public:
	void Update( float dt, RECT clientRect ) override
	{
		screenRect = clientRect;
		time += dt;
		if ( time >= arrowGenTime )
		{
			std::random_device rd;
			std::mt19937 rng( rd() );
			std::uniform_real_distribution<float> arrowXGen( arrowGenXPadding, (float)screenRect.right - arrowGenXPadding );
			arrows.emplace_back(
				Arrow( L"Images/awsom.bmp", Vec2<float>{ arrowXGen( rng ), 0.0f }, Vec2<float>{ 0.0f, arrowSpeed }, arrowWidth, arrowHeight, arrows.size() )
			);
			time = 0.0f;
		}

		for ( auto& arrow : arrows )
		{
			arrow.Update( dt, screenRect );
		}

		UtilSH::remove_erase_if( arrows,
			[]( const Arrow& arrow )
			{
				return arrow.ShouldDestroy();
			}
		);
	}
	void Draw( HDC hdc ) override
	{
		for ( auto& arrow : arrows )
		{
			arrow.Draw( hdc );
		}

		// debug
		std::wstring curArrowCountStr = L"Cur Arrows count : " + std::to_wstring(arrows.size());
		Surface a;
		a.DrawString( hdc, curArrowCountStr, { 300.0f,300.0f }, Gdiplus::Color(255,255,0,0) );
	}
private:
	static constexpr float arrowGenXPadding = 10.0f;
	static constexpr float arrowSpeed = 100.0f;
	static constexpr float arrowWidth = 20.0f;
	static constexpr float arrowHeight = 100.0f;
	RECT screenRect;
	std::vector<Arrow> arrows;
	float time = 0.0f;
	float arrowGenTime = 2.0f;
};