//--------------------------------------------------------------------------------------
// File: I18n.cpp
//
// Copyright (c) Ishgrina. All rights reserved.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------


#include "I18n.h"
#include "../Exceptions/Exception.h"


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
			throw new RuntimeException(L"Locale language detect failed, English is set as default.");
		}
		return wstring(name);
	}

	void LanguageConfig::setLanguageLocal(wstring LanguageLocal)
	{
		mLanguageLocal = LanguageLocal;
	}


	//-------------------------------------------------------------------------------
	// CoreDict
	//-------------------------------------------------------------------------------
	void CoreDict::loadDictFromeLocal(wstring dictFilePath)
	{
		return;
	}

	wstring CoreDict::getStringByKey(wstring key)
	{
		return L"";
	}
}

