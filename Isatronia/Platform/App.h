//--------------------------------------------------------------------------------------
// File: App.h
//
// Copyright (c) Ishgrina. All rights reserved.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------
#pragma once


#include <iostream>
#include <cassert>
#include <wrl.h>
#include <queue>

#include "../Framework/Timer.h"
#include "../Resource/Image.h"
#include "../Exceptions/Exception.h"


// defines: Change these settings to control your App.
#define CLIENT_WIDTH	1920
#define CLIENT_HEIGHT	1080
#define CLIENT_BPP		32
#define WINDOW_CAPTION	L"Isatronia Application"

using namespace Isatronia::Exception;


// Here is Class definiation
namespace Isatronia::Windows {
	using namespace Isatronia::Framework;

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