#include <Windows.h>


class UvcRect;

// UvcRect类：
// 存储了一些用于渲染和判定的矩形
class UvcRect
{
public:
	UvcRect() { rect = { 0 }; return; };
	UvcRect(RECT r) :UvcRect() { rect = r; return; };
	~UvcRect() {};

public:
	RECT rect;
	UINT msg;
};