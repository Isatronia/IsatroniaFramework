//***************************************************************************************
// App.h by Aaron Jsc (C) 2020 All Rights Reserved.
// licenced under CC BY-NC-SA License.
//***************************************************************************************

#pragma once

#include <ddraw.h>
#include <iostream>
#include <cassert>
#include <wrl.h>
#include <queue>

#include "../../libs/dxerr.h"
#include "../Framework/Timer.h"
#include "../Resource/Image.h"
#include "../Exceptions/Exception.h"

#pragma comment(lib,"ddraw.lib")
#pragma comment(lib, "dxguid.lib")

// defines: Change these settings to control your App.
#define CLIENT_WIDTH	1920
#define CLIENT_HEIGHT	1080
#define CLIENT_BPP		32
#define WINDOW_CAPTION	L"Isatronia Application"

#define ReleaseCOM(x) { if(x){ x->Release(); x = nullptr; } }
#define __POSTERR(str) {MessageBoxA(0, str, "Error", NULL);}
#define UvcDXInit_s(res, str) { if (FAILED(res)) {__POSTERR(str);return 0; } }
#define __ZEROMEM(obj) {memset(&obj, 0, sizeof(obj));}

#define __RGB16BIT555(r,g,b) ((b & 31) + ((g & 31) << 5) + ((r & 31) << 10))
#define __RGB16BIT565(r,g,b) ((b & 31) + ((g & 63) << 5) + ((r & 31) << 11))
#define __RGB32BIT(a,r,g,b) ((b) + ((g) << 8) + ((r) << 16) + ((a) << 24))

using namespace Isatronia::Exception;


// Here is Class definiation
namespace Isatronia::Windows {


	class App
	{
	protected:

		static App* mApp;

		HINSTANCE	mhAppInst;
		HWND		mhMainWnd;

		bool		mAppPaused;
		bool		mMinimized;
		bool		mMaximized;
		bool		mResizeing;

		Timer mTimer;

		RECT	mClientRect;


		std::wstring mMainWndCaption;
		int mClientWidth;
		int mClientHeight;
		int mClientBPP;

		// constructor and destructor
	protected:
		App(HINSTANCE hInstance);
		App(const App& res) = delete;
		App& operator=(const App& res) = delete;
		virtual ~App();

	public:
		// get pointer 2 this App class
		static App* GetApp();
		// get this app's instance
		HINSTANCE			getAppInst();
		HWND				getMainWnd();
		float				getAspectRatio();

		int Run();

		virtual void	Initialize();
		virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	protected:

		virtual bool InitMainWindow();
		bool CreatCommandObjects();
		void FlushCommandQueue();

		// Three func about window
		virtual void OnResize();
		virtual void Update(const Timer& Timer);
		virtual void Draw(const Timer& Timer) = 0;

		// to be override for handling mouse input.
		virtual void OnMouseDown(WPARAM btnState, int x, int y) { return; };
		virtual void OnMouseUp(WPARAM btnState, int x, int y) { return; };
		virtual void OnMouseMove(WPARAM btnState, int x, int y) { return; };

	};
}