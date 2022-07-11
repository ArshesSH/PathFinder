#pragma once

#include "Actor.h"

#include <vector>
#include <list>

class PlayerArea : public Actor
{
public:
	PlayerArea( const std::vector<Gdiplus::PointF>& vertices );
	PlayerArea( const Gdiplus::RectF& rect );

	void Update( float dt, class Scene& scene ) override;
	void Draw( Gdiplus::Graphics& gfx )override;
	void MoveToRelativeCoord( const Vec2<float>& amount );
	void GetLineFromIndices( std::pair<Gdiplus::PointF, Gdiplus::PointF>& line , const std::pair<int, int>& indices );
private:

private:
	const Gdiplus::Color color{ 255, 0, 255, 0 };
	std::vector<Gdiplus::PointF> vertices;
	std::vector<Gdiplus::PointF> drawVertices;
};