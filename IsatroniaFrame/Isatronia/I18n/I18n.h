//--------------------------------------------------------------------------------------
// File: I18n.h
//
// Copyright (c) Ishgrina. All rights reserved.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------
#pragma once

#include <iostream>
#include <string>
#include <map>
#include <Windows.h>

namespace Isatronia::I18N {
	using namespace std;

	enum class DisplayLanguage {
		English,
		Chinese_Simplified,
	};

	wstring CheckLocal();

	class LanguageConfig {
	private:
		wstring mLanguageLocal;
	public:
		void setLanguageLocal(wstring LanguageLocal);
	};

	class CoreDict
	{
	private:
		static std::map<std::wstring, std::wstring> mDict;
	//---------------------------------------
	// Methods
	//---------------------------------------
	private:
		void loadDictFromeLocal(std::wstring);
	public:
		CoreDict();
		std::wstring getStringByKey(std::wstring key);
	};


}