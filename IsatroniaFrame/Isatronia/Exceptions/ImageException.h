//--------------------------------------------------------------------------------------
// File: ImageException.h
//
// Copyright (c) Ishgrina. All rights reserved.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------
#pragma once
#include <iostream>
#include "Exception.h"

namespace Isatronia::Exception
{
	using std::wstring;
	using std::string;

	class ImageException : public FileException
	{
		using FileException::FileException;
	
	};

	class BitmapFlipException : public ImageException
	{
		using ImageException::ImageException;
	};
}