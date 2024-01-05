//***************************************************************************************
// UvcDDApp.h by Aaron Jsc (C) 2020 All Rights Reserved.
// licenced under CC BY-NC-SA License.
//***************************************************************************************

#pragma once

#include <ddraw.h>
#include <iostream>
#include <cassert>
#include <wrl.h>
#include <queue>

#include "IsaUtils.h"
#include "UvcTimer.h"
#include "UvcImage.h"

#pragma comment(lib,"ddraw.lib")
#pragma comment(lib, "dxguid.lib")

#define ReleaseCOM(x) { if(x){ x->Release(); x = nullptr; } }

namespace IsaFrame::IsaD9Frame {

	class UvcDDApp
	{
		// constructor and destructor
	protected:
		UvcDDApp(HINSTANCE hInstance);
		UvcDDApp(const UvcDDApp& res) = delete;
		UvcDDApp& operator=(const UvcDDApp& res) = delete;
		virtual ~UvcDDApp();

	public:
		// get pointer 2 this App class
		static UvcDDApp* GetApp();
		// get this app's instance
		HINSTANCE			AppInst();
		HWND				MainWnd();
		float				AspectRatio();

		int Run();

		virtual bool	Initialize();
		virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	protected:
		virtual void OnResize();
		virtual void Update(const UvcTimer& Timer);
		virtual void Draw(const UvcTimer& Timer) = 0;
		//virtual void DrawWithDX() = 0;

		// to be override for handling mouse input.
		virtual void OnMouseDown(WPARAM btnState, int x, int y) { return; };
		virtual void OnMouseUp(WPARAM btnState, int x, int y) { return; };
		virtual void OnMouseMove(WPARAM btnState, int x, int y) { return; };

		// Attach a Clipper to the BackBufferSurface, using mClipperRECTQue
		virtual LPDIRECTDRAWCLIPPER DDrawAttachClipper();

	protected:
		bool InitMainWindow();
		bool InitDDraw();

		bool CreatCommandObjects();
		bool CreatSwapChain();

		void FlushCommandQueue();
		void PlotPixel(DDSURFACEDESC2& ddsd, int x, int y, int r, int g = -1, int b = -1, int a = 0);

		// WARNING - Must Run in Draw func!!!!
		int DrawImageToDDSurface(UvcImage& ubmp, DDSURFACEDESC2 ddsd, RECT SrcRect, int x, int y);
		RGBInfo GetPixelRGB(int x, int y) const;

		DDSURFACEDESC2 GetDDSD() { return mDDSD; };
	public:
		LPDIRECTDRAW7 mlpDD7;

	protected:

		static UvcDDApp* mApp;

		HINSTANCE	mhAppInst;
		HWND		mhMainWnd;

		bool		mAppPaused;
		bool		mMinimized;
		bool		mMaximized;
		bool		mResizeing;
		bool		mFullScreenState;

		UvcTimer mTimer;

		LPDIRECTDRAWSURFACE7	mlpDDSurefacePrimary;
		LPDIRECTDRAWSURFACE7	mlpDDSurefaceBackBuffer;
		LPDIRECTDRAWCLIPPER		mlpDDClipper;

		DDSURFACEDESC2	mDDSD;
		DDPIXELFORMAT	mDDPF;

		RECT	mClientRect;

		static const int SwapChainBufferCount = 2;
		int mCurBackBuffer;

		std::wstring mMainWndCaption;
		int mClientWidth;
		int mClientHeight;
		int mClientBPP;
		// always save depth of Surface to make sure u r using the right fn. to paint.
		int mSurfaceBPP;

		std::queue<RECT> mClipperRECTQue;
	};
}