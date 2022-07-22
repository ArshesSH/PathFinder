#pragma once

#include <vector>
#include <string>
#include "Vec2.h"
#include "Surface.h"
#include "AStar.h"

class TileMap
{
public:
	TileMap( int tileSize, int tileRow, int tileCol );

	void Update( const Vec2<int>& mousePos_in, const Vec2<int>& sceneTopLeft_in, float dt );
	void Draw( Gdiplus::Graphics& gfx );

	bool FindPathOnce();
	bool CanTracking() const;
	void SetFindStart();
	std::vector<Vec2<int>> GetRoute();

	void SetSrcPos();
	void SetDestPos();
	void SetObstaclePos();

	std::vector<Vec2<int>> GetRawPath() const;
	bool IsSrcSet() const;
	Vec2<int> GetSrcTilePos() const;

private:
	void DrawRect( Gdiplus::Graphics& gfx, int x, int y, Gdiplus::Color innerColor );
	void DrawInforms( Gdiplus::Graphics& gfx, int x, int y, int g, int h, int f );
	Vec2<int> FindTileFromPos();
	bool IsInsideTileMap( const Vec2<int>& pos ) const;
	Vec2<int> GridToTile( const Vec2<int>& pos ) const;

private:
	static constexpr float searchDrawDelay = 0.001f;
	const int tileSize;
	const int tileRow;
	const int tileCol;
	const int width;
	const int height;
	const Gdiplus::Color Black = { 255,0,0,0 };
	const Gdiplus::Color White = { 255,255,255,255 };
	const Gdiplus::Color Red = { 255,255,0,0 };
	const Gdiplus::Color Green = { 255,0,255,0 };
	const Gdiplus::Color Blue = { 255,0,0,255 };
	const Gdiplus::Color Gray = { 255,125,125,125 };
	const Gdiplus::Color Magenta = { 255,255,0,255 };
	const Gdiplus::Color Purple = { 255,230,50,230 };
	const Gdiplus::Color LightPink = { 255,255,144,255 };

	Vec2<int> mousePos;
	Vec2<int> sceneTopLeft;
	bool isFindStart = false;

	AStar aStar;
	std::vector<Vec2<int>> path;
	float time = 0.0f;

	bool isFindEnd = false;
};