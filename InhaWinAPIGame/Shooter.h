#pragma once
#include "Actor.h"
class Shooter : public Actor 
{
public:
	Shooter(const std::wstring& imageName)
		:
		Actor( imageName )
	{}

	void Draw(HDC hdc) override
	{
		surface.DrawImageChroma( hdc, pImage.get(), topLeft, bottomRight, { 0,0 }, imageEnd, rotateCenter, angle );
	}
private:
	float angle;
	const Vec2<int> imageEnd = {200,400};
	const Vec2<float> topLeft;
	const Vec2<float> bottomRight;
	const Vec2<float> rotateCenter;
};

