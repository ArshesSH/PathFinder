#pragma once

#include <vector>

#include <ObjIdl.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")

template <typename T>
class PolygonGDI
{
public:
	PolygonGDI() {}
	PolygonGDI(const std::vector<T>& vertices)
		:
		vertices(vertices)
	{}

	void OverridePolygon(  )

private:
	void Insert( int pos, const std::vector<T>& vertices_in )
	{
		vertices.insert( std::next( vertices.begin(), pos ), vertices_in.begin(), vertices_in.end() );
	}
private:
	std::vector<T> vertices;
}