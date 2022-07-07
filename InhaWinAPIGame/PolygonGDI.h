#pragma once

#include <vector>

#include <ObjIdl.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")

class PolygonGDI
{
public:
	PolygonGDI() {}
	PolygonGDI(const std::vector<Gdiplus::PointF>& vertices, const std::vector<int>& indices)
		:
		vertices(vertices),
		indices(indices)
	{}
private:
	std::vector<Gdiplus::PointF> vertices;
	std::vector<int> indices;
}