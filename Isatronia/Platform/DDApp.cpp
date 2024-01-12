#include "DDApp.h"

#include "../../libs/dxerr.h"
#include "../Resource/RGBInfo.h"
#include "../Framework/Macro.h"


namespace Isatronia::Windows {

	using Isatronia::Resource::RGBInfo;
	using Isatronia::Resource::RGBAInfo;

	template<typename T>
	void InitializeWithZero(T& obj) {
		memset(&obj, 0, sizeof(obj));
		return;
	}

	LRESULT CALLBACK
		DDAppMainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		// Forward hwnd on because we can get messages (e.g., WM_CREATE)
		// before CreateWindow returns, and thus before mhMainWnd is valid.
		return DDApp::GetApp()->MsgProc(hwnd, msg, wParam, lParam);
	}

	DDApp::DDApp(HINSTANCE hInstance) : App(hInstance) {
		// directX Init
		mDD7 = nullptr;
		mlpDDSurefacePrimary = nullptr;
		mlpDDSurefaceBackBuffer = nullptr;
		mlpDDClipper = nullptr;

		mFullScreenState = false;

		memset(&mDDSD, 0, sizeof(mDDSD));
		memset(&mDDPF, 0, sizeof(mDDPF));

		mClientRect = { 0 };
		mCurBackBuffer = 1;
		mSurfaceBPP = 0;
	}

	DDApp::~DDApp() {
		memset(&mDDSD, 0, sizeof(mDDSD));
		ReleaseCOM(mlpDDClipper);
		ReleaseCOM(mlpDDSurefaceBackBuffer);
		ReleaseCOM(mlpDDSurefacePrimary);
		ReleaseCOM(mDD7);
		return;
	}

	void DDApp::Update(const Timer& Timer) {
		// TODO: 在此处添加实现代码.
		RECT destRect, srcRect;
		InitializeWithZero(destRect);
		InitializeWithZero(srcRect);

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

	LPDIRECTDRAWCLIPPER DDApp::DDrawAttachClipper()
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
		DXInit_s(
			mDD7->CreateClipper(0, &lpddClipper, NULL),
			"Clipper Attach falied");

		// fill RGNDATA
		// first allocate memory
		region_data = (LPRGNDATA)
			malloc(sizeof(RGNDATAHEADER) +
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
		region_data->rdh.nCount = (DWORD)mClipperRECTQue.size();
		region_data->rdh.nRgnSize = (DWORD)mClipperRECTQue.size() * sizeof(RECT);
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

	bool DDApp::InitDDraw()
	{
		// TODO: 在此处添加实现代码.

		if (FAILED(DirectDrawCreateEx(NULL, (void**)&mDD7, IID_IDirectDraw7, NULL)))
		{
			MessageBoxW(0, L"DD Creat Failed.", 0, MB_OK);
			return false;
		}

		if (mFullScreenState == true)
		{
			if (FAILED(mDD7->SetCooperativeLevel(
				mhMainWnd,
				DDSCL_FULLSCREEN | DDSCL_ALLOWMODEX | DDSCL_EXCLUSIVE | DDSCL_ALLOWREBOOT)))
			{
				MessageBoxA(0, "Set Coop Level Failed.", 0, MB_OK);
				return false;
			}
		}
		else
		{
			DXInit_s(
				mDD7->SetCooperativeLevel(mhMainWnd, DDSCL_NORMAL),
				"Set Coop Level Failed.");
		}

		DXInit_s(
			mDD7->SetDisplayMode(mClientWidth, mClientHeight, mClientBPP, 0, 0),
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

	bool DDApp::CreatSwapChain()
	{
		if (!mFullScreenState)
		{
			memset(&mDDSD, 0, sizeof(mDDSD));
			mDDSD.dwSize = sizeof(mDDSD);
			mDDSD.dwFlags = DDSD_CAPS;
			mDDSD.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

			DXInit_s(
				mDD7->CreateSurface(&mDDSD, &mlpDDSurefacePrimary, NULL),
				"Primary Surface Creat Failed");

			memset(&mDDSD, 0, sizeof(mDDSD));
			mDDSD.dwSize = sizeof(mDDSD);
			mDDSD.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_CKSRCBLT;

			mDDSD.dwHeight = mClientHeight;
			mDDSD.dwWidth = mClientWidth;

			DXInit_s(
				mDD7->CreateSurface(&mDDSD, &mlpDDSurefaceBackBuffer, NULL),
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

		if (FAILED(debug = mDD7->CreateSurface(&mDDSD, &mlpDDSurefacePrimary, NULL)))
		{
			//__POSTERR("Primery Surface Creat Failed");
			DXTrace(__FILEW__, __LINE__, debug, NULL, TRUE);
			return false;
		}

		mDDSD.ddsCaps.dwCaps = DDSCAPS_BACKBUFFER;

		DXInit_s(
			mlpDDSurefacePrimary->GetAttachedSurface(&mDDSD.ddsCaps, &mlpDDSurefaceBackBuffer),
			"Back Buffer Surface Creat Failed"
		);

		return true;
	}

	// PlotPixel -- plot pixel on a Surface
	// if is 8-bit deepth, only write in r.
	void DDApp::PlotPixel(DDSURFACEDESC2& ddsd, int x, int y, int r, int g, int b, int a)
	{
		if (ddsd.lpSurface == nullptr)	return;
		if (y <= 0)						return;
		if (x <= 0)						return;
		if ((DWORD)y > ddsd.dwHeight)	return;
		if ((DWORD)x > ddsd.dwWidth)	return;
		if (r < 0)						return;

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
		// __RGB24BIT mode
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

	int DDApp::DrawImageToDDSurface(Image& ubmp, DDSURFACEDESC2 ddsd, RECT SrcRect, int x, int y)
	{
		using Isatronia::Resource::RGBInfo;
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

	RGBInfo DDApp::GetPixelRGB(int x, int y) const
	{
		RGBInfo col = RGBInfo();
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

	void DDApp::OnResize() {
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

	void DDApp::Initialize() {

		// TODO: 在此处添加实现代码.
		if (!InitMainWindow())
		{
			MessageBoxA(0, "InitWindow Failed.", "", MB_OK);
			throw(new RuntimeException(L"InitWindow Failed."));
			return;
		}

		if (!InitDDraw())
		{
			MessageBoxA(0, "InitDD Failed.", "", MB_OK);
			return;
		}

		OnResize();

		return;

	}

	

	bool DDApp::InitMainWindow()
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
		wc.lpfnWndProc = DDAppMainWndProc;
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

}// end namespace