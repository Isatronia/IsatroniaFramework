//--------------------------------------------------------------------------------------
// File: Bitmap.cpp
//
// Copyright (c) Ishgrina. All rights reserved.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------
#include "BitMap.h"

#include "../Framework/Utils.h"
#include "../Exceptions/Exception.h"
#include "../Exceptions/ImageException.h"

namespace Isatronia::Resource
{
	using namespace Isatronia::Framework;
	using namespace Isatronia::Exception;

	Bitmap::Bitmap() : Image()
	{
		mBitMapFileHeader = { 0 };
		mBitMapInfoHeader = { 0 };
		mPalette = std::vector<PALETTEENTRY>(255);
	}

	Bitmap::Bitmap(const char* fileName) :Image()
	{
		mBitMapFileHeader = { 0 };
		mBitMapInfoHeader = { 0 };
		mPalette = std::vector<PALETTEENTRY>(255);
		Bitmap::loadImage(fileName);
	}

	Bitmap::Bitmap(Bitmap&& bmp) noexcept
	{
		mBitMapFileHeader = bmp.mBitMapFileHeader;
		mBitMapInfoHeader = bmp.mBitMapInfoHeader;
		mPalette = bmp.mPalette;
		mImageInfo = bmp.mImageInfo;
		if ( bmp.mImageInfo )
		{
			bmp.mImageInfo = nullptr;
		}
		mBuffer = bmp.mBuffer;
		if ( bmp.mBuffer.size() > 0 )
		{
			std::vector<RGBAInfo>().swap(bmp.mBuffer);
		}
		mIsLoaded = bmp.mIsLoaded;
		return;
	}

	Bitmap::~Bitmap()
	{
		unloadImage();
	}

	void Bitmap::loadImage(const char* fileName)
	{
		int fileHandle;	// the file handle
		int index;		// looping index

		/*UCHAR* tempBuffer = nullptr;*/	// used to convert 24bit image to 16bit
		std::unique_ptr<UCHAR[]> imageBuffer(nullptr);
		OFSTRUCT fileData;
		memset(&fileData, 0, sizeof(fileData));

		unloadImage();

		//if (-1 == (fileHandle = OpenFile(fileName, &fileData, OF_READ)))
		if ( HFILE_ERROR == ( fileHandle = OpenFile(fileName, &fileData, OF_READ) ) )
		{
			return;
		}

		// load the bitmap file header
		_lread(fileHandle, &mBitMapFileHeader, sizeof(BITMAPFILEHEADER));

		// test if is a Bitmap
		if ( mBitMapFileHeader.bfType != 0x4D42 )
		{
			_lclose(fileHandle);
			return;
		}// end if

		// now load the bitmap file header
		_lread(fileHandle, &mBitMapInfoHeader, sizeof(BITMAPINFOHEADER));

		// fill ImageInfo
		getInfo().setBitCnt(mBitMapInfoHeader.biSize);
		getInfo().setColorDepth(mBitMapInfoHeader.biBitCount);
		getInfo().setSize({ mBitMapInfoHeader.biWidth, std::abs(mBitMapInfoHeader.biHeight) });
		if ( getInfo().getColorDepth() < 32 )
		{
			getInfo().setRGBA(false);
		}
		else
		{
			getInfo().setRGBA(true);
		}

		// what we need done for 8-bit bitmap
		if ( mBitMapInfoHeader.biBitCount == 8 )
		{
			_lread(fileHandle, mPalette.data(), 256 * sizeof(PALETTEENTRY));

			for ( index = 0; index < 256; index++ )
			{
				// reverse the red and greed fields, maybe.
				Swap(mPalette[index].peBlue, mPalette[index].peRed);

				// aleays set the flags word to this
				mPalette[index].peFlags = PC_NOCOLLAPSE;
			}
		}// end if

		// in case of 16 bits
		//_llseek(fileHandle, -(int) ( mBitMapFileHeader.bfSize ), SEEK_END);
		_llseek(fileHandle, -(int) ( mBitMapInfoHeader.biSizeImage ), SEEK_END);
		//_llseek(fileHandle, mBitMapFileHeader.bfOffBits, SEEK_SET);

		// now read in the Image
		if ( mBitMapInfoHeader.biBitCount == 8 ||
			mBitMapInfoHeader.biBitCount == 16 ||
			mBitMapInfoHeader.biBitCount == 24 ||
			mBitMapInfoHeader.biBitCount == 32 )
		{
			// if have another bitmap before, del it.
			/*if ( getImage().size()> 0 )
			{
				delete getImage();
			}*/
			try
			{
				imageBuffer.reset(new UCHAR[mBitMapInfoHeader.biSizeImage]);
				this->setImage(mImageInfo, std::vector<RGBAInfo>(getInfo().getPixelCount()));
			}
			catch ( const std::bad_alloc& e )
			{
				//  if alloc memory failed.
				unloadImage();
				_lclose(fileHandle);
				return;
			}

			// now read.
			_lread(fileHandle, static_cast<LPVOID>( imageBuffer.get() ), mBitMapInfoHeader.biSizeImage);
			for ( int y = 0; y < abs(mBitMapInfoHeader.biHeight); ++y )
			{
				int src_y = mBitMapInfoHeader.biHeight - y - 1;
				for ( int x = 0; x < mBitMapInfoHeader.biWidth; ++x )
				{
					mBuffer[y * mBitMapInfoHeader.biWidth + x] =
						getRGBAInfoInImageBuffer(imageBuffer.get(), mBitMapInfoHeader, x, src_y);
				}
			}
		}// end if
		else
		{
			return;
		}

		_lclose(fileHandle);

		setLoadState(true);

		//Flip();
		//this->mImageInfo->setColorDepth(mBitMapInfoHeader.biBitCount);
		return;
	}

