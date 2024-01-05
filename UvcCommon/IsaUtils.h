#include <Windows.h>

#define __RGB32BIT(a,r,g,b) ((b) + ((g) << 8) + ((r) << 16) + ((a) << 24))

namespace IsaFrame::IsaUtil {

	// UvcRect类：
	// 存储了一些用于渲染和判定的矩形
	class UvcRect
	{
	public:
		UvcRect() { rect = { 0 }; msg = 0; return; };
		UvcRect(RECT r) :UvcRect() { rect = r; return; };
		~UvcRect() {};

	public:
		RECT rect;
		UINT msg;
	};

	class RGBInfo
	{
	public:
		UCHAR r;
		UCHAR g;
		UCHAR b;

		RGBInfo()
		{
			r = 0;
			g = 0;
			b = 0;
			return;
		}
		explicit RGBInfo(int R, int G, int B)
		{
			r = R; g = G; b = B;
			return;
		}
		virtual inline bool operator==(const RGBInfo& col)
		{
			if (col.r == r && col.g == g && col.b == b) return true;
			else return false;
		}
		virtual inline bool operator!=(const RGBInfo& col)
		{
			if (col.r != r || col.g != g || col.b != b) return true;
			else return false;
		}
	};

	class RGBAInfo : public RGBInfo
	{
	public:
		UCHAR a;

		RGBAInfo() : RGBInfo() {
			this->a = 0;
			return;
		}

		explicit RGBAInfo(int r, int g, int b, int a) : RGBInfo(r, g, b) {
			this->a = a;
			return;
		}

		inline bool operator==(const RGBAInfo& col)
		{
			if (col.r == r && col.g == g && col.b == b && col.a == a) return true;
			else return false;
		}
		inline bool operator!=(const RGBAInfo& col)
		{
			if (col.r != r || col.g != g || col.b != b || col.a != a) return true;
			else return false;
		}
	};
}