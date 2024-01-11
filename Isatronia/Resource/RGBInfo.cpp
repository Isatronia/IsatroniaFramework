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

	RGBInfo::RGBInfo(const RGBInfo& info)noexcept : RGBInfo(info.r, info.g, info.b) {
		return;
	}

	RGBInfo::RGBInfo(const RGBInfo&& info) noexcept {
		return;
	}



}