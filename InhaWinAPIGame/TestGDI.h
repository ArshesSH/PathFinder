#pragma once

#include "framework.h"
#include <ObjIdl.h>
#include <gdiplus.h>

class TestGDI
{
public:
    void DrawSprites( HDC hdc, RECT rcClient )
    {
        HDC hMemDC;
        HBITMAP hOldBitmap;
        HDC hComponentDC;
        HBITMAP hOldComponentBitmap;

        hMemDC = CreateCompatibleDC( hdc );
        if ( hDoubleBufferImage == nullptr )
        {
            // Create Bitmap Image for Double buffering
            hDoubleBufferImage = CreateCompatibleBitmap( hdc, rcClient.right, rcClient.bottom );
        }

        hOldBitmap = (HBITMAP)SelectObject( hMemDC, hDoubleBufferImage );

        auto pSpriteList = GetInstance();
        for ( auto& s : *pSpriteList )
        {
            hComponentDC = CreateCompatibleDC( hMemDC );
            hOldComponentBitmap = (HBITMAP)SelectObject( hComponentDC, s.GetHBITMAP() );
            s.DrawSprite( hMemDC, hComponentDC );
            SelectObject( hComponentDC, hOldComponentBitmap );
            DeleteObject( hComponentDC );
        }

        BitBlt( hdc, 0, 0, rcClient.right, clientRECT.bottom, hMemDC, 0, 0, SRCCOPY );
        SelectObject( hMemDC, hOldBitmap );
        DeleteObject( hMemDC );
    }

private:
	void DrawGDI(HDC hdc)
	{
		using namespace Gdiplus;

		Graphics graphics( hdc );

        // Txt
        SolidBrush brush( Color( 255, 255, 0, 0 ) );
        FontFamily fontFamily( L"Consolas" );
        Font font( &fontFamily, 24, FontStyleRegular, UnitPixel );
        PointF pointF( 10.0f, 20.0f );

        graphics.DrawString( L"Hello World!", -1, &font, pointF, &brush );


        // Line
        Pen pen( Color( 100, 0, 255, 255 ), 6 );
        graphics.DrawLine( &pen, 0, 0, 200, 200 );

        // Image
        Image image( L"Images/sigong.png" );
        int w = image.GetWidth();
        int h = image.GetHeight();
        graphics.DrawImage( &image, 300, 100, w, h );

        // animation
        Image zeroImage( L"Images/zero_run.png" );
        int wz = zeroImage.GetWidth() / 16;
        int hz = zeroImage.GetHeight() / 2;
        int xStart = curFrame * wz;
        int yStart = 0;
        // deledte chroma
        ImageAttributes imgAttr;
        imgAttr.SetColorKey( Color( 245, 0, 245 ), Color( 255, 10, 255 ) );
        graphics.DrawImage( &zeroImage, Gdiplus::Rect( 400, 100, wz * 2, hz * 2 ), xStart, yStart, wz, hz, UnitPixel, &imgAttr );


        // alpha rect
        brush.SetColor( Color( 128, 255, 0, 0 ) );
        graphics.FillRectangle( &brush, 600, 100, wz * 2, hz * 2 );


        // Rotate Image
        Image* pImg;
        pImg = Image::FromFile( L"Images/sigong.png" );
        POINT sigongPos = { 300, 200 };
        if ( pImg != nullptr )
        {
            w = pImg->GetWidth();
            h = pImg->GetHeight();

            Gdiplus::Matrix mat;
            static int rot = 0;

            mat.RotateAt( (rot % 360),
                Gdiplus::PointF( ((float)sigongPos.x + (float)w * 0.5f), (float)sigongPos.y + (float)(h * 0.5f) )
            );
            graphics.SetTransform( &mat );
            graphics.DrawImage( pImg, sigongPos.x, sigongPos.y, w, h );
            rot -= 50;

            mat.Reset();
            graphics.SetTransform( &mat );
        }

        // Alpha Image
        if ( pImg )
        {
            REAL transparency = 0.5f;
            ColorMatrix colorMatrix =
            {
                1.0f, 0.0f, 0.0f, 0.0f,         0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,         0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,         0.0f,
                0.0f, 0.0f, 0.0f, transparency, 0.0f,
                0.0f, 0.0f, 0.0f, 0.0f,         1.0f
            };
            imgAttr.SetColorMatrix( &colorMatrix );
            sigongPos.x = 400;
            graphics.DrawImage( pImg, Gdiplus::Rect( sigongPos.x, sigongPos.y, w, h ),  // Dest coord
                0, 0, w, h, UnitPixel, &imgAttr );                                      // Src Coord
        }


        // GrayScale
        if ( pImg )
        {
            ColorMatrix grayMatrix =
            {
                0.3f, 0.3f, 0.3f,        0.0f,         0.0f,
                0.3f, 0.3f, 0.3f,        0.0f,         0.0f,
                0.3f, 0.3f, 0.3f,        0.0f,         0.0f,
                0.0f, 0.0f, 0.0f,        1.0f,         0.0f,
                0.0f, 0.0f, 0.0f,        0.0f,         1.0f
            };
            imgAttr.SetColorMatrix( &grayMatrix );
            sigongPos.x = 500;
            graphics.DrawImage( pImg, Gdiplus::Rect( sigongPos.x, sigongPos.y, w, h ),  // Dest coord
                0, 0, w, h, UnitPixel, &imgAttr );
        }

        // test
        if ( pImg != nullptr )
        {
            ColorMatrix grayMatrix =
            {
                0.3f, 0.3f, 0.3f,        0.0f,         0.0f,
                0.3f, 0.3f, 0.3f,        0.0f,         0.0f,
                0.3f, 0.3f, 0.3f,        0.0f,         0.0f,
                0.0f, 0.0f, 0.0f,        1.0f,         0.0f,
                0.0f, 0.0f, 0.0f,        0.0f,         1.0f
            };
            imgAttr.SetColorMatrix( &grayMatrix );
            sigongPos.x = 600;

            pImg->RotateFlip( RotateNoneFlipX );
            graphics.DrawImage( pImg, Gdiplus::Rect( sigongPos.x, sigongPos.y, w, h ),  // Dest coord
                0, 0, w, h, UnitPixel, &imgAttr );
        }

        delete pImg;
	}

private:
    HBITMAP hDoubleBufferImage;
    std::vector 
    int curFrame = 0;
};