#pragma once

#include <Windows.h>
#include <iostream>
#include <conio.h>

#include <ddraw.h>
#include "UvcImage.h"

namespace IsaFrame::IsaSpriteFrame {


	class IsaBitMap : public UvcImage
	{
	private:

		BITMAPFILEHEADER mBitMapFileHeader;

		BITMAPINFOHEADER mBitMapInfoHeader;

		PALETTEENTRY mPalette[256];
	public:
		IsaBitMap();
		IsaBitMap(const char* fileName);
		~IsaBitMap();

		void loadImage(const char* fileName)override;
		void unloadImage()override;

		void Flip();

		RECT getImageRect();
		RECT GetDestRect(long x, long y);

		RGBInfo getPixelRGB(int x, int y)override;

	};

}