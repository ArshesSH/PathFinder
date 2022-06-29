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
		CreateImage();
	}
	~Sprite()
	{
		DeleteObject( hBitmap );
	}
	void CreateImage()
	{
		hBitmap = (HBITMAP)LoadImage( NULL, filename.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION );
		GetObject( hBitmap, sizeof( BITMAP ), &bitmap );
	}
private:
	std::wstring filename;
	HBITMAP hBitmap;
	BITMAP bitmap;
};