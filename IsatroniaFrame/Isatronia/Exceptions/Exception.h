//--------------------------------------------------------------------------------------
// File: Exception.h
//
// Copyright (c) Ishgrina. All rights reserved.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------
#pragma once
#include <iostream>
#include <string>
#include <exception>
#include <Windows.h>

//#define __POSTERR(str) {MessageBox(0, str, L"Error", NULL);}

namespace Isatronia::Exception
{
	using std::wstring;
	using std::string;
	//--------------------------------------------------
	// Utils
	//--------------------------------------------------
	void ShowErrorDialog(std::string msg, std::string title = "Error");
	void ShowErrorDialog(const char* msg, const char* title = "Error");
	void ShowErrorDialog(std::wstring msg, std::wstring title = L"Error");

	//--------------------------------------------------
	// Base Exception
	//--------------------------------------------------
	class Exception : public std::exception
	{
	public:
		Exception() = delete;
		Exception(string Description);
		Exception(const char*& Description);
		Exception(const char* Description);
	public:
		virtual void showErrorDialog(bool fatal = false);
	};

	class LogicException : public Exception
	{
		using Exception::Exception;
	};

	class FileException : public Exception
	{
		using Exception::Exception;
	};
}