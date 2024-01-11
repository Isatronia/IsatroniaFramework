#include <Windows.h>

#define __RGB32BIT(a,r,g,b) ((b) + ((g) << 8) + ((r) << 16) + ((a) << 24))

namespace Isatronia::Framework {

	// Swap func for all types
	template<typename T>
	void Swap(T& a, T& b) { T c; c = a; a = b; b = c; };


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
}