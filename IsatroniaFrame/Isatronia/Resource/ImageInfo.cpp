#include "ImageInfo.h"

namespace Isatronia::Resource
{
	POINT ImageInfo::getSize()
	{
		return mSize;
	}

	__int32 ImageInfo::getWidth()
	{
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

	__int32 ImageInfo::getPixelCount()
	{
		return (mSize.x * mSize.y);
	}

	__int32 ImageInfo::getColorDepth()
	{
		return mColorDepth;
	}

	bool ImageInfo::isRGBA()
	{
		return mRGBA;
	}

	void ImageInfo::setSize(POINT& size)
	{
		this->mSize.x = size.x;
		this->mSize.y = size.y;
		return;
	}
	void ImageInfo::setSize(POINT&& size)
	{
		this->mSize.x = size.x;
		this->mSize.y = size.y;
		return;
	}

	void ImageInfo::setBitCnt(__int32 count)
	{
		this->mBitCnt = count;
		return;
	}

	void ImageInfo::setColorDepth(__int32 depth)
	{
		this->mColorDepth = depth;
		return;
	}

	void ImageInfo::setRGBA(bool isRGBA)
	{
		this->mRGBA = isRGBA;
		return;
	}

	// extra methods
}