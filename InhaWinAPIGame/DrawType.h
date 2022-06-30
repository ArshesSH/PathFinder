#pragma once

#include "framework.h"
#include "Vec2.h"

namespace DrawType
{
	class NonChroma
	{
	public:
		void operator()(HDC hdc, int x, int y, int cx, int cy,
			HDC hdcSrc, int x1, int y1, int, int )const
		{
			BitBlt( hdc, x, y, cx, cy, hdcSrc, x1, y1, SRCCOPY );
		}
	};
	
	class Chroma
	{
	public:
		Chroma( COLORREF chroma )
			:
			chroma( chroma )
		{}
		void operator()(
			HDC hdc, int xOriginDest, int yOriginDest, int wDest, int hDest,
			HDC hdcSrc, int xOriginSrc, int yOriginSrc, int wSrc, int hSrc) const
		{
			TransparentBlt( hdc, xOriginDest, yOriginDest, wDest, hDest, hdcSrc, xOriginSrc, yOriginSrc, wSrc, hSrc, chroma );
		}
	private:
		COLORREF chroma;
	};
}