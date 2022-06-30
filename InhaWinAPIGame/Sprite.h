#pragma once

#include "framework.h"
#include "Vec2.h"
#include <string>

#pragma comment(lib, "msimg32.lib")

class Sprite
{
public:
	enum class Type
	{
		NonChroma,
		Chroma
	};
public:
	Sprite( const std::wstring& filename, Type type, COLORREF chroma = RGB( 255, 0, 255 ) )
		:
		filename( filename ),
		type( type ),
		chroma( chroma )
	{
		CreateSprite();
		drawSize.x = bitmap.bmWidth;
		drawSize.y = bitmap.bmHeight;
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

	void UpdateSprite( const Vec2<int>& drawPos, const Vec2<int>& destSize, const Vec2<int>& srcPos, const Vec2<int>& srcSize )
	{
		drawStartPos = drawPos;
		drawSize = destSize;
		imageStartPos = srcPos;
		imageSize = srcSize;
	}
	void UpdateDrawPos(const Vec2<int>& pos)
	{
		drawStartPos = pos;
	}
	void UpdateDrawSize( const Vec2<int>& size )
	{
		drawSize = size;
	}
	void UpdateSrcImagePos( const Vec2<int>& pos )
	{
		imageStartPos = pos;
	}
	void UpdateSrcImageSize( const Vec2<int>& size )
	{
		imageSize = size;
	}

	void DrawSprite( HDC hdc, HDC hdcSrc )
	{
		DrawSprite( hdc, drawStartPos, drawSize.x, drawSize.y, hdcSrc, imageStartPos, imageSize.x, imageSize.y );
	}

	void DrawSprite( HDC hdc, const Vec2<int>& pos, int wDest, int hDest,
		HDC hdcSrc, const Vec2<int>& imgPos, int wSrc, int hSrc ) const
	{
		DrawSprite( hdc, pos.x, pos.y, wDest, hDest, hdcSrc, imgPos.x, imgPos.y, wSrc, hSrc );
	}

	void DrawSprite( HDC hdc, int xOriginDest, int yOriginDest, int wDest, int hDest,
		HDC hdcSrc, int xOriginSrc, int yOriginSrc, int wSrc, int hSrc ) const
	{
		switch ( type )
		{
			case Sprite::Type::NonChroma:
			{
				BitBlt( hdc, xOriginDest, yOriginDest, wDest, hDest, hdcSrc, xOriginSrc, yOriginSrc, SRCCOPY );
			}
			break;

			case Sprite::Type::Chroma:
			{
				TransparentBlt( hdc, xOriginDest, yOriginDest, wDest, hDest, hdcSrc, xOriginSrc, yOriginSrc, wSrc, hSrc, chroma );
			}
			break;
		}
	}

	void DeleteSprite()
	{
		DeleteObject( hBitmap );
	}

	HBITMAP GetHBITMAP() const
	{
		return hBitmap;
	}
	void SetDrawSize( int x, int y )
	{
		drawSize.x = x;
		drawSize.y = y;
	}
	void SetDrawSize( const Vec2<int>& size )
	{
		drawSize = size;
	}

private:
	std::wstring filename;
	HBITMAP hBitmap;
	BITMAP bitmap;

	Vec2<int> drawStartPos;
	Vec2<int> drawSize;
	Vec2<int> imageStartPos;
	Vec2<int> imageSize;

	Type type;
	COLORREF chroma;

};