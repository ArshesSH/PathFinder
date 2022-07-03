#pragma once

#include "framework.h"
#include <ObjIdl.h>
#include <gdiplus.h>
#include <string>
#include <memory>
#include "Vec2.h"

class Surface
{
public:
	Surface( const std::wstring& filename );

private:
	std::shared_ptr<Gdiplus::Image> pImage;
};

