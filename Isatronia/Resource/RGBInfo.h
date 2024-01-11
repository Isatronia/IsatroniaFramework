#pragma once

#include <Windows.h>

namespace Isatronia::Resource {
	class RGBInfo {
	public:
		UCHAR r;
		UCHAR g;
		UCHAR b;

	public:
		explicit RGBInfo(UCHAR R, UCHAR G, UCHAR B);
		RGBInfo(const RGBInfo& info) noexcept : RGBInfo(info.r, info.g, info.b) {};
		RGBInfo(const RGBInfo&& info) noexcept : RGBInfo(info.r, info.g, info.b) {};
		RGBInfo() : RGBInfo(0, 0, 0) {};

		bool operator==(RGBInfo other) {
			if (other.r == r && other.g == g && other.b == b) {
				return true;
			}
			return false;
		}

		void operator=(RGBInfo& info) {
			r = info.r;
			g = info.g;
			b = info.b;
			return;
		}

		void operator=(RGBInfo&& info) noexcept {
			r = info.r;
			g = info.g;
			b = info.b;
			return;
		}
	};

	class RGBAInfo : public RGBInfo
	{
	public:
		UCHAR a;
	public:
		explicit RGBAInfo(UCHAR R, UCHAR G, UCHAR B, UCHAR A) : RGBInfo(R, G, B), a(A) {};
		RGBAInfo(const RGBAInfo& info) :RGBAInfo(info.r, info.g, info.b, info.a) {};
		RGBAInfo(const RGBAInfo&& info) noexcept :RGBAInfo(info.r, info.g, info.b, info.a) {};
		RGBAInfo() :RGBAInfo(0, 0, 0, 0) {};

		void operator=(RGBAInfo& info) {
			r = info.r;
			g = info.g;
			b = info.b;
			a = info.a;
			return;
		}
		void operator=(RGBAInfo&& info) noexcept {
			r = info.r;
			g = info.g;
			b = info.b;
			a = info.a;
			return;
		}
	};
}