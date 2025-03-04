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
#include <vector>

#include <ddraw.h>
#include "Image.h"

namespace Isatronia::Resource
{
	/*********************************************
	* Class: Bitmap
	*
	* Desc:
	* Save Infomations of a bitmap file, so program
	* could do some rendering when need.
	*
	**********************************************/

	class Bitmap : public Image
	{
	private:

		BITMAPFILEHEADER mBitMapFileHeader;

		BITMAPINFOHEADER mBitMapInfoHeader;

		std::vector<PALETTEENTRY> mPalette;
	public:
		Bitmap(const char* fileName);
		Bitmap(Bitmap&& bmp) noexcept;
		Bitmap();
		~Bitmap();

		void loadImage(const char* fileName)override;
		void unloadImage()override;

		void Flip();

		RECT getImageRect();
		RECT GetDestRect(__int32 x, __int32 y);

		RGBInfo getPixelRGB(__int32 x, __int32 y)override;

	protected:
		__int32 getPixelIndex(unsigned __int32 x, unsigned __int32 y);
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