#pragma once

#include "framework.h"
#include <ObjIdl.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
#include <string>
#include <memory>
#include "Codex.h"
#include "Vec2.h"

class Surface
{
public:
	void DrawString( HDC hdc, const std::wstring& str, const Vec2<float> pos, Gdiplus::Color color, int fontSize = 24, const std::wstring& fontType = L"Consolas" )
	{
		using namespace Gdiplus;

		Graphics graphics( hdc );

		SolidBrush brush( color );
		FontFamily fontFamily( fontType.c_str() );
		Font font( &fontFamily, fontSize, FontStyleRegular, UnitPixel );
		PointF pointF( pos.x, pos.y );

		graphics.DrawString( str.c_str(), str.size(), &font, pointF, &brush );
	}
	
private:
};

