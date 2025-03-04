//--------------------------------------------------------------------------------------
// File: I18n.cpp
//
// Copyright (c) Ishgrina. All rights reserved.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------

#include "I18n.h"
#include "Exception.h"
#include "RuntimeException.h"

namespace Isatronia::I18N
{
	using std::wstring;
	using namespace Isatronia::Exception;

	wstring CheckLocal()
	{
		LCID lcid = GetThreadLocale();
		wchar_t name[LOCALE_NAME_MAX_LENGTH];
		if ( LCIDToLocaleName(lcid, name, LOCALE_NAME_MAX_LENGTH, NULL) == 0 )
		{
			throw new RuntimeException("Locale language detect failed, English is set as default.");
		}
		return wstring(name);
	}

	void LanguageConfig::setLanguageLocal(wstring LanguageLocal)
	{
		mLanguageLocal = LanguageLocal;
		return;
	}

	//-------------------------------------------------------------------------------
	// CoreDict
	//-------------------------------------------------------------------------------
	std::map<std::wstring, std::wstring> CoreDict::mDict = std::map<std::wstring, std::wstring>();

	CoreDict::CoreDict()
	{
		if ( CoreDict::mDict.size() == 0 )
		{
			CoreDict::mDict = std::map<std::wstring, std::wstring>();
		}
		return;
	}
	void CoreDict::loadDictFromeLocal(std::wstring dictFilePath)
	{
		return;
	}

	std::wstring CoreDict::getStringByKey(std::wstring key)
	{
		return L"";
	}
}