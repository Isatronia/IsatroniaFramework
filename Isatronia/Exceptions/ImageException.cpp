//--------------------------------------------------------------------------------------
// File: ImageException.cpp
//
// Copyright (c) Ishgrina. All rights reserved.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------
#include "./ImageException.h"

namespace Isatronia::Exception
{
	using std::wstring;

	//----------------------------------------------------
	// ImageException
	//----------------------------------------------------
	ImageException::ImageException(wstring desc, wstring ImagePath)
		:FileException(desc, ImagePath)
	{
		return;
	};

	ImageException::ImageException(wstring desc)
		:FileException(desc, L"**File Path Not Contained**")
	{

	}

	//----------------------------------------------------
	// BitmapFlipException
	//----------------------------------------------------
	BitmapFlipException::BitmapFlipException(wstring ExceptionDescription, wstring ImagePath)
		:ImageException(ExceptionDescription, ImagePath)
	{
		return;
	}

	BitmapFlipException::BitmapFlipException(wstring ImagePath) :ImageException(L"Bitmap Flip Error")
	{
		setFilePath(ImagePath);
		return;
	}
	
	BitmapFlipException::BitmapFlipException(): ImageException(L"Bitmap Flip Function Throwed an Exception.")
	{
		return;
	}
}