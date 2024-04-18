#include "ImageInfo.h"

namespace Isatronia::Resource
{
	POINT ImageInfo::getSize()
	{
		return mSize;
	}

	__int32 ImageInfo::getWidth(){
		return mSize.x;
	}

	__int32 ImageInfo::getHeight()
	{
		return mSize.y;
	}

	__int32 ImageInfo::getBitCount()
	{
		return mBitCnt;
	}

	__int32 ImageInfo::getColorDepth()
	{
		return mColorDepth;
	}

	bool ImageInfo::isRGBA()
	{
		return mRGBA;
	}

	// extra methods
}