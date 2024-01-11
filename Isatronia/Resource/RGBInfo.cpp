#include "RGBInfo.h"

namespace Isatronia::Resource {
	//--------------------------------------------------
	// RGBInfo
	//--------------------------------------------------
	RGBInfo::RGBInfo(UCHAR R, UCHAR G, UCHAR B) : r(R), g(G), b(B) {
		// equal to 
		r = R;
		g = G;
		return;
	}

	RGBInfo::RGBInfo(const RGBInfo& RGB)noexcept : RGBInfo(RGB.r, RGB.g, RGB.b) {
		return;
	}

	RGBInfo::RGBInfo(const RGBInfo&& RGB) noexcept {
		r = RGB.r;
		g = RGB.g;
		b = RGB.b;
		return;
	}

	RGBInfo::RGBInfo() : RGBInfo(0, 0, 0) {

	}

	bool RGBInfo::operator==(const RGBInfo& RGB) {
		if (RGB.r == r && RGB.g == g && RGB.b == b) {
			return true;
		}
		return false;
	}

	void RGBInfo::operator=(const RGBInfo& info) {
		r = info.r;
		g = info.g;
		b = info.b;
		return;
	}

	void RGBInfo::operator=(const RGBInfo&& info) noexcept {
		r = info.r;
		g = info.g;
		b = info.b;
		return;
	}

	//--------------------------------------------------
	// RGBAInfo
	//--------------------------------------------------
	RGBAInfo::RGBAInfo(UCHAR R, UCHAR G, UCHAR B, UCHAR A) : RGBInfo(R, G, B), a(A) {
		return;
	}

	RGBAInfo::RGBAInfo(const RGBAInfo& RGBA) :RGBAInfo(RGBA.r, RGBA.g, RGBA.b, RGBA.a) {
		return;
	}

	RGBAInfo::RGBAInfo(const RGBAInfo&& RGBA) noexcept {
		r = RGBA.r;
		g = RGBA.g;
		b = RGBA.b;
		a = RGBA.a;
		return;
	}

	RGBAInfo::RGBAInfo() : RGBAInfo(0, 0, 0, 0) {
		return;
	}

	bool RGBAInfo::operator==(const RGBAInfo& RGBA) {
		if (r == RGBA.r && g == RGBA.g && b == RGBA.b && a == RGBA.a) {
			return true;
		}
		return false;
	}

	bool RGBAInfo::operator==(const RGBInfo& RGB) {
		if (r == RGB.r && g == RGB.g && b == RGB.b && a == 0xff) {
			return true;
		}
		return false;
	}

	void RGBAInfo::operator=(const RGBAInfo& RGBA) {
		r = RGBA.r;
		g = RGBA.g;
		b = RGBA.b;
		a = RGBA.a;
		return;
	};

	void RGBAInfo::operator=(const RGBAInfo&& RGBA) noexcept {
		r = RGBA.r;
		g = RGBA.g;
		b = RGBA.b;
		a = RGBA.a;
		return;
	}

}