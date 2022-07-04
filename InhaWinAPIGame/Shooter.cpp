#include "Shooter.h"

#include "MathSH.h"

Shooter::Shooter( const std::wstring& imageName, const Vec2<float>& size )
	:
	Actor( imageName ),
	size( size )
{
}

Shooter::Shooter( const std::wstring& imageName, const Vec2<float>& center, const Vec2<float>& size, const Vec2<float> rotateCenter )
	:
	Actor( imageName ),
	center(center),
	size(size),
	rotateCenter(rotateCenter)
{

}

void Shooter::Update( float dt, const Scene& scene )
{
	angle = MathSH::WrapAngle( angle );
	
	const Vec2<float> topPos = { center.x, center.y - size.y };
	shootPos = (topPos - rotateCenter).Rotate( angle * MathSH::PI / 180.0f ) + rotateCenter;
	
	KbdInput( dt );
}

void Shooter::Draw( HDC hdc )
{
	surface.DrawImageChroma( hdc, pImage.get(), {center.x - size.x, center.y - size.y},
		{ center.x + size.x, center.y + size.y }, { 0,0 }, imageEnd, rotateCenter, angle );

	// Debug
	std::wstring angleDebugStr = L"angle : " + std::to_wstring( angle );
	surface.DrawString( hdc, angleDebugStr, { 0,40 }, Gdiplus::Color( 255, 255, 0, 0 ) );
	std::wstring shootPosStr = L"shootPos : " + std::to_wstring( shootPos.x ) + L", " + std::to_wstring( shootPos.y );
	surface.DrawString( hdc, shootPosStr, { 0,60 }, Gdiplus::Color( 255, 255, 0, 0 ) );
}

void Shooter::SetCenter( const Vec2<float>& v )
{
	center = v;
}

void Shooter::SetRotateCenter( const Vec2<float>& v )
{
	rotateCenter = v;
}
