#include "PlayerArea.h"

#include <cassert>
#include "Scene.h"

PlayerArea::PlayerArea(const std::vector<Gdiplus::Point>& vertices)
	:
	polygon(vertices),
	drawVertices(vertices)
{
}

PlayerArea::PlayerArea( const Gdiplus::Rect& rect )
{
	const int left = rect.GetLeft();
	const int top = rect.GetTop();
	const int right = rect.GetRight();
	const int bottom = rect.GetBottom();

	polygon.vertices.emplace_back( left, top );
	polygon.vertices.emplace_back( right, top );
	polygon.vertices.emplace_back( right, bottom );
	polygon.vertices.emplace_back( left, bottom );

	drawVertices = polygon.vertices;
}

void PlayerArea::Update( float dt, Scene& scene )
{
	MoveToRelativeCoord( (Vec2<int>)scene.GetSceneTopLeft() );
}

void PlayerArea::Draw( Gdiplus::Graphics& gfx )
{
	Surface::DrawFillPolygon( gfx, color, drawVertices[0], (int)drawVertices.size() );
}

void PlayerArea::MoveToRelativeCoord( const Vec2<int>& amount )
{
	drawVertices = polygon.vertices;
	for (size_t i = 0; i < polygon.size(); ++i)
	{
		drawVertices[i] = polygon.vertices[i] + Gdiplus::Point( amount.x, amount.y );
	}
}

