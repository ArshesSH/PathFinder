#include "Surface.h"

Surface::Surface( const std::wstring& filename )
{
	pImage = std::make_shared<Gdiplus::Image>( filename.c_str() );

}