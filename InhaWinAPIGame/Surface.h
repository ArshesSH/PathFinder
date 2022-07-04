#pragma once

#include "framework.h"
#include <ObjIdl.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
#include <string>
#include <memory>
#include "Vec2.h"
#include "GeometricObject.h"

class Surface
{
public:

	void DrawString( HDC hdc, const std::wstring& str, const Vec2<float> pos, Gdiplus::Color color, float fontSize = 24.0f, const std::wstring& fontType = L"Consolas" )
	{
		using namespace Gdiplus;
		Graphics graphics( hdc );

		SolidBrush brush( color );
		FontFamily fontFamily( fontType.c_str() );
		Font font( &fontFamily, fontSize, FontStyleRegular, UnitPixel );
		PointF pointF( pos.x, pos.y );

		graphics.DrawString( str.c_str(), str.size(), &font, pointF, &brush );
	}

	void DrawImageNonChroma(HDC hdc, Gdiplus::Image* image, const Vec2<float>& topLeft, const Vec2<float>& bottomRight, const Vec2<int> imageStart, const Vec2<int> imageEnd)
	{
		using namespace Gdiplus;
		Graphics graphics( hdc );

		const Gdiplus::Rect r( (int)topLeft.x, (int)topLeft.y, (int)(bottomRight.x - topLeft.x), (int)(bottomRight.y - topLeft.y) );
		graphics.DrawImage( image, r, imageStart.x, imageStart.y, imageEnd.x, imageEnd.y, UnitPixel );
	}

	void DrawImageNonChroma( HDC hdc, Gdiplus::Image* image, const Vec2<float>& topLeft, const Vec2<float>& bottomRight,
		const Vec2<int> imageStart, const Vec2<int> imageEnd, const Vec2<int> rotateCenter, float angle )
	{
		using namespace Gdiplus;
		Graphics graphics( hdc );

		Matrix mat;
		mat.RotateAt( angle, { (float)rotateCenter.x, (float)rotateCenter.y } );
		graphics.SetTransform( &mat );

		const Gdiplus::Rect r( (int)topLeft.x, (int)topLeft.y, (int)(bottomRight.x - topLeft.x), (int)(bottomRight.y - topLeft.y) );
		graphics.DrawImage( image, r, imageStart.x, imageStart.y, imageEnd.x, imageEnd.y, UnitPixel );

		mat.Reset();
		graphics.SetTransform( &mat );
	}


	void DrawImageChroma( HDC hdc, Gdiplus::Image* image, const Vec2<float>& topLeft, const Vec2<float>& bottomRight,
		const Vec2<int> imageStart, const Vec2<int> imageEnd, int angle = 0,
		Gdiplus::Color lowChroma = { 245, 0, 245 }, Gdiplus::Color highChroma = {255,10,255} )
	{
		using namespace Gdiplus;
		Graphics graphics( hdc );

		ImageAttributes imgAttr;
		imgAttr.SetColorKey( lowChroma, highChroma );

		const Gdiplus::Rect r( (int)topLeft.x, (int)topLeft.y, (int)(bottomRight.x - topLeft.x), (int)(bottomRight.y - topLeft.y) );
		graphics.DrawImage( image, r, imageStart.x, imageStart.y, imageEnd.x, imageEnd.y, UnitPixel, &imgAttr );
	}
	void DrawImageChroma( HDC hdc, Gdiplus::Image* image, const Vec2<float>& topLeft, const Vec2<float>& bottomRight,
		const Vec2<int> imageStart, const Vec2<int> imageEnd, const Vec2<int> rotateCenter, float angle,
		Gdiplus::Color lowChroma = { 245, 0, 245 }, Gdiplus::Color highChroma = { 255,10,255 } )
	{
		using namespace Gdiplus;
		Graphics graphics( hdc );

		Matrix mat;
		mat.RotateAt( angle, { (float)rotateCenter.x, (float)rotateCenter.y } );
		graphics.SetTransform( &mat );

		ImageAttributes imgAttr;
		imgAttr.SetColorKey( lowChroma, highChroma );

		const Gdiplus::Rect r( (int)topLeft.x, (int)topLeft.y, (int)(bottomRight.x - topLeft.x), (int)(bottomRight.y - topLeft.y) );
		graphics.DrawImage( image, r, imageStart.x, imageStart.y, imageEnd.x, imageEnd.y, UnitPixel, &imgAttr );

		mat.Reset();
		graphics.SetTransform( &mat );
	}
private:
};

