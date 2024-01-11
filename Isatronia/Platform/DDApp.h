#pragma once

#include "App.h"

#include <ddraw.h>


#include "../Exceptions/Exception.h"
#include "../Resource/Image.h"
#include "../Resource/RGBInfo.h"


#pragma comment(lib,"ddraw.lib")
#pragma comment(lib, "dxguid.lib")

namespace Isatronia::Windows {
	using namespace Isatronia::Exception;
	using Isatronia::Resource::Image;
	using Isatronia::Resource::RGBInfo;

	class DDApp : public App
	{
	protected:
		
		bool mFullScreenState;
		int mCurBackBuffer;
		static const int SwapChainBufferCount = 2;

		// Pointer to Direct Draw 7
		LPDIRECTDRAW7 mDD7;
		// Pointer to DD Surface, primary and backbuffer
		LPDIRECTDRAWSURFACE7	mlpDDSurefacePrimary;
		LPDIRECTDRAWSURFACE7	mlpDDSurefaceBackBuffer;
		// Pointer to clipper
		LPDIRECTDRAWCLIPPER		mlpDDClipper;
		// Surface Desc
		DDSURFACEDESC2	mDDSD;
		// Pixel format
		DDPIXELFORMAT	mDDPF;

		// always save depth of Surface to make sure u r using the right fn. to paint.
		int mSurfaceBPP;

		std::queue<RECT> mClipperRECTQue;
	protected:
		DDApp(HINSTANCE hInstance);
		DDApp(const DDApp& res) = delete;
		DDApp& operator=(const DDApp& res) = delete;
		virtual ~DDApp();

		bool InitDDraw();

		virtual void Update(const Timer& Timer);
		// Attach a Clipper to the BackBufferSurface, using mClipperRECTQue
		virtual LPDIRECTDRAWCLIPPER DDrawAttachClipper();

		void PlotPixel(DDSURFACEDESC2& ddsd, int x, int y, int r, int g = -1, int b = -1, int a = 0);

		// WARNING - Must Run in Draw func!!!!
		int DrawImageToDDSurface(Image& ubmp, DDSURFACEDESC2 ddsd, RECT SrcRect, int x, int y);
		RGBInfo GetPixelRGB(int x, int y) const;
		bool CreatSwapChain();

		DDSURFACEDESC2 GetDDSD() { return mDDSD; };
		
		//override:
		virtual void OnResize()override;
		virtual void Initialize()override;
		virtual bool InitMainWindow()override;
	};
}