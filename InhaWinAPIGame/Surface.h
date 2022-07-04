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
	void DrawString( HDC hdc, const std::wstring& str, const Vec2<float> pos, Gdiplus::Color color, float fontSize = 24.0f, const std::wstring& fontType = L"Consolas" );

	void DrawImageNonChroma( HDC hdc, Gdiplus::Image* image, const Vec2<float>& topLeft, const Vec2<float>& bottomRight, const Vec2<int> imageStart, const Vec2<int> imageEnd );

	void DrawImageNonChroma( HDC hdc, Gdiplus::Image* image, const Vec2<float>& topLeft, const Vec2<float>& bottomRight,
		const Vec2<int> imageStart, const Vec2<int> imageEnd, const Vec2<float> rotateCenter, float angle );

	void DrawImageChroma( HDC hdc, Gdiplus::Image* image, const Vec2<float>& topLeft, const Vec2<float>& bottomRight,
		const Vec2<int> imageStart, const Vec2<int> imageEnd, int angle = 0,
		Gdiplus::Color lowChroma = { 245, 0, 245 }, Gdiplus::Color highChroma = { 255,10,255 } );

	void DrawImageChroma( HDC hdc, Gdiplus::Image* image, const Vec2<float>& topLeft, const Vec2<float>& bottomRight,
		const Vec2<int> imageStart, const Vec2<int> imageEnd, const Vec2<float> rotateCenter, float angle,
		Gdiplus::Color lowChroma = { 245, 0, 245 }, Gdiplus::Color highChroma = { 255,10,255 } );
private:
};

