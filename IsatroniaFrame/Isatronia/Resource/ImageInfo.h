#pragma once

#include <Windows.h>

namespace Isatronia::Resource
{
	class ImageInfo
	{
	private:
		// size of the image
		POINT mSize;

		// total size of image, save for later.
		__int32 mBitCnt;

		// col dip
		__int32 mColorDepth;

		// is RGBA
		bool mRGBA;

	public:
		POINT getSize();
		__int32 getWidth();
		__int32 getHeight();

		__int32 getBitCount();

		__int32 getColorDepth();

		bool isRGBA();
	};
}