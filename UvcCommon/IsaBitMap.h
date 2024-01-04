#pragma once

#include <Windows.h>
#include <iostream>
#include <conio.h>

#include <ddraw.h>
#include "UvcImage.h"
class IsaBitMap : UvcImage
{
public:
	IsaBitMap();
	IsaBitMap(const char* fileName);
	~IsaBitMap();

	int loadImage(const char* fileName);
	int unloadImage();

	bool Flip();

	RECT GetRect();
	RECT GetDestRect(long x, long y);

public:

	BITMAPFILEHEADER mBitMapFileHeader;

	BITMAPINFOHEADER mBitMapInfoHeader;

	PALETTEENTRY mPalette[256];
};
