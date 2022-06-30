#pragma once

#include "framework.h"
#include <string>

#pragma comment(lib, "msimg32.lib")

class Sprite
{
public:
	Sprite(const std::wstring& filename)
		:
		filename(filename)
	{
		CreateSprite();
	}
	~Sprite()
	{
		DeleteObject( hBitmap );
	}
	void CreateSprite(int x = 0, int y = 0)
	{
		hBitmap = (HBITMAP)LoadImage( NULL, filename.c_str(), IMAGE_BITMAP, x, y, LR_LOADFROMFILE | LR_CREATEDIBSECTION );
		GetObject( hBitmap, sizeof( BITMAP ), &bitmap );
	}

private:
	std::wstring filename;
	HBITMAP hBitmap;
	BITMAP bitmap;


};