#pragma once

#include "DynamicActor.h"

#include <vector>
#include "PlayerArea.h"

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
	enum class MoveState
	{
		Stop,
		Vertical,
		Horizontal
	};

public:
	PanicPlayer( const Vec2<float> pos, const Vec2<float> vel, float width, float height, int id );

	void Update( float dt, class Scene& scene ) override;
	void Draw( Gdiplus::Graphics& gfx ) override;

private:
	void KbdInput(float dt);
	void MoveToRelativeCoord( const Vec2<float> amount );
private:
	static constexpr wchar_t imageName[] = L"Images/awsom.bmp";

	const Vec2<float> dirLeft = { -1,0 };
	const Vec2<float> dirUp = { 0,-1 };
	const Vec2<float> dirRight = { 1, 0 };
	const Vec2<float> dirDown = { 0, 1 };

	MoveState movestate = MoveState::Stop;
	Vec2<float> dir;

	float speed = 100.0f;

	//temp
	Vec2<float> movedTopLeft;
	Vec2<float> movedBottomRight;
};