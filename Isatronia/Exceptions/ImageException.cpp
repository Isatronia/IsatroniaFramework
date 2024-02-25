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
	ImageException::ImageException(std::string Description)
		:std::exception(Description.c_str())
	{
		return;
	}

	void ImageException::showErrorDialog()
	{
		ShowErrorDialog(this->what());
		return;
	}

	//----------------------------------------------------
	// BitmapFlipException
	//----------------------------------------------------
	BitmapFlipException::BitmapFlipException(string Description)
		:ImageException(Description)
	{
		return;
	}
}