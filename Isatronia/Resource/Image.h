//***************************************************************************************
// App.h by Aaron Jsc (C) 2020 All Rights Reserved.
// licenced under CC BY-NC-SA.
//***************************************************************************************
#pragma once

#include <Windows.h>
#include <iostream>
#include <conio.h>

#include <ddraw.h>

#include "./Resource.h"
#include "./RGBInfo.h"

namespace Isatronia::Resource {

	class Image: public Resource
	{
	private:
		// Image Size.
		POINT mImageDimension;
		// The memory where Image stored.
		UCHAR* mBuffer;
		
		// total size of image, save for later.
		int mBitCnt;
		// col dip
		int mColorDepth;

	public:
		// This constructor will give u a empty Image.
		Image();
		virtual ~Image();

		// load image from file.
		virtual void loadImage(const char* fileName) = 0;
		virtual void unloadImage() = 0;


		virtual RGBInfo getPixelRGB(int x, int y) = 0;

	public:
		// getters and setters.
		POINT getImageDimension();
		void setImageDimension(POINT dim);

		UCHAR* getImage();

		int getImageSize();

		int getColorDepth();

		// setters for subclasses.
	protected:
		void setImage(UCHAR* img);
		void setImageSize(int size);
		void setColorDepth(int colorDepth);
	};
}