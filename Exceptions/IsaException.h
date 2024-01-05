#pragma once
#include <iostream>
#include <string>
#include <Windows.h>

//#define __POSTERR(str) {MessageBox(0, str, L"Error", NULL);}

namespace IsaFrame::Exception {

	using namespace std;

	void postError(wstring msg, wstring title = L"Error") {
		MessageBox(0, msg.c_str(), title.c_str(), NULL);
		return;
	}

	void postError(string msg, string title = "Error") {
		MessageBoxA(0, msg.c_str(), title.c_str(), NULL);
		return;
	}

	// Base Esception
	class Exception {
	private:
		wstring mExceptionInfo;

	public:
		Exception() = delete;
		Exception(wstring info) : mExceptionInfo(info) {};

		virtual wstring getExceptionInfo() { return mExceptionInfo; };

		virtual void showExceptionDialog(bool fatal = false) {
			postError(mExceptionInfo);
			if (fatal) {
				exit(-1);
			}
			return;
		}
	protected:
		void setExceptionInfo(wstring ExceptionInfo) { mExceptionInfo = ExceptionInfo; };
	};

	class FileException : public Exception
	{
	private:
		wstring mFilePath;
	public:
		FileException(wstring desc, wstring path) : Exception(desc), mFilePath(path) {};

		wstring getFilePath() { return mFilePath; };
		void setFilePath(wstring path) { mFilePath = path; };

		virtual void showExceptionDialog(bool fatal = false)override {
			wstring tempInfo = L"";
			tempInfo = L"";
		}
	};

	class RuntimeException : public Exception
	{
	public:
		RuntimeException(wstring ExceptionInfo) : Exception(ExceptionInfo) {};
	};

	template<typename T>
	class ArrayIndexOutOfBoundException : public Exception
	{
	private:
		T* mArrayAddress;
	public:
		ArrayIndexOutOfBoundException(wstring info, T* arr) :
			Exception(info),
			mArrayAddress(arr)
		{};

		void* getArrayAddress() { return (void*)mArrayAddress; };
	};
}