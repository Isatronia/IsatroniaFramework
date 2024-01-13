//--------------------------------------------------------------------------------------
// File: Sprite.cpp
//
// Copyright (c) Ishgrina. All rights reserved.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------
#include "Sprite.h"
#include "../Framework/Timer.h"
#include "../Resource/Image.h"
#include "../Resource/BitMap.h"
#include "../Resource/BitMap.h"
namespace Isatronia::Sprite {

	using namespace Isatronia::Framework;
	using namespace Isatronia::Resource;

	Sprite::Sprite()
	{
		//memset(&mHitBox, 0, sizeof(RECT));

		//mCharax = 0;
		//mCharay = 0;
		//mCharavx = 0;
		//mCharavy = 0;
		//mStdvx = 20;

		//mAnimIndex = 0;
		//mAnimIndexAddCount = 0;
		//mJumpTimes = 2;

		//mdie = 0;
		//mfaceRight = true;
		//mFall = false;

		//LastFireTick = 0;
		//mFire = false;

		//mAtk = 10;
		//mHp = 100;
		return;
	}

	Sprite::Sprite(int CharaX, int CharaY) :Sprite()
	{
		//mCharax = CharaX;
		//mCharay = CharaY;
		//mCharavx = 0;
		//mCharavy = 0;

		//mfaceRight = true;
		//mFall = false;
		return;
	}

	Image* Sprite::getCurrentImage()
	{
		// TODO: 在此处插入 return 语句
		/*if (mfaceRight)
		{
			if (mAnimIndex)
				return rAnim[Animlist[mAnimIndex % 6]];
			else
				return rAnim[0];
		}
		else
		{
			if (mAnimIndex)
				return lAnim[Animlist[mAnimIndex % 6]];
			else
				return lAnim[0];
		}
		return UvcImage();*/
		return new Bitmap();
	}

	inline void Sprite::Jump()
	{
		if (mJumpTimes <= 0) return;
		mJumpTimes -= 1;
		mCharavy = -160;
		Fall();
		return;
	}

	void Sprite::StopRun()
	{
		if (mCharavx)
			mCharavx = 0;
		return;
	}

	void Sprite::Move()
	{
		Count();
		if (mFall)
		{
			if (mCharavy < 20)
				mCharavy = mCharavy + __G__;
		}

		mCharax = mCharax + mCharavx;
		mCharay = mCharay + mCharavy;

		if (abs(mCharavx) != 20)
		{
			mCharavx = 0;
		}

		// edge detect
		if (mCharax + uBmp.mBitMapInfoHeader.biWidth > mClientWidth)
			mCharax = mClientWidth - uBmp.mBitMapInfoHeader.biWidth;
		if (mCharax < 0)
			mCharax = 0;

		if (mCharay + uBmp.mBitMapInfoHeader.biHeight > mClientHeight)
		{
			mCharavy = 0;
			mCharay = mClientHeight - uBmp.mBitMapInfoHeader.biHeight;
			StopFall();
		}
		if (mCharay < 0)
		{
			mCharay = 0;
			mCharavy = 0;
		}

		// 不悬空不会产生y轴速度
		if (!mFall)
		{
			mCharavy = 0;
		}

		return;
	}

	void Sprite::Count()
	{
		if (mCharavx)
		{
			mAnimIndex++;
		}

		if (!isMoving())
		{
			mAnimIndex = 0;
			mAnimIndexAddCount = 0;
		}
		return;
	}

	inline void Sprite::Damage(ULONGLONG Dmg)
	{
		if (Dmg >= mHp)
		{
			mdie = spriteState::die;
			return;
		}
		else
		{
			mHp = mHp - Dmg;
		}
	}

	inline POINT Sprite::GetCenterPos()
	{
		POINT pos;
		// x坐标中心点计算为角色x坐标加碰撞箱中点，y类似
		pos.x = ((mHitBox.left + mHitBox.right) >> 1) + mCharax;
		pos.y = ((mHitBox.top + mHitBox.bottom) >> 1) + mCharay;
		return pos;
	}

	void Sprite::PlotPixel(DDSURFACEDESC2& ddsd, int x, int y, int r, int g, int b, int a)
	{
		if (ddsd.lpSurface == nullptr)	return;
		if (y <= 0)				return;
		if (x <= 0)				return;
		if (y > ddsd.dwHeight)	return;
		if (x > ddsd.dwWidth)	return;
		if (r < 0)				return;

		if (r == 0 && g == 255 && b == 0) return;
		UINT	pixelFor32Bit = 0;
		UINT* bufferFor32bit = (UINT*)ddsd.lpSurface;

		switch (uBmp.mBitCnt)
		{
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
		bufferFor32bit = nullptr;
		return;
	}

	void Sprite::PlotPixel(UvcImage& UImg, int x, int y, int r, int g, int b, int a)
	{
		UINT	pixelFor32Bit = 0;
		UINT*	bufferFor32bit = (UINT*)UImg.getImage();

		switch (UImg.getImageSize())
		{
			// __RGB 24BIT mode
		case 24:
		{
			pixelFor32Bit = __RGB32BIT(0, r, g, b);
			bufferFor32bit[x + (y * (int)(UImg.getImageRect().right))] = pixelFor32Bit;
		}
		break;
		// __RGB32BIT mode
		case 32:
		{
			pixelFor32Bit = __RGB32BIT(a, r, g, b);
			bufferFor32bit[x + (y * (int)(UImg.getImageRect().right))] = pixelFor32Bit;
		}
		break;
		default:
			break;
		}
		bufferFor32bit = nullptr;
		return;
	}

	//void Sprite::SetClientSize(int Width, int Height)
	//{
	//	mClientWidth = Width;
	//	mClientHeight = Height;
	//	return;
	//}

	// ----------------------------------------------------
	// Getters and Setters.
	// ----------------------------------------------------

	int Sprite::getX() {
		return mCharax;
	}

	void Sprite::setX(LONG x) {
		this->mCharax = x;
		return;
	}

	void Sprite::setY(LONG y) {
		this->mCharay = y;
		return;
	}

	int Sprite::getY() {
		return mCharay;
	}

	POINT Sprite::getPoint() {
		return POINT{ getX(), getY() };
	}

	void Sprite::setHitBox(RECT hitBox)
	{
		this->mHitBox = hitBox;
		return;
		/*try {

		}catch(...){
		}
		if (uBmp.mBitMapInfoHeader.biHeight <= Height)	Height = uBmp.mBitMapInfoHeader.biHeight;
		if (uBmp.mBitMapInfoHeader.biWidth <= Width)	Width = uBmp.mBitMapInfoHeader.biWidth;
		if (Width == 65535 && Height == 65535)
		{
			detectRect = uBmp.getRect();
			return;
		}
		detectRect.left = (uBmp.mBitMapInfoHeader.biWidth - Width) / 2;
		detectRect.right = (uBmp.mBitMapInfoHeader.biWidth + Width) / 2;

		detectRect.top = (uBmp.mBitMapInfoHeader.biHeight - Height) / 2;
		detectRect.bottom = (uBmp.mBitMapInfoHeader.biHeight + Height) / 2;
		return;*/
	}
};