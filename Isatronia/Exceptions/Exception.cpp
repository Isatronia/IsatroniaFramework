//--------------------------------------------------------------------------------------
// File: Exception.cpp
//
// Copyright (c) Ishgrina. All rights reserved.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------
#include "Exception.h"

namespace Isatronia::Exception {
	using std::wstring;

	void PostExceptionInfo(std::string msg, std::string title = "Error") {
		MessageBoxA(0, msg.c_str(), title.c_str(), NULL);
		return;
	}

	void PostExceptionInfo(std::wstring msg, std::wstring title = L"Error") {
		MessageBox(0, msg.c_str(), title.c_str(), NULL);
		return;
	}

	//---------------------------------------------------------
	// Exception Class
	//---------------------------------------------------------
	wstring Exception::getExceptionInfo() {
		return mExceptionInfo;
	}

	Exception::Exception(wstring info) : mExceptionInfo(info) {
		return;
	};

	void Exception::showExceptionDialog(bool fatal) {
		PostExceptionInfo(mExceptionInfo);
		if (fatal) {
			exit(-1);
		}
		return;
	}

	void Exception::setExceptionInfo(wstring ExceptionInfo) {
		mExceptionInfo = ExceptionInfo;
		return;
	}

	//---------------------------------------------------------
	// File Exception
	//---------------------------------------------------------
	FileException::FileException(wstring desc, wstring path) : Exception(desc), mFilePath(path) {
		return;
	};

	wstring FileException::getFilePath() {
		return mFilePath;
	}

	void FileException::setFilePath(wstring path) {
		mFilePath = path;
		return;
	}

	void FileException::showExceptionDialog(bool fatal) {
			wstring tempInfo = L"";
			tempInfo = L"";
	}

	//---------------------------------------------------------
	// Runtime Exception
	//---------------------------------------------------------
	RuntimeException::RuntimeException(wstring ExceptionInfo) : Exception(ExceptionInfo) {
		return;
	}

	RuntimeException::RuntimeException(const wchar_t* ExceptionInfo) : Exception(wstring(ExceptionInfo)) {
		return;
	}

}