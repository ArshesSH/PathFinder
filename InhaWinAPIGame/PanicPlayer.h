#pragma once

#include "Actor.h"

#include <vector>
#include "Rect.h"
#include "PlayerArea.h"

class PanicPlayer : public Actor
{
public:
	class MoveRecord
	{

	public:
		std::vector<Vec2<int>> pos;
		std::vector<Vec2<int>> dir;
	};

public:
	enum class MoveMode
	{
		Edge,
		OutSide
	};

public:
	PanicPlayer( const Vec2<int> pos, int width, int height );

	void Update( float dt, class Scene& scene ) override;
	void Draw( Gdiplus::Graphics& gfx ) override;
	void ControlPlayer( float dt, PlayerArea& area );

private:
	void MoveObjectToRelativeCoord( const Vec2<int> amount );
	void MovePos( float dt, const Vec2<int>& dir, PlayerArea& area );
private:
	static constexpr wchar_t imageName[] = L"Images/awsom.bmp";
	std::shared_ptr<Gdiplus::Image> pImage;
	Vec2<int> imageEnd = { pImage->GetWidth(), pImage->GetHeight() };

	const Vec2<int> dirLeft = { -1,0 };
	const Vec2<int> dirUp = { 0,-1 };
	const Vec2<int> dirRight = { 1, 0 };
	const Vec2<int> dirDown = { 0, 1 };

	Vec2<int> dir;
	int speed = 10;
	Rect<int> collisionRect;

	MoveMode moveMode = MoveMode::Edge;
	std::pair<int, int> curLineIndices = {0,1};

	Vec2<int> relativeTopLeft;
	Vec2<int> relativeBottomRight;

	//Debug
	std::pair<Gdiplus::Point, Gdiplus::Point> curVertices;
};