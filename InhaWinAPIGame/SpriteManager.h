#pragma once

#include <vector>
#include "TemplateSingleton.h"
#include "Sprite.h"

class SpriteManager : public TemplateSingleton<std::vector<Sprite>>
{
public:
	void AddSprite( const std::wstring& filename )
	{
		GetInstance()->emplace_back( filename );
	}
	void AddSprite( const Sprite& sprite )
	{
		GetInstance()->push_back( sprite );
	}
	void UpdateSpriteManager()
	{

	}
	void DrawSprites( HDC hdc, int x, int y )
	{
		HDC hMemDC;
		HBITMAP hOldBitmap;
		HDC hMemDC2;
		HBITMAP hOldBitmap2;

		hMemDC = CreateCompatibleDC( hdc );
		if ( hDoubleBufferImage == nullptr )
		{
			// Create Bitmap Image for Double buffering
			hDoubleBufferImage = CreateCompatibleBitmap( hdc, clientRECT.right, clientRECT.bottom );
		}
		
		hOldBitmap = (HBITMAP)SelectObject( hMemDC, hDoubleBufferImage );

		auto pSpriteList = GetInstance();
		for ( auto& s : *pSpriteList )
		{

		}
	}
private:
	HBITMAP hDoubleBufferImage;
	RECT clientRECT;
};