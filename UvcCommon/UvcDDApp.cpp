//***************************************************************************************
// UvcDDApp.cpp by Aaron Jsc (C) 2020 All Rights Reserved.
// licenced under CC BY-NC-SA License.
//***************************************************************************************

// defines: Change these settings to control your App.

#define CLIENT_WIDTH	1920
#define CLIENT_HEIGHT	1080
#define CLIENT_BPP		32

#include "UvcDDApp.h"
#include "../libs/dxerr.cpp"
#include "IsaUtils.h"
#include <Windows.h>

#define __POSTERR(str) {MessageBoxA(0, str, "Error", NULL);}
#define UvcDXInit_s(res, str) { if (FAILED(res)) {__POSTERR(str);return 0; } }
#define __ZEROMEM(obj) {memset(&obj, 0, sizeof(obj));}

#define __RGB16BIT555(r,g,b) ((b & 31) + ((g & 31) << 5) + ((r & 31) << 10))
#define __RGB16BIT565(r,g,b) ((b & 31) + ((g & 63) << 5) + ((r & 31) << 11))
#define __RGB32BIT(a,r,g,b) ((b) + ((g) << 8) + ((r) << 16) + ((a) << 24))

namespace IsaD9Frame {


	LRESULT CALLBACK
		MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		// Forward hwnd on because we can get messages (e.g., WM_CREATE)
		// before CreateWindow returns, and thus before mhMainWnd is valid.
		return UvcDDApp::GetApp()->MsgProc(hwnd, msg, wParam, lParam);
	}

	UvcDDApp* UvcDDApp::mApp = nullptr;

	UvcDDApp::UvcDDApp(HINSTANCE hInstance)
	{
		mhAppInst = hInstance;
		mhMainWnd = NULL;

		// member Init
		mAppPaused = false;
		mMinimized = false;
		mMaximized = false;
		mResizeing = false;
		mFullScreenState = false;

		mClientRect = { 0 };

		// directX Init
		mlpDD7 = nullptr;
		mlpDDSurefacePrimary = nullptr;
		mlpDDSurefaceBackBuffer = nullptr;
		mlpDDClipper = nullptr;

		memset(&mDDSD, 0, sizeof(mDDSD));
		memset(&mDDPF, 0, sizeof(mDDPF));

		mCurBackBuffer = 1;

		mMainWndCaption = L"UvcDDApp";
		mClientWidth = CLIENT_WIDTH;
		mClientHeight = CLIENT_HEIGHT;
		mClientBPP = CLIENT_BPP;
		assert(mApp == nullptr);
		mApp = this;
		return;
	}

	UvcDDApp::~UvcDDApp()
	{
		memset(&mDDSD, 0, sizeof(mDDSD));
		ReleaseCOM(mlpDDClipper);
		ReleaseCOM(mlpDDSurefaceBackBuffer);
		ReleaseCOM(mlpDDSurefacePrimary);
		ReleaseCOM(mlpDD7);
		return;
	}

	LRESULT UvcDDApp::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		// TODO: 在此处添加实现代码.
		switch (msg)
		{
		case WM_ACTIVATE:
			if (LOWORD(wParam) == WA_INACTIVE)
			{
				// when the Window is inactive, pause the game.
				mAppPaused = true;
				mTimer.Stop();
			}
			else
			{
				mAppPaused = false;
				mTimer.Start();
			}
			return 0;
			break;
		case WM_COMMAND:
		{
		}
		break;
		case WM_KEYDOWN:
			switch (wParam)
			{
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;
			case VK_F2:
				mAppPaused = !mAppPaused;
				break;
			default:
				break;
			}
			break;
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			// TODO: 在此处添加使用 hdc 的任何绘图代码...
			EndPaint(hwnd, &ps);
		}
		break;
		case WM_MOVE:
		{
			OnResize();
		}
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
		return 0;
	}

	UvcDDApp* UvcDDApp::GetApp()
	{
		// TODO: 在此处添加实现代码.
		return mApp;
	}

	HINSTANCE UvcDDApp::AppInst()
	{
		// TODO: 在此处添加实现代码.
		return mhAppInst;
	}

	HWND UvcDDApp::MainWnd()
	{
		// TODO: 在此处添加实现代码.
		return mhMainWnd;
	}

	float UvcDDApp::AspectRatio()
	{
		// TODO: 在此处添加实现代码.
		return (float)mClientWidth / mClientHeight;
	}

	int UvcDDApp::Run()
	{
		// TODO: 在此处添加实现代码.
		MSG msg = { 0 };

		mTimer.Reset();

		ULONGLONG t1 = GetTickCount64(), t2 = GetTickCount64();

		while (msg.message != WM_QUIT)
		{
			// If there are Window messages then process them.
			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			// Otherwise, do animation/game stuff.
			else
			{
				t1 = GetTickCount64();
				if (t1 - t2 > 33)
				{
					if (!mAppPaused)
					{
						Update(mTimer);
					}
					else
					{
						Sleep(100);
					}
					t2 = GetTickCount64();
				}
			}
		}

		return 0;
	}

	bool UvcDDApp::Initialize()
	{
		// TODO: 在此处添加实现代码.
		if (!InitMainWindow())
		{
			MessageBoxA(0, "InitWindow Failed.", "", MB_OK);
			return false;
		}

		if (!InitDDraw())
		{
			MessageBoxA(0, "InitDD Failed.", "", MB_OK);
			return false;
		}

		OnResize();

		return true;
	}

	void UvcDDApp::OnResize()
	{
		if (mhMainWnd != nullptr)
		{
			GetWindowRect(mhMainWnd, &mClientRect);
		}
		if (mlpDDSurefacePrimary != nullptr)
		{
			memset(&mDDPF, 0, sizeof(mDDPF));
			mDDPF.dwSize = sizeof(mDDPF);
			mlpDDSurefacePrimary->GetPixelFormat(&mDDPF);
		}

		return;
	}

	void UvcDDApp::Update(const UvcTimer& Timer)
	{
		// TODO: 在此处添加实现代码.
		RECT destRect, srcRect;
		__ZEROMEM(destRect);
		__ZEROMEM(srcRect);

		destRect.top = 0;
		destRect.bottom = mClientHeight;
		destRect.left = 0;
		destRect.right = mClientWidth;

		srcRect.top = 0;
		srcRect.bottom = mClientHeight;
		srcRect.left = 0;
		srcRect.right = mClientWidth;

		memset(&mDDSD, 0, sizeof(mDDSD));
		mDDSD.dwSize = sizeof(mDDSD);
		if (FAILED(mlpDDSurefacePrimary->Lock(NULL, &mDDSD,
			DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT,
			NULL)))
		{
			return;
		}

		Draw(Timer);

		if (FAILED(mlpDDSurefacePrimary->Unlock(NULL)))
		{
			MessageBoxA(mhMainWnd, "Unlock Falied", "Error", MB_OK);
			PostQuitMessage(0);
			return;
		}

		if (mFullScreenState)
		{
			if (FAILED(mlpDDSurefacePrimary->Flip(NULL, DDFLIP_WAIT)))
			{
				MessageBoxA(NULL, "Flip blocked", "Error", MB_OK);
				//PostQuitMessage(0);
				return;
			}
		}
		else
		{
			if (FAILED(mlpDDSurefacePrimary->Blt(&destRect, mlpDDSurefaceBackBuffer, &srcRect, DDBLT_WAIT, NULL)))
			{
				__POSTERR("Blt Failed");
				PostQuitMessage(0);
				return;
			}
		}
		return;
	}

	//void UvcDDApp::Draw(const UvcTimer& Timer)
	//{
	//	// TODO: 在此处添加实现代码.
	//}

	LPDIRECTDRAWCLIPPER UvcDDApp::DDrawAttachClipper()
	{
		// init index and Clipper
		size_t index = 0;
		size_t nCnt = mClipperRECTQue.size();
		LPDIRECTDRAWCLIPPER lpddClipper = nullptr;
		LPRGNDATA region_data = nullptr;

		if (mClipperRECTQue.size() == 0)
		{
			mClipperRECTQue.push({ 0 ,0, mClientWidth, mClientHeight });
		}

		// Attach Clipper
		UvcDXInit_s(
			mlpDD7->CreateClipper(0, &lpddClipper, NULL),
			"Clipper Attach falied");

		// fill RGNDATA
		// first allocate memory
		region_data = (LPRGNDATA)malloc(sizeof(RGNDATAHEADER) +
			(mClipperRECTQue.size() * sizeof(RECT)));

		// then Fill Rects
		for (index = 0; index < mClipperRECTQue.size(); index++)
		{
			memcpy(region_data->Buffer + index, &mClipperRECTQue.front(), sizeof(RECT));
			mClipperRECTQue.push(mClipperRECTQue.front());
			mClipperRECTQue.pop();
		}

		// set up header
		region_data->rdh.dwSize = sizeof(RGNDATAHEADER);
		region_data->rdh.iType = RDH_RECTANGLES;
		region_data->rdh.nCount = mClipperRECTQue.size();
		region_data->rdh.nRgnSize = mClipperRECTQue.size() * sizeof(RECT);
		region_data->rdh.rcBound.left = 64000;
		region_data->rdh.rcBound.top = 64000;
		region_data->rdh.rcBound.right = -64000;
		region_data->rdh.rcBound.bottom = -64000;

		//find bounds of all Clipping regions
		for (index = 0; index < nCnt; index++)
		{
			//left
			if (mClipperRECTQue.front().left < region_data->rdh.rcBound.left)
			{
				region_data->rdh.rcBound.left = mClipperRECTQue.front().left;
			}
			//right
			if (mClipperRECTQue.front().right > region_data->rdh.rcBound.right)
			{
				region_data->rdh.rcBound.right = mClipperRECTQue.front().right;
			}
			//top
			if (mClipperRECTQue.front().top < region_data->rdh.rcBound.top)
			{
				region_data->rdh.rcBound.top = mClipperRECTQue.front().top;
			}
			//bottom
			if (mClipperRECTQue.front().bottom > region_data->rdh.rcBound.bottom)
			{
				region_data->rdh.rcBound.bottom = mClipperRECTQue.front().bottom;
			}
		}

		// now we computed the bounding region and set up the data
		// now, let's set the clipping list.
		if (FAILED(lpddClipper->SetClipList(region_data, NULL)))
		{
			free(region_data);
			__POSTERR("SetClipList Failed");
			return NULL;
		}

		if (FAILED(mlpDDSurefacePrimary->SetClipper(lpddClipper)))
		{
			free(region_data);
			__POSTERR("BkBuffer SetClipper failed");
			return NULL;
		}

		return lpddClipper;
	}

	bool UvcDDApp::InitMainWindow()
	{
		// TODO: 在此处添加实现代码.
		WNDCLASSEX wc;
		if (mhAppInst == nullptr)
		{
			MessageBoxW(0, L"Null instance.", 0, MB_OK);
			return false;
		}

		memset(&wc, 0, sizeof(wc));

		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_DBLCLKS | CS_OWNDC |
			CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = MainWndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = mhAppInst;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = NULL;
		wc.lpszMenuName = NULL;
		wc.lpszClassName = L"MainWnd";
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		if (!RegisterClassEx(&wc))
		{
			MessageBoxW(0, L"RegisterClass Failed.", 0, MB_OK);
			return false;
		}

		RECT r = { 0,0,mClientWidth, mClientHeight };
		AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, false);
		int width = r.right - r.left;
		int height = r.bottom - r.top;

		if (!(mhMainWnd = CreateWindowEx(

			NULL,														// extrened style
			L"MainWnd",													// class
			(mFullScreenState ? NULL : mMainWndCaption.c_str()),		//title
			(mFullScreenState ? WS_POPUPWINDOW : WS_OVERLAPPEDWINDOW),	// windows style //| WS_VISIBLE
			0,															// initial x, y
			0,
			mClientWidth,												// initial width, height
			mClientHeight,
			NULL,														// handle to parent
			NULL,														// handle to menu
			mhAppInst,													// instance of this application
			NULL
		)))
		{
			MessageBoxW(0, L"CreateWindow Failed.", 0, MB_OK);
			return false;
		}

		ShowWindow(mhMainWnd, SW_SHOW);
		UpdateWindow(mhMainWnd);

		return true;
	}

	bool UvcDDApp::InitDDraw()
	{
		// TODO: 在此处添加实现代码.

		if (FAILED(DirectDrawCreateEx(NULL, (void**)&mlpDD7, IID_IDirectDraw7, NULL)))
		{
			MessageBoxW(0, L"DD Creat Failed.", 0, MB_OK);
			return false;
		}

		if (mFullScreenState == true)
		{
			if (FAILED(mlpDD7->SetCooperativeLevel(
				mhMainWnd,
				DDSCL_FULLSCREEN | DDSCL_ALLOWMODEX | DDSCL_EXCLUSIVE | DDSCL_ALLOWREBOOT)))
			{
				MessageBoxA(0, "Set Coop Level Failed.", 0, MB_OK);
				return false;
			}
		}
		else
		{
			UvcDXInit_s(
				mlpDD7->SetCooperativeLevel(mhMainWnd, DDSCL_NORMAL),
				"Set Coop Level Failed.");
		}

		UvcDXInit_s(
			mlpDD7->SetDisplayMode(mClientWidth, mClientHeight, mClientBPP, 0, 0),
			"SetDisplayMode Error"
		);

		if (!(CreatSwapChain()))
		{
			return false;
		}

		if (!(DDrawAttachClipper()))
		{
			__POSTERR("Attach Clipper Failed");
			return false;
		}

		return true;
	}

	bool UvcDDApp::CreatCommandObjects()
	{
		// TODO: 在此处添加实现代码.
		return true;
	}

	bool UvcDDApp::CreatSwapChain()
	{
		if (!mFullScreenState)
		{
			memset(&mDDSD, 0, sizeof(mDDSD));
			mDDSD.dwSize = sizeof(mDDSD);
			mDDSD.dwFlags = DDSD_CAPS;
			mDDSD.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

			UvcDXInit_s(
				mlpDD7->CreateSurface(&mDDSD, &mlpDDSurefacePrimary, NULL),
				"Primary Surface Creat Failed");

			memset(&mDDSD, 0, sizeof(mDDSD));
			mDDSD.dwSize = sizeof(mDDSD);
			mDDSD.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_CKSRCBLT;

			mDDSD.dwHeight = mClientHeight;
			mDDSD.dwWidth = mClientWidth;

			UvcDXInit_s(
				mlpDD7->CreateSurface(&mDDSD, &mlpDDSurefaceBackBuffer, NULL),
				"Back Buffer Surface Creat Failed"
			);

			return true;
		}

		memset(&mDDSD, 0, sizeof(mDDSD));
		mDDSD.dwSize = sizeof(mDDSD);
		mDDSD.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
		mDDSD.dwBackBufferCount = 1;
		mDDSD.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_COMPLEX | DDSCAPS_FLIP;

		HRESULT debug = 0;

		if (FAILED(debug = mlpDD7->CreateSurface(&mDDSD, &mlpDDSurefacePrimary, NULL)))
		{
			//__POSTERR("Primery Surface Creat Failed");
			DXTrace(__FILEW__, __LINE__, debug, NULL, TRUE);
			return false;
		}

		mDDSD.ddsCaps.dwCaps = DDSCAPS_BACKBUFFER;

		UvcDXInit_s(
			mlpDDSurefacePrimary->GetAttachedSurface(&mDDSD.ddsCaps, &mlpDDSurefaceBackBuffer),
			"Back Buffer Surface Creat Failed"
		);

		return true;
	}

	void UvcDDApp::FlushCommandQueue()
	{
		// TODO: 在此处添加实现代码.
	}

	// PlotPixel -- plot pixel on a Surface
	// if is 8-bit deepth, only write in r.
	void UvcDDApp::PlotPixel(DDSURFACEDESC2& ddsd, int x, int y, int r, int g, int b, int a)
	{
		if (ddsd.lpSurface == nullptr)	return;
		if (y <= 0)				return;
		if (x <= 0)				return;
		if (y > ddsd.dwHeight)	return;
		if (x > ddsd.dwWidth)	return;
		if (r < 0)				return;

		if (r == 0 && g == 255 && b == 0) return;

		UCHAR	pixelFor16BIT = 0;
		UINT	pixelFor32Bit = 0;

		UCHAR* buffer = (UCHAR*)ddsd.lpSurface;
		USHORT* bufferFor16bit = (USHORT*)ddsd.lpSurface;
		UINT* bufferFor32bit = (UINT*)ddsd.lpSurface;

		switch (mDDPF.dwRGBBitCount)
		{
			// __RGB16BIT555 mode:
		case 15:
		{
			pixelFor16BIT = __RGB16BIT555(r, g, b);
			bufferFor16bit[x + (y * (int)(ddsd.lPitch >> 1))] = pixelFor16BIT;
		}
		break;
		// __RGB16BIT565 mode
		case 16:
		{
			pixelFor16BIT = __RGB16BIT565(r, g, b);
			bufferFor16bit[x + (y * (int)(ddsd.lPitch >> 1))] = pixelFor16BIT;
		}
		break;
		// __RGB 24BIT mode
		case 24:
		{
			pixelFor32Bit = __RGB32BIT(0, r, g, b);
			bufferFor32bit[x + (y * (int)(ddsd.lPitch >> 2))] = pixelFor32Bit;
		}
		break;
		// __RGB32BIT mode
		case 32:
		{
			pixelFor32Bit = __RGB32BIT(a, r, g, b);
			bufferFor32bit[x + (y * (int)(ddsd.lPitch >> 2))] = pixelFor32Bit;
		}
		break;
		default:
			break;
		}

		buffer = nullptr;
		bufferFor16bit = nullptr;
		bufferFor32bit = nullptr;
		return;
	}

	int UvcDDApp::DrawImageToDDSurface(UvcImage& ubmp, DDSURFACEDESC2 ddsd, RECT SrcRect, int x, int y)
	{
		//UCHAR r = 0, g = 0, b = 0;
		RGBInfo col = RGBInfo();

		for (int j = 0; j < SrcRect.bottom - SrcRect.top; j++)
		{
			for (int i = 0; i < SrcRect.right - SrcRect.left; i++)
			{
				col = ubmp.getPixelRGB(SrcRect.left + i, SrcRect.top + j);
				//PlotPixel(ddsd, mClientRect.left + x, mClientRect.top + y, r, g, b);
				PlotPixel(ddsd, x + i, y + j, col.r, col.g, col.b);
			}
		}

		return 1;
	}

	RGBInfo UvcDDApp::GetPixelRGB(int x, int y) const
	{
		RGBInfo col;
		UCHAR* buffer = (UCHAR*)mDDSD.lpSurface;

		DWORD addr = 0;

		switch (mDDPF.dwRGBBitCount)
		{
		case 24:
			addr = (x + x + x) + (y * mDDSD.lPitch);
			col.b = buffer[addr + 0];
			col.g = buffer[addr + 1];
			col.r = buffer[addr + 2];
			break;
		case 32:
			addr = (x + x + x + x) + (y * mDDSD.lPitch);
			col.b = buffer[addr + 0];
			col.g = buffer[addr + 1];
			col.r = buffer[addr + 2];
			break;
		default:
			break;
		}
		return col;
	}
}
/*

// 由于有了dxerr就被废弃的函数

// ------------------------------
// DXTraceW函数
// ------------------------------
// 在调试输出窗口中输出格式化错误信息，可选的错误窗口弹出(已汉化)
// [In]strFile			当前文件名，通常传递宏__FILEW__
// [In]hlslFileName     当前行号，通常传递宏__LINE__
// [In]hr				函数执行出现问题时返回的HRESULT值
// [In]strMsg			用于帮助调试定位的字符串，通常传递L#x(可能为NULL)
// [In]bPopMsgBox       如果为TRUE，则弹出一个消息弹窗告知错误信息
// 返回值: 形参hr
HRESULT WINAPI DXTraceW(_In_z_ const WCHAR* strFile, _In_ DWORD dwLine, _In_ HRESULT hr,
	_In_opt_ const WCHAR* strMsg, _In_ bool bPopMsgBox)
{
	WCHAR strBufferFile[MAX_PATH];
	WCHAR strBufferLine[128];
	WCHAR strBufferError[300];
	WCHAR strBufferMsg[1024];
	WCHAR strBufferHR[40];
	WCHAR strBuffer[3000];

	swprintf_s(strBufferLine, 128, L"%lu", dwLine);
	if (strFile)
	{
		swprintf_s(strBuffer, 3000, L"%ls(%ls): ", strFile, strBufferLine);
		OutputDebugStringW(strBuffer);
	}

	size_t nMsgLen = (strMsg) ? wcsnlen_s(strMsg, 1024) : 0;
	if (nMsgLen > 0)
	{
		OutputDebugStringW(strMsg);
		OutputDebugStringW(L" ");
	}
	// Windows SDK 8.0起DirectX的错误信息已经集成进错误码中，可以通过FormatMessageW获取错误信息字符串
	// 不需要分配字符串内存
	FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		strBufferError, 256, nullptr);

	WCHAR* errorStr = wcsrchr(strBufferError, L'\r');
	if (errorStr)
	{
		errorStr[0] = L'\0';	// 擦除FormatMessageW带来的换行符(把\r\n的\r置换为\0即可)
	}

	swprintf_s(strBufferHR, 40, L" (0x%0.8x)", hr);
	wcscat_s(strBufferError, strBufferHR);
	swprintf_s(strBuffer, 3000, L"错误码含义：%ls", strBufferError);
	OutputDebugStringW(strBuffer);

	OutputDebugStringW(L"\n");

	if (bPopMsgBox)
	{
		wcscpy_s(strBufferFile, MAX_PATH, L"");
		if (strFile)
			wcscpy_s(strBufferFile, MAX_PATH, strFile);

		wcscpy_s(strBufferMsg, 1024, L"");
		if (nMsgLen > 0)
			swprintf_s(strBufferMsg, 1024, L"当前调用：%ls\n", strMsg);

		swprintf_s(strBuffer, 3000, L"文件名：%ls\n行号：%ls\n错误码含义：%ls\n%ls您需要调试当前应用程序吗？",
			strBufferFile, strBufferLine, strBufferError, strBufferMsg);

		int nResult = MessageBoxW(GetForegroundWindow(), strBuffer, L"错误", MB_YESNO | MB_ICONERROR);
		if (nResult == IDYES)
			DebugBreak();
	}

	return hr;
}

#endif

// 老旧的被废弃的表面创建函数。

	// TODO: 在此处添加实现代码.
	memset(&mDDSD, 0, sizeof(mDDSD));
	mDDSD.dwSize = sizeof(mDDSD);
	mDDSD.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
	mDDSD.dwBackBufferCount = mCurBackBuffer;
	mDDSD.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_COMPLEX | DDSCAPS_FLIP;	//primary surface

	HRESULT debug = 0;

	if (FAILED(debug = mlpDD7->CreateSurface(&mDDSD, &mlpDDSurefacePrimary, NULL)))
	{
		__POSTERR(L"Primery Surface Creat Failed");
#ifdef DEBUG
		DXTraceW(__FILEW__, __LINE__, debug, L"Primery Surface Creat Failed", TRUE);
#endif // DEBUG
		return false;
	}

	mDDSD.ddsCaps.dwCaps = DDSCAPS_BACKBUFFER;

	UvcDXInit_s(
		mlpDDSurefacePrimary->GetAttachedSurface(&mDDSD.ddsCaps, &mlpDDSurefaceBackBuffer),
		L"Back Buffer Surface Creat Failed"
	);

*/