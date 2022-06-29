#pragma once

#include <vector>
#include "Sprite.h"

class SpriteManager
{
public:
	SpriteManager() = default;
	Sprite operator[]( size_t pos )
	{
		return spriteList[pos];
	}
	
	std::vector<Sprite> GetSpriteList()
	{
		return spriteList;
	}
	
	void AddSprite()
	{
	}

private:
	std::vector<Sprite> spriteList;
};