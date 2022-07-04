#include "Arrow.h"

#include "Game.h"

Arrow::Arrow( const std::wstring& imagename, const Vec2<float>& pos, const Vec2<float>& vel, float width, float height, int id )
	:
	Actor( imagename ),
	rigidBody( PhysicsEntity::Type::Rect, pos, id, width, height, vel, 0.0f, 0.0f, 0 )
{}

void Arrow::Update( float dt, const Game& game )
{
	rigidBody.Update( dt );
	if ( CheckFloor( game.screenRect ) )
	{
		shouldDestroy = true;
	}
}

void Arrow::Draw( HDC hdc )
{
	surface.DrawImageChroma( hdc, pImage.get(), rigidBody.GetLeftTop(), rigidBody.GetRightBottom(), { 0,0 }, { 20,20 } );
}

inline bool Arrow::CheckFloor( RECT screenRect )
{
	const Vec2<float> topLeft( (float)screenRect.left, (float)screenRect.top );
	const Vec2<float> bottomRight( (float)screenRect.right, (float)screenRect.bottom );

	// Create Normalized Horizontal and Vertical Window Sized Vectors
	const Vec2<float> NormalizedHorizontal = Vec2<float>( bottomRight.x - topLeft.x, topLeft.y ).GetNormalized();
	const Vec2<float> NormalizedVertical = Vec2<float>( topLeft.x, bottomRight.y - topLeft.y ).GetNormalized();

	// Set Projection vals
	float minHorizon = INFINITY;
	float maxHorizon = -INFINITY;
	float minVertical = INFINITY;
	float maxVertical = -INFINITY;

	std::vector<Vec2<float>> vertices = rigidBody.GetVertices();

	for ( auto e : vertices )
	{
		// Check Horizontal
		const float pHorizon = e * NormalizedHorizontal;
		minHorizon = (std::min)(minHorizon, pHorizon);
		maxHorizon = (std::max)(maxHorizon, pHorizon);

		// Case Left Collision
		if ( minHorizon < topLeft.x )
		{
			return true;
		}
		// Case Right Collision
		else if ( bottomRight.x < maxHorizon )
		{
			return true;
		}

		// Check Vertical
		const float pVertical = e * NormalizedVertical;
		minVertical = (std::min)(minVertical, pVertical);
		maxVertical = (std::max)(maxVertical, pVertical);

		// Case Top Collision
		//if ( minVertical < topLeft.y )
		//{
		//	return true;
		//}
		// Case Bottom Collision
		if ( bottomRight.y < maxVertical )
		{
			return true;
		}
	}
	return false;
}
