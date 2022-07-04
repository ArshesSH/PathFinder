#include "Surface.h"

void Surface::DrawString( HDC hdc, const std::wstring& str, const Vec2<float> pos, Gdiplus::Color color, float fontSize, const std::wstring& fontType )
{
	using namespace Gdiplus;
	Graphics graphics( hdc );

	SolidBrush brush( color );
	FontFamily fontFamily( fontType.c_str() );
	Font font( &fontFamily, fontSize, FontStyleRegular, UnitPixel );
	PointF pointF( pos.x, pos.y );

	graphics.DrawString( str.c_str(), str.size(), &font, pointF, &brush );
}

void Surface::DrawRect( HDC hdc, Gdiplus::Color color, float penWidth, const Vec2<float>& topLeft, float width, float height)
{
	using namespace Gdiplus;
	Graphics graphics( hdc );

	Pen pen( color, penWidth );
	Gdiplus::RectF r( { topLeft.x, topLeft.y }, { width, height } );
	graphics.DrawRectangle( &pen, r );
}

void Surface::DrawRect( HDC hdc, Gdiplus::Color color, float penWidth, Gdiplus::RectF rectF )
{
	using namespace Gdiplus;
	Graphics graphics( hdc );

	Pen pen( color, penWidth );
	graphics.DrawRectangle( &pen, rectF );
}

void Surface::DrawImageNonChroma( HDC hdc, Gdiplus::Image* image, const Vec2<float>& topLeft, const Vec2<float>& bottomRight, const Vec2<int> imageStart, const Vec2<int> imageEnd )
{
	using namespace Gdiplus;
	Graphics graphics( hdc );

	const Gdiplus::Rect r( (int)topLeft.x, (int)topLeft.y, (int)(bottomRight.x - topLeft.x), (int)(bottomRight.y - topLeft.y) );
	graphics.DrawImage( image, r, imageStart.x, imageStart.y, imageEnd.x, imageEnd.y, UnitPixel );
}

void Surface::DrawImageNonChroma( HDC hdc, Gdiplus::Image* image, const Vec2<float>& topLeft, const Vec2<float>& bottomRight, const Vec2<int> imageStart, const Vec2<int> imageEnd, const Vec2<float> rotateCenter, float angle )
{
	using namespace Gdiplus;
	Graphics graphics( hdc );

	Matrix mat;
	mat.RotateAt( angle, { rotateCenter.x, rotateCenter.y } );
	graphics.SetTransform( &mat );

	const Gdiplus::Rect r( (int)topLeft.x, (int)topLeft.y, (int)(bottomRight.x - topLeft.x), (int)(bottomRight.y - topLeft.y) );
	graphics.DrawImage( image, r, imageStart.x, imageStart.y, imageEnd.x, imageEnd.y, UnitPixel );

	mat.Reset();
	graphics.SetTransform( &mat );
}

void Surface::DrawImageChroma( HDC hdc, Gdiplus::Image* image, const Vec2<float>& topLeft, const Vec2<float>& bottomRight, const Vec2<int> imageStart, const Vec2<int> imageEnd, int angle, Gdiplus::Color lowChroma, Gdiplus::Color highChroma )
{
	using namespace Gdiplus;
	Graphics graphics( hdc );

	ImageAttributes imgAttr;
	imgAttr.SetColorKey( lowChroma, highChroma );

	const Gdiplus::Rect r( (int)topLeft.x, (int)topLeft.y, (int)(bottomRight.x - topLeft.x), (int)(bottomRight.y - topLeft.y) );
	graphics.DrawImage( image, r, imageStart.x, imageStart.y, imageEnd.x, imageEnd.y, UnitPixel, &imgAttr );
}

void Surface::DrawImageChroma( HDC hdc, Gdiplus::Image* image, const Vec2<float>& topLeft, const Vec2<float>& bottomRight, const Vec2<int> imageStart, const Vec2<int> imageEnd, const Vec2<float> rotateCenter, float angle, Gdiplus::Color lowChroma, Gdiplus::Color highChroma )
{
	using namespace Gdiplus;
	Graphics graphics( hdc );

	Matrix mat;
	mat.RotateAt( angle, { rotateCenter.x, rotateCenter.y } );
	graphics.SetTransform( &mat );

	ImageAttributes imgAttr;
	imgAttr.SetColorKey( lowChroma, highChroma );

	const Gdiplus::Rect r( (int)topLeft.x, (int)topLeft.y, (int)(bottomRight.x - topLeft.x), (int)(bottomRight.y - topLeft.y) );
	graphics.DrawImage( image, r, imageStart.x, imageStart.y, imageEnd.x, imageEnd.y, UnitPixel, &imgAttr );

	mat.Reset();
	graphics.SetTransform( &mat );
}
