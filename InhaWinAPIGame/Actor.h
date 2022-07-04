#pragma once

#include <string>
#include "ImageCodex.h"
#include "Surface.h"

class Actor
{
public:
	Actor( const std::wstring& imagename)
		:
		pImage( ImageCodex::Retrieve( imagename ) )
	{
	}
	virtual ~Actor() {}
	Actor( const Actor& ) = default;
	Actor( Actor&& ) = default;
	Actor& operator=( const Actor& ) = default;
	Actor& operator=( Actor&& ) noexcept = default;
	virtual void Update( float dt, const class Game& game ) = 0;
	virtual void Draw( HDC hdc ) = 0;
	bool ShouldDestroy() const
	{
		return shouldDestroy;
	}
protected:
	std::shared_ptr<Gdiplus::Image> pImage;
	Surface surface;
	bool shouldDestroy = false;
};