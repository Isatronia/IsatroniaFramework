#pragma once

#include <Windows.h>
#include <iostream>
#include <conio.h>

#include <ddraw.h>
#include "UvcImage.h"

namespace IsaD9Frame {


	class IsaBitMap : public UvcImage
	{
	public:
		IsaBitMap();
		IsaBitMap(const char* fileName);
		~IsaBitMap();

		int loadImage(const char* fileName);
		int unloadImage();

		bool Flip();

		RECT getImageRect();
		RECT GetDestRect(long x, long y);

		RGBInfo getPixelRGB(int x, int y)override;

	public:

		BITMAPFILEHEADER mBitMapFileHeader;

		BITMAPINFOHEADER mBitMapInfoHeader;

		PALETTEENTRY mPalette[256];
	};

}