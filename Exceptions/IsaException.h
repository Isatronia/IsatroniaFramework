#pragma once
#include <iostream>
#include <string>
#include <Windows.h>

//#define __POSTERR(str) {MessageBox(0, str, L"Error", NULL);}

namespace Isatronia {
	using namespace std;

	template<typename T>
	concept isString = typeid(T) == typeid(string) || typeid(T) == typeid(wstring);

	template<typename T>
	void __POSTERR(wstring msg, wstring title = L"Error") {
		MessageBox(0, msg, title, NULL);
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
			__POSTERR(mExceptionInfo);
			if (fatal) {
				exit(-1);
			}
			return;
		}
	};

	template<typename T>
	class ArrayIndexOutOfBoundException : public Exception
	{
	private:
		T* mArrayAddress;
	public:
		ArrayIndexOutOfBoundException(wstring info, T* arr): 
			Exception(info),
			mArrayAddress(arr)
		{};

		void* getArrayAddress() { return (void*)mArrayAddress; };
	};
}