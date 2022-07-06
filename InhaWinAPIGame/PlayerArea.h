#pragma once

#include "Actor.h"

class PlayerArea : public Actor
{
public:
	PlayerArea();

	void Update( float dt, class Scene& scene ) override;
	void Draw( HDC hdc )override;
private:
	std::shared_ptr<Gdiplus::Image> pImage;
};