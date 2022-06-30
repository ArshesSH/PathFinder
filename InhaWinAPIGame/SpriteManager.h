#pragma once

#include <vector>
#include "TemplateSingleton.h"
#include "Sprite.h"
#include "DrawType.h"

class SpriteManager : public TemplateSingleton<std::vector<Sprite>>
{
public:
	void AddSprite( const std::wstring& filename, Sprite::Type type, COLORREF chroma = RGB( 255, 0, 255 ) )
	{
		auto pSpriteList = GetInstance();
		pSpriteList->emplace_back( filename, type, chroma );
	}
	void AddSprite( const Sprite& sprite )
	{
		GetInstance()->push_back( sprite );
	}
	void DrawSprites( HDC hdc )
	{
		HDC hMemDC;
		HBITMAP hOldBitmap;
		HDC hComponentDC;
		HBITMAP hOldComponentBitmap;

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
			hComponentDC = CreateCompatibleDC( hMemDC );
			hOldComponentBitmap = (HBITMAP)SelectObject( hComponentDC, s.GetHBITMAP() );
			s.DrawSprite( hMemDC, hComponentDC );
			SelectObject( hComponentDC, hOldComponentBitmap );
			DeleteObject( hComponentDC );
		}

		BitBlt( hdc, 0, 0, clientRECT.right, clientRECT.bottom, hMemDC, 0, 0, SRCCOPY );
		SelectObject( hMemDC, hOldBitmap );
		DeleteObject( hMemDC );
	}
private:
	HBITMAP hDoubleBufferImage;
	RECT clientRECT;
};