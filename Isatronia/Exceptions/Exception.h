#pragma once
#include <iostream>
#include <string>
#include <exception>
#include <Windows.h>

//#define __POSTERR(str) {MessageBox(0, str, L"Error", NULL);}

namespace Isatronia::Exception {
	
	using std::wstring;

	//--------------------------------------------------
	// Base Exception
	//--------------------------------------------------
	class Exception: public std::exception {
	private:
		wstring mExceptionInfo;

	public:
		Exception() = delete;
		Exception(wstring info);

		virtual wstring getExceptionInfo();

		virtual void showExceptionDialog(bool fatal = false);
	protected:
		void setExceptionInfo(wstring ExceptionInfo);
	};

	class FileException : public Exception
	{
	private:
		wstring mFilePath;
	public:
		FileException(wstring desc, wstring path);

		wstring getFilePath();
		void setFilePath(wstring path);

		virtual void showExceptionDialog(bool fatal = false)override;
	};

	class RuntimeException : public Exception
	{
	public:
		RuntimeException(wstring ExceptionInfo);
		RuntimeException(const wchar_t* ExceptionInfo);
	};


	//template<typename T>
	//class ArrayIndexOutOfBoundException : public Exception
	//{
	//private:
	//	T* mArrayAddress;
	//public:
	//	ArrayIndexOutOfBoundException(wstring info, T* arr) :
	//		Exception(info),
	//		mArrayAddress(arr)
	//	{};

	//	void* getArrayAddress() { return (void*)mArrayAddress; };
	//};
}