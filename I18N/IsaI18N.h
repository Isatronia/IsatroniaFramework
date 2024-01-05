#pragma once

#include <iostream>
#include <string>
#include <Windows.h>

#include "../Exceptions/IsaException.h"

namespace IsaFrame::I18N {
	using namespace std;

	wstring CheckLocal() {
		LCID lcid = GetThreadLocale();
		wchar_t name[LOCALE_NAME_MAX_LENGTH];
		if (LCIDToLocaleName(lcid, name, LOCALE_NAME_MAX_LENGTH, NULL) == 0) {
			throw(new Exception::RuntimeException(L"Locale language detect failed, English is set as default."));
		}
		return wstring(name);
	}

	class LanguageConfig {
	private:
		wstring mLanguageLocal;
	public:
		void setLanguageLocal(wstring LanguageLocal) {
			mLanguageLocal = LanguageLocal;
		}

	};
}