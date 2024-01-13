//--------------------------------------------------------------------------------------
// File: BitMap.h
//
// Copyright (c) Ishgrina. All rights reserved.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------
#pragma once

#include <Windows.h>
#include <iostream>
#include <conio.h>

#include <ddraw.h>
#include "Image.h"

namespace Isatronia::Resource {


	class Bitmap : public Image
	{
	private:

		BITMAPFILEHEADER mBitMapFileHeader;

		BITMAPINFOHEADER mBitMapInfoHeader;

		PALETTEENTRY mPalette[256];
	public:
		Bitmap();
		Bitmap(const char* fileName);
		~Bitmap();

		void loadImage(const char* fileName)override;
		void unloadImage()override;

		void Flip();

		RECT getImageRect();
		RECT GetDestRect(long x, long y);

		RGBInfo getPixelRGB(int x, int y)override;

	};
}

//LPDIRECTDRAWSURFACE7 Bitmap::CreatDDSurface(int Height, int Width, int mem_flags)
//{
//	DDSURFACEDESC2 ddsd;
//	LPDIRECTDRAWSURFACE7 lpdds7;
//
//	memset(&ddsd, 0, sizeof(ddsd));
//	ddsd.dwSize = sizeof(ddsd);
//
//	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
//
//	ddsd.dwHeight = Height;
//	ddsd.dwWidth = Width;
//	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | mem_flags;
//
//	if (FAILED(mlpDD7->CreateSurface(&ddsd, &lpdds7, NULL)))
//	{
//		__POSTERR(L"Gif Surface Creat Failed");
//		return false;
//	}
//
//	return lpdds7;
//}