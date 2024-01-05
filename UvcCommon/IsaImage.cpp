#include "IsaImage.h"

#define __POSTERR(str) {MessageBoxA(0, str, L"Error", NULL);}


template<typename T>
void Swap(T& a, T& b) { T c; c = a; a = b; b = c; };

//UvcImage::UvcImage()
//{
//	mBitMapFileHeader = { 0 };
//	mBitMapInfoHeader = { 0 };
//	memset(&mPalette, 0, sizeof(mPalette));
//	mBuffer = nullptr;
//	mBitCnt = 0;
//}
//
//UvcImage::UvcImage(const char* fileName)
//{
//	UvcImage::loadImage(fileName);
//}
//
//UvcImage::~UvcImage()
//{
//}
//
//int UvcImage::loadImage(const char* fileName)
//{
//	// TODO: 在此处添加实现代码.
//
//	int fileHandle,	// the file handle
//		index;			// looping index
//
//	UCHAR* tempBuffer = nullptr;	// used to convert 24bit image to 16bit
//	OFSTRUCT fileData;
//	memset(&fileData, 0, sizeof(fileData));
//
//	if (-1 == (fileHandle = OpenFile(fileName, &fileData, OF_READ)))
//	{
//		return 0;
//	}
//
//	// load the bitmap file header
//	_lread(fileHandle, &mBitMapFileHeader, sizeof(BITMAPFILEHEADER));
//
//	// test if is a Bitmap
//	if (mBitMapFileHeader.bfType != 0x4D42)
//	{
//		_lclose(fileHandle);
//		return 0;
//	}// end if
//
//	// now load the bitmap file header
//	_lread(fileHandle, &mBitMapInfoHeader, sizeof(BITMAPINFOHEADER));
//
//	// what we need done for 8-bit bitmap
//	if (mBitMapInfoHeader.biBitCount == 8)
//	{
//		_lread(fileHandle, &mPalette,
//			256 * sizeof(PALETTEENTRY));
//
//		for (index = 0; index < 256; index++)
//		{
//			// reverse the red and greed fields, maybe.
//			Swap(mPalette[index].peBlue, mPalette->peRed);
//
//			// aleays set the flags word to this
//			mPalette->peFlags = PC_NOCOLLAPSE;
//		}
//	}// end if
//
//	// in case of 16 bits
//	_llseek(fileHandle, -(int)(mBitMapFileHeader.bfSize), SEEK_END);
//
//	// now read in the Image
//	if (mBitMapInfoHeader.biBitCount == 8 ||
//		mBitMapInfoHeader.biBitCount == 16 ||
//		mBitMapInfoHeader.biBitCount == 24)
//	{
//		// if have another bitmap before, del it.
//		if (mBuffer != nullptr)
//		{
//			free(mBuffer);
//		}
//
//		if (!(mBuffer = (UCHAR*)malloc(mBitMapInfoHeader.biSizeImage)))
//		{
//			_lclose(fileHandle);
//			return 0;
//		}
//
//		// now read.
//		_lread(fileHandle, mBuffer,
//			mBitMapInfoHeader.biSizeImage);
//	}// end if
//	else
//	{
//		return 0;
//	}
//
//	_lclose(fileHandle);
//
//	Flip();
//
//	return 1;
//}
//
//int UvcImage::unloadImage()
//{
//	if (mBuffer != nullptr)
//	{
//		free(mBuffer);
//		mBuffer = nullptr;
//	}
//	return 1;
//}
//
//bool UvcImage::Flip()
//{
//	// TODO: 在此处添加实现代码.
//	UCHAR* buffer = (UCHAR*)malloc(sizeof(mBuffer));
//
//	if (mBitMapInfoHeader.biHeight < 0) return true; // the BM do not need flip.
//	if (mBitMapInfoHeader.biBitCount < 8) return false;	// not deal with 1&4bit bitmap.
//
//	mBitCnt = mBitMapInfoHeader.biBitCount / 8;
//	// Flip the bitmap
//	for (int y = 0; y < mBitMapInfoHeader.biHeight; y++)
//	{
//		memcpy(buffer + y * mBitMapInfoHeader.biHeight,
//			mBuffer + (mBitMapInfoHeader.biHeight - y) * mBitMapInfoHeader.biHeight,
//			mBitMapInfoHeader.biWidth);
//	}
//
//	free(mBuffer);
//	mBuffer = buffer;
//	buffer = nullptr;
//	return true;
//}
//
//RECT UvcImage::getRect()
//{
//	RECT r = { 0 };
//	r.top = 0;
//	r.left = 0;
//	r.right = mBitMapInfoHeader.biWidth;
//	r.bottom = mBitMapInfoHeader.biHeight;
//	return r;
//}
//
//RECT UvcImage::GetDestRect(long x, long y)
//{
//	RECT r = { 0 };
//	r.top = y;
//	r.left = x;
//	r.right = x + mBitMapInfoHeader.biWidth;
//	r.bottom = y + mBitMapInfoHeader.biHeight;
//	return r;
//}

