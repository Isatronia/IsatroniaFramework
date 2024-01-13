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
		English_US,
		Chinese_Simplifieded,
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
		map<wstring, wstring> mDict;
	//---------------------------------------
	// Methods
	//---------------------------------------
	private:
		void loadDictFromeLocal(wstring);
	public:
		wstring getStringByKey(wstring key);
	};


}