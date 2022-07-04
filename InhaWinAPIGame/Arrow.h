#pragma once

#include "Actor.h"

class Arrow : public Actor
{
public:
	Arrow( const std::wstring& imagename, const Vec2<float>& pos, const Vec2<float>& vel, float width, float height, int id)
		:
		Actor(imagename, pos, vel, width, height, PhysicsEntity::Type::Rect, id)
	{}
	~Arrow() {}
	Arrow( const Arrow& ) = default;
	Arrow( Arrow&& ) = default;
	Arrow& operator=( const Arrow& ) = default;
	Arrow& operator=( Arrow&& ) = default;

	void Update( float dt, RECT screenRect ) override
	{
		rigidBody.Update( dt );
		if ( CheckFloor(screenRect) )
		{
			shouldDestroy = true;
		}
	}
	void Draw( HDC hdc ) override
	{
		surface.DrawImageChroma( hdc, pImage.get(), rigidBody.GetLeftTop(), rigidBody.GetRightBottom(), { 0,0 }, imageEnd );
	}

private:
	bool CheckFloor( RECT screenRect )
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

private:
	const Vec2<int> imageEnd = { pImage->GetWidth(), pImage->GetHeight() };
};