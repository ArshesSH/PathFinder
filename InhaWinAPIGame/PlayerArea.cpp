#include "PlayerArea.h"

#include <cassert>
#include "Scene.h"

PlayerArea::PlayerArea(const std::vector<Gdiplus::Point>& vertices)
	:
	vertices(vertices),
	drawVertices(vertices)
{
}

PlayerArea::PlayerArea( const Gdiplus::Rect& rect )
{
	const int left = rect.GetLeft();
	const int top = rect.GetTop();
	const int right = rect.GetRight();
	const int bottom = rect.GetBottom();

	vertices.emplace_back( left, top );
	vertices.emplace_back( right, top );
	vertices.emplace_back( right, bottom );
	vertices.emplace_back( left, bottom );

	drawVertices = vertices;
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
	drawVertices = vertices;
	for (size_t i = 0; i < vertices.size(); ++i)
	{
		drawVertices[i] = vertices[i] + Gdiplus::Point( amount.x, amount.y );
	}
}

std::pair<Gdiplus::Point, Gdiplus::Point> PlayerArea::GetLineFromIndices( const std::pair<int, int>& indices ) const
{
	assert( indices.first >= 0 && indices.second < (int)vertices.size() );
	return { vertices[indices.first], vertices[indices.second] };
}
