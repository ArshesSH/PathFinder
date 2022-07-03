#pragma once

#include "framework.h"
#include <vector>
#include <ObjIdl.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")

#include "Surface.h"


class DrawManager
{
public:
	void Update(float dt)
	{
		testpos.y += 100 * dt;
	}

	void DrawMain( HDC hdc, const RECT& clientRECT )
	{
		HDC hMemDC;
		HBITMAP hOldBitmap;

		hMemDC = CreateCompatibleDC( hdc );
		if ( hDoubleBufferImage == nullptr )
		{
			// Create Bitmap Image for Double buffering
			hDoubleBufferImage = CreateCompatibleBitmap( hdc, clientRECT.right, clientRECT.bottom );
		}

		hOldBitmap = (HBITMAP)SelectObject( hMemDC, hDoubleBufferImage );

		FillRect( hMemDC, &clientRECT, (HBRUSH)GetStockObject( WHITE_BRUSH ) );

		Surface a;
		a.DrawString( hMemDC, L"hello", testpos, Gdiplus::Color( 255, 255, 0, 0 ) );

		BitBlt( hdc, 0, 0, clientRECT.right, clientRECT.bottom, hMemDC, 0, 0, SRCCOPY );
		SelectObject( hMemDC, hOldBitmap );
		DeleteObject( hMemDC );
	}


private:
	HBITMAP hDoubleBufferImage;
	Vec2<float> testpos = { 0,0 };
};