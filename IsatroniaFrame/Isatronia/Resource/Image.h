//--------------------------------------------------------------------------------------
// File: Image.h
//
// Copyright (c) Ishgrina. All rights reserved.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------
#pragma once

#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <vector>

#include <ddraw.h>

#include "./Resource.h"
#include "./RGBInfo.h"
#include "./ImageInfo.h"

namespace Isatronia::Resource
{
	class Image : public Resource
	{
	protected:
		// Image Info
		ImageInfo* mImageInfo;
		/*POINT mImageDimension;*/

		// The memory where Image stored.
		//UCHAR* mBuffer;
		std::vector<RGBAInfo> mBuffer;

		bool mIsLoaded;

	public:
		// This constructor will give u an empty Image.
		Image();
		virtual ~Image();

		// load image from file.
		virtual void loadImage(const char* fileName) = 0;
		virtual void unloadImage() = 0;

		virtual RGBInfo getPixelRGB(int x, int y) = 0;

	public:
		// public getters
		const ImageInfo& getImageInfo() const;
		const std::vector<RGBAInfo>& getImage() const;
		bool isLoaded();

		// setters for subclasses.
	protected:
		ImageInfo& getInfo();
		void setImage(ImageInfo* info, std::vector<RGBAInfo>& img);
		void setImage(ImageInfo* info, std::vector<RGBAInfo>&& img);
		void setPixel(unsigned __int32 x, unsigned __int32 y, RGBAInfo& pixel);
		//void setImageInfo(ImageInfo* info);
		//void setImageMemory(RGBAInfo* img);
		void setLoadState(bool isLoaded);
	};
}