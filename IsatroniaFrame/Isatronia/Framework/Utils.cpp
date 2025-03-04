//--------------------------------------------------------------------------------------
// File: Utils.cpp
//
// Copyright (c) Ishgrina. All rights reserved.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------

#include "Utils.h"
#include <cstdint>

namespace Isatronia::Framework
{
	// Swap func for all types

	// UvcRect�ࣺ
	UvcRect::UvcRect()
	{
		rect = { 0 };
		msg = 0;
		return;
	}
	UvcRect::UvcRect(RECT& r) :UvcRect()
	{
		rect = r;
		msg = 0;
		return;
	}
	UvcRect::UvcRect(RECT&& r)
	{
		rect = r;
		msg = 0;
		return;
	}

	UvcRect::~UvcRect() {};

	Isatronia::Resource::RGBAInfo getRGBAInfoInImageBuffer(
		const UCHAR* mBuffer,
		const BITMAPINFOHEADER& mBitMapInfoHeader,
		int x,
		int y)
	{
		__int32 width = abs(mBitMapInfoHeader.biWidth); // ������biWidth
		__int32 bytesPerPixel = mBitMapInfoHeader.biBitCount / 8;
		// ���������ÿ���ֽ���
		__int32 paddedWidth = ( width * bytesPerPixel + 3 ) & ~3;
		// ����ƫ����
		__int32 offset = y * paddedWidth + x * bytesPerPixel;

		Isatronia::Resource::RGBAInfo col;
		switch ( mBitMapInfoHeader.biBitCount )
		{
		case 16:
		{
			uint16_t pixel = *reinterpret_cast<const uint16_t*>( mBuffer + offset );
			col.r = ( pixel >> 11 ) & 0x1F; // 5λ��ɫ
			col.g = ( pixel >> 5 ) & 0x3F; // 6λ��ɫ
			col.b = pixel & 0x1F;         // 5λ��ɫ
			break;
		}
		case 24: // BGR˳��
			col.b = mBuffer[offset];
			col.g = mBuffer[offset + 1];
			col.r = mBuffer[offset + 2];
			break;
		case 32: // BGRA˳��
			col.b = mBuffer[offset];
			col.g = mBuffer[offset + 1];
			col.r = mBuffer[offset + 2];
			col.a = mBuffer[offset + 3];
			break;
		default: break;
		}
		return col;
	}
}