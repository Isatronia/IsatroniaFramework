//***************************************************************************************
// App.cpp by Aaron Jsc (C) 2020 All Rights Reserved.
// licenced under CC BY-NC-SA License.
//***************************************************************************************



#include "App.h"
#include "../Exceptions/Exception.h"
#include "../../libs/dxerr.h"



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