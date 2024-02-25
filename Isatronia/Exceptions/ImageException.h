//--------------------------------------------------------------------------------------
// File: ImageException.h
//
// Copyright (c) Ishgrina. All rights reserved.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------
#pragma once
#include <iostream>
#include "./Exception.h"

namespace Isatronia::Exception
{
	using std::wstring;
	using std::string;

	class ImageException : public std::exception
	{
	public:
		ImageException(string Description);
	public:
		virtual void showErrorDialog();
	};

	class BitmapFlipException : public ImageException
	{
	public:
		BitmapFlipException(string Description);
	};
}