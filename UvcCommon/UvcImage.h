//***************************************************************************************
// UvcDDApp.h by Aaron Jsc (C) 2020 All Rights Reserved.
// licenced under CC BY-NC-SA.
//***************************************************************************************
#pragma once

#include <Windows.h>
#include <iostream>
#include <conio.h>

#include <ddraw.h>

#include "IsaUtils.h"

namespace IsaD9Frame {

	class UvcImage
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
		UvcImage();
		~UvcImage();

		// load image from file.
		virtual int loadImage(const char* fileName) = 0;
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

	// ---------------------------------------------------
	// Methods
	// ---------------------------------------------------
	void UvcImage::unloadImage() {
		if (getImage())
		{
			delete getImage();
		}
		setImage(nullptr);
		setColorDepth(0);
		setImageDimension(POINT{ 0, 0 });
		setImageSize(0);
	}

	// ---------------------------------------------------
	// Constructors
	// ---------------------------------------------------
	UvcImage::UvcImage() {
		setImageDimension(POINT{ 0 ,0 });
		setColorDepth(0);
		setImage(nullptr);
		setImageSize(0);
		return;
	}

	UvcImage::~UvcImage() {
		if (mBuffer) {
			delete mBuffer;
		}
		return;
	}

	// ---------------------------------------------------
	// Getters And Setters
	// ---------------------------------------------------

	POINT UvcImage::getImageDimension() {
		return mImageDimension;
	}

	void UvcImage::setImageDimension(POINT dim) {
		mImageDimension = dim;
		return;
	}

	UCHAR* UvcImage::getImage() {
		return mBuffer;
	}

	void UvcImage::setImage(UCHAR* img) {
		mBuffer = img;
		return;
	}

	int UvcImage::getImageSize() {
		return mBitCnt;
	}

	void UvcImage::setImageSize(int size) {
		mBitCnt = size;
		return;
	}

	int UvcImage::getColorDepth() {
		return mColorDepth;
	}

	void UvcImage::setColorDepth(int colorDepth) {
		mColorDepth = colorDepth;
		return;
	}
}