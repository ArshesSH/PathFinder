#include "PlayerArea.h"

PlayerArea::PlayerArea(const std::vector<Gdiplus::PointF>& vertices)
	:
	vertices(vertices),
	drawVertices(vertices)
{
}

PlayerArea::PlayerArea( const Gdiplus::RectF& rect )
{
	const float left = rect.GetLeft();
	const float top = rect.GetTop();
	const float right = rect.GetRight();
	const float bottom = rect.GetBottom();

	vertices.emplace_back( left, top );
	vertices.emplace_back( right, top );
	vertices.emplace_back( right, bottom );
	vertices.emplace_back( left, bottom );

	drawVertices = vertices;
}

void PlayerArea::Update( float dt, Scene& scene )
{
}

void PlayerArea::Draw( HDC hdc )
{
	surf.DrawFillPolygon( hdc, color, drawVertices[0], drawVertices.size() );
}

void PlayerArea::MoveToRelativeCoord( const Vec2<float> amount )
{
	drawVertices = vertices;
	for (auto i = 0; i < vertices.size(); ++i)
	{
		drawVertices[i] = vertices[i] + Gdiplus::PointF( amount.x, amount.y );
	}
}
