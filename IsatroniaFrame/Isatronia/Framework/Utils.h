//--------------------------------------------------------------------------------------
// File: Utils.h
//
// Copyright (c) Ishgrina. All rights reserved.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------
#include <Windows.h>
#include "../Resource/RGBInfo.h"

#define __RGB32BIT(a,r,g,b) ((b) + ((g) << 8) + ((r) << 16) + ((a) << 24))

namespace Isatronia::Framework
{
	// Swap func for all types
	template<typename T>
	void Swap(T& a, T& b) { T c; c = a; a = b; b = c; };

	// UvcRect类：
	// 存储了一些用于渲染和判定的矩形
	class UvcRect
	{
	public:
		UvcRect();
		UvcRect(RECT& r);
		UvcRect(RECT&& r);

		~UvcRect();

	public:
		RECT rect;
		UINT msg;
	};

	Isatronia::Resource::RGBAInfo getRGBAInfoInImageBuffer(
		const UCHAR* mBuffer,
		const BITMAPINFOHEADER& mBitMapInfoHeader,
		int x,
		int y);
}