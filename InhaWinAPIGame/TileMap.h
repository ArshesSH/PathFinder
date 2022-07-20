#pragma once

#include <vector>
#include <string>
#include "Vec2.h"
#include "Surface.h"

class TileMap
{
public:


public:
	TileMap( int tileSize, int tileRow, int tileCol )
		:
		tileSize(tileSize),
		tileRow( tileRow ),
		tileCol(tileCol),
		tiles( tileRow * tileCol, TileState::Empty )
	{
	}

	void Draw( Gdiplus::Graphics& gfx )
	{
		for ( int i = 0; i < (int)tiles.size(); ++i )
		{
			const int x = i % tileRow;
			const int y = i / tileRow;
			Gdiplus::Color c;
			switch ( tiles[i] )
			{
			case TileState::Empty:
				{
					c = White;
				}
				break;
			case TileState::Opened:
				{
					c = Green;
				}
				break;
			case TileState::Closed:
				{
					c = Red;
				}
				break;
			case TileState::Obstacle:
				{
					c = Gray;
				}
				break;
			case TileState::Source:
				{
					c = Blue;
				}
			case TileState::Target:
				{
					c = Magenta;
				}
			}
			DrawRect( gfx, x * tileSize, y * tileSize, c );
			
		}
	}

private:
	void DrawRect( Gdiplus::Graphics& gfx, int x, int y, Gdiplus::Color innerColor )
	{
		Surface::DrawFillRect( gfx, innerColor, x + 1, y + 1, tileSize - 1, tileSize - 1 );
		Surface::DrawRect( gfx, Black, 1, x, y, tileSize, tileSize );
	}
	void DrawInforms( Gdiplus::Graphics& gfx, int x, int y, int g, int h, int f )
	{
		const std::wstring strGH = std::to_wstring( g ) + L"  " + std::to_wstring(h);
		Surface::DrawString( gfx, strGH, (float)x, (float)y, Black, 10 );

	}
	
private:
	const int tileSize;
	const int tileRow;
	const int tileCol;
	const Gdiplus::Color Black = { 255,0,0,0 };
	const Gdiplus::Color White = { 255,255,255,255 };
	const Gdiplus::Color Red = { 255,255,0,0 };
	const Gdiplus::Color Green = { 255,0,255,0 };
	const Gdiplus::Color Blue = { 255,0,0,255 };
	const Gdiplus::Color Gray = { 255,144,144,144 };
	const Gdiplus::Color Magenta = { 255,255,0,255 };

	std::vector<TileState> tiles;
};