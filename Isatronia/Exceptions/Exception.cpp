//--------------------------------------------------------------------------------------
// File: Exception.cpp
//
// Copyright (c) Ishgrina. All rights reserved.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------
#include "Exception.h"

namespace Isatronia::Exception
{
	using std::wstring;

	void ShowErrorDialog(std::string msg, std::string title)
	{
		MessageBoxA(0, msg.c_str(), title.c_str(), MB_ICONWARNING | MB_OK);
		return;
	}

	void ShowErrorDialog(const char* msg, const char* title)
	{
		MessageBoxA(0, msg, title, MB_ICONWARNING | MB_OK);
		return;
	}

	void ShowErrorDialog(std::wstring msg, std::wstring title)
	{
		MessageBoxW(0, msg.c_str(), title.c_str(), MB_ICONWARNING | MB_OK);
		return;
	}

	//---------------------------------------------------------
	// Exception Class
	//---------------------------------------------------------
	Exception::Exception(string Description) : exception(Description.c_str())
	{
		return;
	}

	void Exception::showErrorDialog(bool fatal)
	{
		ShowErrorDialog(this->what());
		if ( fatal )
		{
			exit(-1);
		}
		return;
	}
}