/*
LPDIRECTDRAWSURFACE7 UvcImage::GetDDSurface()
{
	return mlpDDS7;
}

RECT UvcImage::GetRect()
{
	RECT r = { 0 };
	r.top = 0;
	r.right = 0;
	r.left = mBitMapInfoHeader.biWidth;
	r.bottom = mBitMapInfoHeader.biHeight;
	return r;
}

LPDIRECTDRAWSURFACE7 UvcImage::CreatDDSurface(LPDIRECTDRAW7& lpDD7, int Height, int Width, int mem_flags)
{
	DDSURFACEDESC2 ddsd;
	LPDIRECTDRAWSURFACE7 lpdds7;

	memset(&ddsd, 0, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);

	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;

	ddsd.dwHeight = Height;
	ddsd.dwWidth = Width;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | mem_flags;

	DWORD debugCode = 0;

	if (FAILED(debugCode = lpDD7->CreateSurface(&ddsd, &lpdds7, NULL)))
	{
		__POSTERR(L"Gif Surface Creat Failed");

		return false;
	}

	return lpdds7;
}

int UvcImage::loadBufferTODDSurface(LPDIRECTDRAW7& lpdd7)
{
	mlpDDS7 = CreatDDSurface(lpdd7, mBitMapInfoHeader.biHeight, mBitMapInfoHeader.biWidth);

	if (mlpDDS7 == nullptr)
	{
		__POSTERR(L"Creat Surface ERR");
		PostQuitMessage(0);
		return 0;
	}

	DDSURFACEDESC2 ddsd;
	memset(&ddsd, 0, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);

	if (FAILED(mlpDDS7->Lock(NULL, &ddsd,
		DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT,
		NULL)))
	{
		__POSTERR(L"Image Lock Failed");
		PostQuitMessage(0);
		return 0;
	}

	UINT* videoBuffer = (UINT*)& ddsd.lpSurface;
	int lPitch32 = (int)(ddsd.lPitch >> 2);
	int index = 0;
	UCHAR blue, green, red;

	for (int y = 0; y < mBitMapInfoHeader.biHeight; y++)
	{
		for (int x = 0; x < mBitMapInfoHeader.biWidth; x++)
		{
			blue = mBuffer[index * 3 + 0];
			green = mBuffer[index * 3 + 1];
			red = mBuffer[index * 3 + 2];
			videoBuffer[x + y * lPitch32] = __RGB32BIT(0, red, green, blue);
			index++;
		}
	}

	if (FAILED(mlpDDS7->Unlock(NULL)))
	{
		__POSTERR(L"unlock failed");
		PostQuitMessage(0);
		return 0;
	}

	mSurfaceLoaded = true;

	return 1;
}

int UvcImage::loadImageToDDSurface(LPDIRECTDRAW7& lpdd7, const char* fileName)
{
	if (!loadImage(fileName))
	{
		__POSTERR(L"loadFailed");
		return 0;
	}

	if (!loadBufferTODDSurface(lpdd7))
	{
		return 0;
	}

	return 1;
}
*/