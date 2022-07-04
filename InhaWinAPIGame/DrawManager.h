#pragma once

#include "framework.h"
#include <vector>
#include <ObjIdl.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")

//#include <functional>
#include "Bullet.h"
#include "Surface.h"


class DrawManager
{
public:
	void Update(float dt)
	{
		pos.y += 100 * dt;
	}

	template<typename F>
	void DrawMain( HDC hdc, const RECT& clientRECT, F drawFunc )
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

		/*Surface a;
		a.DrawString( hMemDC, L"Hello", pos, {255,255,0,0} );*/
		drawFunc(hMemDC);

		BitBlt( hdc, 0, 0, clientRECT.right, clientRECT.bottom, hMemDC, 0, 0, SRCCOPY );
		SelectObject( hMemDC, hOldBitmap );
		DeleteObject( hMemDC );
	}


private:
	Vec2<float> pos = {0,0};
	HBITMAP hDoubleBufferImage = nullptr;
};