	void Bitmap::unloadImage()
	{
		mBitMapFileHeader = { 0 };
		mBitMapInfoHeader = { 0 };
		mPalette = std::vector<PALETTEENTRY>(255, { 0 });
		mIsLoaded = false;
		if ( mBuffer.size() > 0 )
		{
			std::vector<RGBAInfo>().swap(mBuffer);
		}
		if ( mImageInfo )
		{
			delete mImageInfo;
			mImageInfo = nullptr;
		}
		return;
	}

	void Bitmap::Flip()
	{
		if ( mBitMapInfoHeader.biHeight < 0 ) return; // the BM do not need flip.
		if ( mBitMapInfoHeader.biBitCount < 8 )
		{
			throw( new BitmapFlipException("Flip Exception Occured.") );
			return;	// not deal with 1&4bit bitmap.
		}

		std::vector<RGBAInfo> buffer(getInfo().getPixelCount());
		//mBitCnt = mBitMapInfoHeader.biBitCount / 8;
		//setImageSize(mBitMapInfoHeader.biBitCount / 8);

		// Flip the bitmap
		int _ylim = mBitMapInfoHeader.biHeight >> 1;
		int _width = getInfo().getWidth();
		for ( int y = 0; y < _ylim; ++y )
		{
			int _yOppo = getInfo().getHeight() - y - 1;
			/*memcpy(buffer + y * (int) mBitMapInfoHeader.biHeight,
				getImage() + ( (int) mBitMapInfoHeader.biHeight - y ) * mBitMapInfoHeader.biHeight,
				mBitMapInfoHeader.biWidth);*/
			for ( int x = 0; x < mBitMapInfoHeader.biWidth; ++x )
			{
				std::swap(mBuffer[y * _width + x], mBuffer[_yOppo * _width + x]);
				//buffer[getPixelIndex(x, y)] = mBuffer[getPixelIndex(x, abs(getInfo().getHeight() - y - 1))];
			}
		}
		return;
	}

	RECT Bitmap::getImageRect()
	{
		return { 0, 0, getInfo().getWidth(), getInfo().getHeight() };
	}
	RECT Bitmap::GetDestRect(__int32 x, __int32 y)
	{
		return { x , y, x + getInfo().getWidth(), y + getInfo().getHeight() };
	}


	RGBInfo Bitmap::getPixelRGB(int x, int y)
	{
		if ( x < getInfo().getWidth() && y < getInfo().getHeight() )
		{
			return mBuffer[getPixelIndex(x, y)];
		}
		return RGBInfo();
	}

	__int32 Bitmap::getPixelIndex(unsigned __int32 x, unsigned __int32 y)
	{
		if ( !isLoaded() ||
			static_cast<__int64>( x ) > static_cast<__int64>( getInfo().getWidth() ) ||
			static_cast<__int64>( y ) > static_cast<__int64>( getInfo().getHeight() ) )
		{
			return NULL;
		}
		return getInfo().getWidth() * y + x;
	}


}