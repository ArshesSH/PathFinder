#pragma once

#include "Actor.h"

#include <vector>
#include "MathSH.h"
#include "Polygon.h"

class PlayerArea : public Actor
{
public:
	PlayerArea( const std::vector<Gdiplus::Point>& vertices );
	PlayerArea( const Gdiplus::Rect& rect );

	void Update( float dt, class Scene& scene ) override;
	void Draw( Gdiplus::Graphics& gfx )override;
	void MoveToRelativeCoord( const Vec2<int>& amount );

public:
	ArshesSH::Polygon<Gdiplus::Point> polygon;

private:
	const Gdiplus::Color color{ 255, 0, 255, 0 };
	std::vector<Gdiplus::Point> drawVertices;
};