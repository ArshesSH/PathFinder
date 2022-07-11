#pragma once

#include "DynamicActor.h"

#include <vector>

class PanicPlayer : public DynamicActor
{
public:
	class MoveRecord
	{

	public:
		std::vector<Vec2<float>> pos;
		std::vector<Vec2<float>> dir;
	};

public:
	enum class MoveMode
	{
		Edge,
		OutSide
	};

public:
	PanicPlayer( const Vec2<float> pos, const Vec2<float> vel, float width, float height, int id );

	void Update( float dt, class Scene& scene ) override;
	void Draw( Gdiplus::Graphics& gfx ) override;

private:
	void KbdInput(float dt, Scene& scene);
	void MovePos( float dt, const Vec2<float>& dir, Scene& scene );
	void MoveObjectToRelativeCoord( const Vec2<float> amount );
	bool CanMove(const Vec2<float> nextPos, const Scene& scene ) const;
private:
	static constexpr wchar_t imageName[] = L"Images/awsom.bmp";

	const Vec2<float> dirLeft = { -1,0 };
	const Vec2<float> dirUp = { 0,-1 };
	const Vec2<float> dirRight = { 1, 0 };
	const Vec2<float> dirDown = { 0, 1 };

	Vec2<float> dir;
	float speed = 100.0f;
	MoveMode moveMode = MoveMode::Edge;

	std::pair<int, int> curLineIndex = { 0, 1 };

	Vec2<float> relativeTopLeft;
	Vec2<float> relativeBottomRight;
};