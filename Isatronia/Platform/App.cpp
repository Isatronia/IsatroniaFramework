//***************************************************************************************
// App.cpp by Aaron Jsc (C) 2020 All Rights Reserved.
// licenced under CC BY-NC-SA License.
//***************************************************************************************



#include "App.h"
#include "../Exceptions/Exception.h"
#include "../../libs/dxerr.cpp"



namespace Isatronia::Windows {
	using namespace Exception;

	LRESULT CALLBACK
		AppMainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		// Forward hwnd on because we can get messages (e.g., WM_CREATE)
		// before CreateWindow returns, and thus before mhMainWnd is valid.
		return App::GetApp()->MsgProc(hwnd, msg, wParam, lParam);
	}

	App* App::mApp = nullptr;

	App::App(HINSTANCE hInstance)
	{
		mhAppInst = hInstance;
		mhMainWnd = NULL;

		// member Init
		mAppPaused = false;
		mMinimized = false;
		mMaximized = false;
		mResizeing = false;

		mMainWndCaption	=	WINDOW_CAPTION;
		mClientWidth	=	CLIENT_WIDTH;
		mClientHeight	=	CLIENT_HEIGHT;
		mClientBPP		=	CLIENT_BPP;
		assert(mApp == nullptr);
		mApp = this;
		return;
	}

	App::~App()
	{
		return;
	}

	LRESULT App::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
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

	App* App::GetApp()
	{
		// TODO: 在此处添加实现代码.
		return mApp;
	}

	HINSTANCE App::getAppInst()
	{
		// TODO: 在此处添加实现代码.
		return mhAppInst;
	}

	HWND App::getMainWnd()
	{
		// TODO: 在此处添加实现代码.
		return mhMainWnd;
	}

	float App::getAspectRatio()
	{
		// TODO: 在此处添加实现代码.
		return (float)mClientWidth / mClientHeight;
	}

	int App::Run()
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

	void App::Initialize()
	{
		if (!InitMainWindow())
		{
			MessageBoxA(0, "InitWindow Failed.", "", MB_OK);
			throw(new RuntimeException(L"InitWindow Failed."));
			return;
		}
		OnResize();

		return;
	}

	void App::OnResize()
	{
		if (mhMainWnd != nullptr)
		{
			GetWindowRect(mhMainWnd, &mClientRect);
		}
		return;
	}

	void App::Update(const Timer& Timer)
	{
		
	}

	//void App::Draw(const UvcTimer& Timer)
	//{
	//	// TODO: 在此处添加实现代码.
	//}

	

	bool App::InitMainWindow()
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
		wc.lpfnWndProc = AppMainWndProc;
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
			mMainWndCaption.c_str(),									//title
			WS_OVERLAPPEDWINDOW,										// windows style //| WS_VISIBLE
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

	

	bool App::CreatCommandObjects()
	{
		// TODO: 在此处添加实现代码.
		return true;
	}

	

	void App::FlushCommandQueue()
	{
		// TODO: 在此处添加实现代码.
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