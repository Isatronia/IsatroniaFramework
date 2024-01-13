//--------------------------------------------------------------------------------------
// File: ImageException.h
//
// Copyright (c) Ishgrina. All rights reserved.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------
#pragma once
#include <iostream>
#include "./Exception.h"

namespace Isatronia::Exception {

	using std::wstring;

	class ImageException : public FileException {
	public:

		ImageException(wstring, wstring);
		ImageException(wstring);
	};

	class BitmapFlipException : public ImageException
	{
	public:
		BitmapFlipException(wstring ExceptionDescription, wstring ImagePath);
		BitmapFlipException(wstring ImagePath);
		BitmapFlipException();
	};
}