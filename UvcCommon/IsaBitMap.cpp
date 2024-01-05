#include "IsaBitMap.h"

namespace IsaD9Frame {


	template<typename T>
	void Swap(T& a, T& b) { T c; c = a; a = b; b = c; };

	IsaBitMap::IsaBitMap() : UvcImage()
	{
		mBitMapFileHeader = { 0 };
		mBitMapInfoHeader = { 0 };
		memset(&mPalette, 0, sizeof(mPalette));
	}

	IsaBitMap::IsaBitMap(const char* fileName)
	{
		IsaBitMap::loadImage(fileName);
	}

	void IsaBitMap::loadImage(const char* fileName)
	{

		int fileHandle;	// the file handle
		int index;		// looping index

		UCHAR* tempBuffer = nullptr;	// used to convert 24bit image to 16bit
		OFSTRUCT fileData;
		memset(&fileData, 0, sizeof(fileData));

		//if (-1 == (fileHandle = OpenFile(fileName, &fileData, OF_READ)))
		if (HFILE_ERROR == (fileHandle = OpenFile(fileName, &fileData, OF_READ)))
		{
			return 0;
		}

		// load the bitmap file header
		_lread(fileHandle, &mBitMapFileHeader, sizeof(BITMAPFILEHEADER));

		// test if is a Bitmap
		if (mBitMapFileHeader.bfType != 0x4D42)
		{
			_lclose(fileHandle);
			return 0;
		}// end if

		// now load the bitmap file header
		_lread(fileHandle, &mBitMapInfoHeader, sizeof(BITMAPINFOHEADER));

		// what we need done for 8-bit bitmap
		if (mBitMapInfoHeader.biBitCount == 8)
		{
			_lread(fileHandle, &mPalette,
				256 * sizeof(PALETTEENTRY));

			for (index = 0; index < 256; index++)
			{
				// reverse the red and greed fields, maybe.
				Swap(mPalette[index].peBlue, mPalette->peRed);

				// aleays set the flags word to this
				mPalette->peFlags = PC_NOCOLLAPSE;
			}
		}// end if

		// in case of 16 bits
		_llseek(fileHandle, -(int)(mBitMapFileHeader.bfSize), SEEK_END);

		// now read in the Image
		if (mBitMapInfoHeader.biBitCount == 8 ||
			mBitMapInfoHeader.biBitCount == 16 ||
			mBitMapInfoHeader.biBitCount == 24)
		{
			// if have another bitmap before, del it.
			if (getImage() != nullptr)
			{
				delete getImage();
			}

			setImage(new UCHAR[mBitMapInfoHeader.biSizeImage]);
			// test if new failed.
			if (!getImage())
			{
				_lclose(fileHandle);
				return 0;
			}

			// now read.
			_lread(fileHandle, getImage(), mBitMapInfoHeader.biSizeImage);
		}// end if
		else
		{
			return 0;
		}

		_lclose(fileHandle);

		Flip();

		setColorDepth(mBitMapInfoHeader.biBitCount);

		return;
	}

	void IsaBitMap::unloadImage()
	{
		try {
			if (getImage() != nullptr)
			{
				delete getImage();
				setImage(nullptr);
			}
			return;
		}
		catch (...) {
			return;
		}
		return;
	}

	void IsaBitMap::Flip()
	{
		// TODO: 在此处添加实现代码.
		UCHAR* buffer = new UCHAR[sizeof(getImage())];

		if (mBitMapInfoHeader.biHeight < 0) return; // the BM do not need flip.
		if (mBitMapInfoHeader.biBitCount < 8) {
			throw(new BitmapFlipException());
			return;	// not deal with 1&4bit bitmap.
		}

		//mBitCnt = mBitMapInfoHeader.biBitCount / 8;
		setImageSize(mBitMapInfoHeader.biBitCount / 8);

		// Flip the bitmap
		for (int y = 0; y < mBitMapInfoHeader.biHeight; y++)
		{
			memcpy(buffer + y * (int)mBitMapInfoHeader.biHeight,
				getImage() + ((int)mBitMapInfoHeader.biHeight - y) * mBitMapInfoHeader.biHeight,
				mBitMapInfoHeader.biWidth);
		}

		delete getImage();
		setImage(buffer);
		buffer = nullptr;
		return true;
	}

	RGBInfo IsaBitMap::getPixelRGB(int x, int y) {
		if (mBitMapInfoHeader.biBitCount < 8) return RGBInfo(0, 0, 0);
		RGBInfo col(0, 0, 0);
		UCHAR* mBuffer = getImage();
		switch (mBitMapInfoHeader.biBitCount)
		{
		case 16:
		{
			col.b = (mBuffer[(x + y * mBitMapInfoHeader.biWidth) * 2 + 0]) >> 3;
			col.g = (mBuffer[(x + y * mBitMapInfoHeader.biWidth) * 2 + 1]) >> 2;
			col.r = (mBuffer[(x + y * mBitMapInfoHeader.biWidth) * 2 + 2]) >> 3;
		}
		break;
		case 24:
		{
			col.b = mBuffer[(x + y * mBitMapInfoHeader.biWidth) * 3 + 0];
			col.g = mBuffer[(x + y * mBitMapInfoHeader.biWidth) * 3 + 1];
			col.r = mBuffer[(x + y * mBitMapInfoHeader.biWidth) * 3 + 2];
		}
		break;
		case 32:
		{
			col.b = mBuffer[(x + y * mBitMapInfoHeader.biWidth) * 4 + 0];
			col.g = mBuffer[(x + y * mBitMapInfoHeader.biWidth) * 4 + 1];
			col.r = mBuffer[(x + y * mBitMapInfoHeader.biWidth) * 4 + 2];
		}
		break;
		default:break;
		}
		return col;
	}
}

//LPDIRECTDRAWSURFACE7 IsaBitMap::CreatDDSurface(int Height, int Width, int mem_flags)
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