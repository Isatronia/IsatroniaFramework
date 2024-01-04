//***************************************************************************************
// UvcDDApp.h by Aaron Jsc (C) 2020 All Rights Reserved.
// licenced under CC BY-NC-SA.
//***************************************************************************************
#pragma once

#include <Windows.h>
#include <iostream>
#include <conio.h>

#include <ddraw.h>

class UvcImage
{
private:
	// Image Size.
	POINT mImageDimension;
	// The memory where Image stored.
	UCHAR* mBuffer;
	// total size of image, save for later.
	int mBitCnt;

public:
	// This constructor will give u a empty Image.
	UvcImage();
	UvcImage(const char* fileName);
	~UvcImage();

	// load image from file.
	virtual int loadImage(const char* fileName) = 0;
	virtual int unloadImage() = 0;

	virtual RECT getRect();
	virtual RECT getDestRect(long x, long y);

public:
	// getters and setters.
	POINT getImageDimension();
	void setImageDimension(POINT dim);

	UCHAR* getImage();
	
	int getImageSize();

	// setters for subclasses.
protected:
	void setImage(UCHAR* img);
	void setImageSize(int size);

};

POINT UvcImage::getImageDimension() {
	return this->mImageDimension;
}

void UvcImage::setImageDimension(POINT dim) {
	this->mImageDimension = dim;
	return;
}

UCHAR* UvcImage::getImage() {
	return this->mBuffer;
}

void UvcImage::setImage(UCHAR* img) {
	this->mBuffer = img;
	return;
}

void UvcImage::setImageSize(int size) {
	this->mBitCnt = size;
	return;
}
