#define WIN32_LEAN_AND_MEAN_
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <deque>
#include <vector>
#include <map>

#include "DDApp.h"
#include "Exception.h"
#include "RuntimeException.h"

using std::string;
using std::deque;
using std::vector;
using std::map;
using std::pair;



//#define __POSTERR(str) {MessageBox(0, str, "Error", NULL);}
//#define DXInit_s(res, str) { if (FAILED(res)) {__POSTERR(str);return false; } }
//#define InitDDStruct(dds) {memset(&dds, 0, sizeof(decltype(dds)); dds.dwsize = decltype(dds))}

//#define __GAME_STATE_MENU__		0
//#define __GAME_STATE_RUN__		1
//#define __GAME_STATE_WIN__		2
//#define __GAME_STATE_DIE__		3
//#define __GAME_STATE_END__		4
//#define __GAME_STATE_STGINIT__	5


using namespace Isatronia::Windows;


enum class GameState {
	menu,
	run,
	win,
	die,
	end,
	stginit
};

class TestApp :public DDApp
{
public:

	//TestApp(HINSTANCE hInstance) :App(hInstance) { mFullScreenState = false; };
	explicit TestApp(HINSTANCE hInstance, int Width = 1920, int Height = 1080) :DDApp(hInstance) { mFullScreenState = false; mClientWidth = Width; mClientHeight = Height; };
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual void Initialize();
	virtual void GlobalInitialization();
private:
	virtual void Draw(const Timer& Timer)override;
	virtual void Update(const Timer& Timer)override;
	

public:
	void Pause() { mAppPaused = true; return; };
	void unPause() { mAppPaused = false; return; };
};



int APIENTRY WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hprevInstance,
	_In_ LPSTR cmdLine,
	_In_ int showcmd
){
	using std::ifstream;

	// buffer String
	char sz[100] = { 0 };

	try {
		// 前置数据载入

		// Init App
		TestApp app(hInstance);
		app.Initialize();
		return app.Run();
	}
	catch (Isatronia::Exception::Exception* e)
	{
		e->showErrorDialog();
		return -1;
	}
	catch (...)
	{
		MessageBoxA(nullptr, "Failed", "Failed", MB_OK);
		return 1;
	}
	return -1;
}

void TestApp::Draw(const Timer& Timer)
{
	return;
}

void TestApp::Update(const Timer& Timer)
{
	// TODO: 在此处添加实现代码.

	// To Draw Debug Info
	HDC hdc;
	COLORREF old_fcol, old_bcol;
	int old_tmode;

	memset(&mDDSD, 0, sizeof(mDDSD));
	mDDSD.dwSize = sizeof(mDDSD);
	if (FAILED(mlpDDSurefacePrimary->Lock(NULL, &mDDSD,
		DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT,
		NULL)))
	{
		//MessageBox(mhMainWnd, "Lock Falied", "Error", MB_OK);
		//PostQuitMessage(0);
		return;
	}

	Draw(Timer);

	if (FAILED(mlpDDSurefacePrimary->Unlock(NULL)))
	{
		MessageBoxA(mhMainWnd, "Unlock Falied", "Error", MB_OK);
		PostQuitMessage(0);
		return;
	}

	//if (!ShowDebugInfo)	return;
	if (FAILED(mlpDDSurefacePrimary->GetDC(&hdc)))
	{
		Exception* e = new Exception("DC get ERR");
		e->showErrorDialog();
		delete e;
		return;
	}
	old_fcol = SetTextColor(hdc, RGB(255, 255, 255));
	old_bcol = SetBkColor(hdc, RGB(0, 0, 0));
	old_tmode = SetBkMode(hdc, TRANSPARENT);

	//sprintf_s(debug, "RECT: left:%d right:%d top:%d bottom:%d", Chara.detectRect.left, Chara.detectRect.right, Chara.detectRect.top, Chara.detectRect.bottom);
	//TextOut(hdc, 0, 30, debug, strlen(debug));
	//sprintf_s(debug, "CharaPos X:%d Y:%d  CharaState:%d CenterPos: x:%d y:%d", Chara.GetX(), Chara.GetY(), Chara.GetDieState(), Chara.GetCenterPos().x, Chara.GetCenterPos().y);
	//TextOut(hdc, 0, 45, debug, strlen(debug));
	//sprintf_s(debug, "GoalRect:  left:%d right:%d top:%d bottom:%d", GoalList[mStage].left, GoalList[mStage].right, GoalList[mStage].top, GoalList[mStage].bottom);
	//TextOut(hdc, 0, 60, debug, strlen(debug));
	//sprintf_s(debug, "GameState:%d SubStateSlected:%d Stage:%d", mGameState, mSubStateSlected, mStage);
	//TextOut(hdc, 0, 75, debug, strlen(debug));
	//sprintf_s(debug, "LeftEnimy: %d", EnimyList.size());
	//TextOut(hdc, 0, 90, debug, strlen(debug));

	SetTextColor(hdc, old_fcol);
	SetBkColor(hdc, old_bcol);
	SetBkMode(hdc, old_tmode);
	if (FAILED(mlpDDSurefacePrimary->ReleaseDC(hdc)))
	{
		Exception* e = new Exception("DC release ERR");
		e->showErrorDialog();
		delete e;
		return;
	}

	return;
}

void TestApp::GlobalInitialization() {
	return;
}

//void TestApp::StageInit()
//{
//	using namespace std;
//	RECT r;
//	char FileName[50];
//	int index = 0, x = 0, y = 0;
//	string sz;
//
//	sprintf_s(FileName, "rcs\\stage%d.uvcsource", mStage);
//	ifstream fin(FileName);
//	if (!fin.is_open()) return;
//
//	while (fin >> index)
//	{
//		fin >> x >> y;
//		EnimyList.push_back(CEnimy(EnimyDict[index], x, y));
//	}
//
//	fin.close();
//}

//void TestApp::KeyDownEvent(WPARAM wParam)
//{
//	return;
	//switch (wParam)
	//{
	//case VK_UP:
	//case 'W':
	//case 'X':
	//	switch (mGameState)
	//	{
	//	case __GAME_STATE_MENU__:
	//		mSubStateSlected -= 1;
	//		if (mSubStateSlected < 0)
	//			mSubStateSlected = 0;
	//		break;
	//	case __GAME_STATE_RUN__:
	//		Chara.Jump();
	//		Chara.Fall();
	//		break;
	//	}
	//
	//	break;
	//case VK_LEFT:
	//case 'A':
	//	Chara.RunLeft();
	//	break;
	//case VK_DOWN:
	//case 'S':
	//	switch (mGameState)
	//	{
	//	case __GAME_STATE_MENU__:
	//		mSubStateSlected += 1;
	//		if (mSubStateSlected > 1)
	//			mSubStateSlected = 1;
	//		break;
	//	case __GAME_STATE_RUN__:
	//		break;
	//	default:break;
	//	}
	//
	//	break;
	//case VK_RIGHT:
	//case 'D':
	//	Chara.RunRight();
	//	break;
	//
	//case 'Z':
	//case VK_RETURN:
	//	switch (mGameState)
	//	{
	//	case __GAME_STATE_MENU__:
	//		switch (mSubStateSlected)
	//		{
	//		case __MENU_NEWGAME__:
	//			mGameState = __GAME_STATE_STGINIT__;
	//			mSubStateSlected = 0;
	//			Chara.Fall();
	//			break;
	//		case __MENU_EXIT__:
	//			PostQuitMessage(0);
	//			break;
	//		default:break;
	//		}
	//		break;
	//
	//	case __GAME_STATE_RUN__:
	//	{
	//		Chara.Fireing();
	//	}
	//	break;
	//
	//	default:
	//		break;
	//	}
	//
	//	break;// end return.
	//case VK_ESCAPE:
	//	PostQuitMessage(0);
	//	break;// end ESC
	//case VK_F2:
	//	mAppPaused = !mAppPaused;
	//	break;// end f2
	//
	//case VK_F3:
	//	ShowDebugInfo = !ShowDebugInfo;
	//	break;
	//default:
	//	break;
	//}
	//return;
//}// End KeyDown Event

//void TestApp::KeyUpEvent(WPARAM wParam)
//{
//	switch (wParam)
//	{
//	case VK_UP:
//	case 'W':
//		break;
//	case VK_DOWN:
//	case 'S':
//		break;
//	case VK_LEFT:
//	case VK_RIGHT:
//	case 'A':
//	case 'D':
//		//Chara.StopRun();
//		break;
//
//	default:
//		break;
//	}
//	return;
//}

//void TestApp::SetCameraPos(LONG x, LONG y)
//{
//	Camerax = x;
//	Cameray = y;
//	return;
//}

void TestApp::Initialize()
{
	// TODO: 在此处添加实现代码.
	if (!InitMainWindow())
	{
		throw new Isatronia::Exception::RuntimeException(
			"Initralize main window Failed.");
	}

	if (!InitDDraw())
	{
		throw new Isatronia::Exception::RuntimeException(
			"Initralize DirectDraw Failed.");
	}
	GlobalInitialization();
	OnResize();
	return;
}

LRESULT TestApp::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此处添加实现代码.
	switch (msg)
	{
	case WM_ACTIVATE:
		if (LOWORD(wParam) == WA_INACTIVE)
		{
			// when the Window is inactive, pause the game.
			mAppPaused = true;
			mTimer.Stop();
		}
		else
		{
			mAppPaused = false;
			mTimer.Start();
		}
		return 0;
		break;
	case WM_COMMAND:
	{
	}
	break;
	case WM_KEYDOWN:
		//KeyDownEvent(wParam);
		break;
	case WM_KEYUP:
	{
		//KeyUpEvent(wParam);
		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		// TODO: 在此处添加使用 hdc 的任何绘图代码...
		EndPaint(hwnd, &ps);
	}
	break;
	case WM_MOVE:
	{
		OnResize();
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}






/*

int flag = 0;// 用于部分判定
	int judx = 0, judy = 0;
	RGBInfo col;// for debug
	int step = 0;

	switch (mGameState)
	{
	case __GAME_STATE_MENU__:
	{
		DrawImageToDDSurface(MenuBkg, mDDSD, MenuBkg.GetRect(), 0, 0);
		for (int i = 0; i < __MAX_MENU__; i++)
		{
			DrawImageToDDSurface(Menu[i][(i == mSubStateSlected)], mDDSD, Menu[i][(i == mSubStateSlected)].GetRect(), 1500, (i + 25) * 25);
		}
	}// end menu
	break;
	case __GAME_STATE_RUN__:
	{
		// 摄像机先做一下移动
		if (Chara.GetX() > 960 && Chara.GetX() < (Map.mBitMapInfoHeader.biWidth - 960))
		{
			Camerax = Chara.GetX() - 960;
		}

		if (Chara.GetX() < 960)
		{
			Camerax = 0;
		}

		// 现在准备写一下掉落的判定
		// 思路是对玩家角色下方逐像素进行rgb比对，如果和背景颜色一样说明没有落脚点
		// 就往下掉(0v0)

		// Anim slect
		// 这个是画背景的
		DrawImageToDDSurface(TestApp::bkg, mDDSD, TestApp::bkg.GetRect(), 0, 0);

		// 这里画地图
		DrawImageToDDSurface(Map, mDDSD, Map.GetCameraRECT(Camerax, Cameray, mClientWidth, mClientHeight), 0, 0);

		// 开始掉落比对
		// 使用判定矩形来看看到头没
		// 因为是逐帧操作的所以每次只需要比对Vy行像素
		// 如果y轴方向速度小于零说明正在往上飞，不用管
		if (Chara.Getvy() >= 0)
		{
			// 如果角色正在掉落
			if (Chara.IsFalling())
			{
				for (int j = 0; j < Chara.Getvy(); j++)
				{
					for (int i = Chara.detectRect.left; i < Chara.detectRect.right; i++)
					{
						// 计算要检测的值时一定记住要算相对坐标
						// 要检测的x值范围为 碰撞箱左 -- 碰撞箱右
						judx = Chara.GetX() - Camerax + i;
						// 要检测的y值范围为 碰撞箱下 -- 碰撞箱下+ y轴方向速度
						judy = Chara.GetY() - Cameray + Chara.detectRect.bottom + j;

						// 超出边界没有检测必要
						if (judx > mClientWidth || judx < 0) break;
						if (judy > mClientHeight || judy < 0) break;

						//逐像素比对,有墙就站住
						// 因为都是在主表面上进行检测所以并不用减摄像机算相对坐标
						if (GetPixelRGB(judx, judy) != TestApp::bkg.GetPixelRGB(judx, judy))
						{
							Chara.ForceSetVy(j);
							Chara.StopFall();
						}
					}
					// 这里改过说明之前的循环中已经发现异常，可以退出循环
					if (!Chara.IsFalling()) break;
				}
			}
			// 玩家没在掉落过程中的话每一帧检测一下是否会掉落
			else
			{
				flag = 0;
				for (int i = Chara.detectRect.left; i < Chara.detectRect.right; i++)
				{
					// 碰撞检测起止：
					// x轴： 碰撞箱左右
					judx = Chara.GetX() - Camerax + i;
					judy = Chara.GetY() - Cameray + Chara.detectRect.bottom + 1;
					if (GetPixelRGB(judx, judy) == TestApp::bkg.GetPixelRGB(judx, judy))
					{
						// 此处flag变量用于保存每行中与背景色一致的像素个数
						flag++;
					}
				}
				// 发现人物已经完全离开平台
				if (flag >= (Chara.detectRect.right - Chara.detectRect.left))
				{
					Chara.Fall();
				}
			}
		}
		// 这里进行左右碰撞检测，主要用于人物撞停不会卡进墙里
		if (Chara.Getvx() != 0 && Chara.Getvy() >= 20)
		{
			flag = 0;
			// 改变一下系数，简化后续判定
			if (Chara.Getvx() > 0)	flag = 1;
			if (Chara.Getvx() < 0)	flag = -1;

			// 算出相对坐标
			// 其中x坐标为 玩家中心坐标
			judx = Chara.GetX() - Camerax	// 基准坐标（在摄像机视角下的中心坐标
				+ ((Chara.detectRect.left + Chara.detectRect.right) >> 1)	// 加上这个值后得到角色的x中心
				+ (flag * ((Chara.detectRect.right - Chara.detectRect.left) >> 1)); // 算出碰撞箱相对摄像机的判定起始x
			judy = Chara.GetY() - Cameray;
			for (int i = 0; i < Chara.Getvx(); i++)
			{
				for (int j = judy + Chara.detectRect.top; j < judy + Chara.detectRect.bottom; j++)
				{
					if (GetPixelRGB(judx + i * flag, j) != TestApp::bkg.GetPixelRGB(judx + i * flag, j))
					{
						Chara.ForceSetVx(i * flag);
						break;
					}
				}
				// 不是标准值说明被改过了，前面检测到墙壁了
				if (abs(Chara.Getvx()) != Chara.GetStdVx())	break;
			}
		}
		if (mStage >= GoalList.size())
		{
			Chara.SetDieState(__DIE_STATE_WIN__);
		}
		else
		{
			if (IsIn(Chara.GetCenterPos(), GoalList[mStage]))
			{
				Chara.SetDieState(__DIE_STATE_WIN__);
			}
		}

		if (Chara.GetDieState() == __DIE_STATE_WIN__)
		{
			mGameState = __GAME_STATE_WIN__;
		}
		if (Chara.GetDieState() == __DIE_STATE_DIE__)
		{
			mGameState = __GAME_STATE_DIE__;
		}

		Chara.Move();

		// 正在开火
		if (Chara.IsFireing())
		{
			step = 1;
			if (!Chara.IsFaceRight())step = -1;
			for (int i = Chara.GetX() + (Chara.IsFaceRight() ? Chara.detectRect.right : Chara.detectRect.left) - Camerax; i > 0 && i < mClientWidth; i = i + step)
			{
				PlotPixel(mDDSD, i, Chara.GetY() + 36, 255, 231, 46);
			}
			Chara.Fired();
			for (auto x : EnimyList)
			{
				if (x.Box.top < Chara.GetY() + 36 && x.Box.bottom > Chara.GetY() + 36)
				{
					x.Damage(10);
				}
			}
			for (int i = 0; i < EnimyList.size();)
			{
				if (EnimyList[i].mDeath)
				{
					EnimyList.erase(EnimyList.begin() + i);
				}
				else
				{
					i = i + 1;
				}
			}
		}

		// 这个是画玩家的
		DrawImageToDDSurface(Chara.GetBMP(), mDDSD, Chara.GetBMP().GetRect(), Chara.GetX() - Camerax, Chara.GetY() - Cameray);

		for (auto x : EnimyList)
		{
			DrawImageToDDSurface(x.GetCurImage(), mDDSD, x.GetCurImage().GetRect(), x.x - Camerax, x.y - Cameray);
		}
	}
	break;// end RUN
	case __GAME_STATE_WIN__:
	{
		Chara.ForceSetVx(20);

		Chara.ForceSetPos(Chara.GetX() + 20, Chara.GetY());
		Chara.Count();
		// 这个是画背景的
		DrawImageToDDSurface(TestApp::bkg, mDDSD, TestApp::bkg.GetRect(), 0, 0);

		// 这里画地图
		DrawImageToDDSurface(Map, mDDSD, Map.GetCameraRECT(Camerax, Cameray, mClientWidth, mClientHeight), 0, 0);
		DrawImageToDDSurface(Chara.GetBMP(), mDDSD, Chara.GetBMP().GetRect(), Chara.GetX() - Camerax, Chara.GetY() - Cameray);
		if (Chara.GetX() >= Map.mBitMapInfoHeader.biWidth)
			mGameState = __GAME_STATE_STGINIT__;
	}
	break;
	case __GAME_STATE_DIE__:
	{
	}
	break;
	case __GAME_STATE_STGINIT__:
	{
		Chara.SetDieState(__DIE_STATE_ALIVE__);
		Chara.ForceSetPos(10, 10);
		mGameState = __GAME_STATE_RUN__;
		mStage = mStage + 1;
		StageInit();

		if (mStage >= GoalList.size())
		{
			mStage = 0;
			mGameState = __GAME_STATE_END__;
			break;
		}
	}
	break;
	case __GAME_STATE_END__:
	{
		mGameState = __GAME_STATE_MENU__;
	}
	break;
	default:break;
	}// end Switch
	return;


// 函数的前置声明
inline bool IsIn(POINT p, RECT rect);



// Init Class's static member.
int Role::mClientWidth = 800;
int Role::mClientHeight = 600;
Image TestApp::bkg;

// Stage Map
Image Map;
// Menu Bkg.
Image MenuBkg;
// new Charas.(BOBs)
Role Chara(10, 10);
// Chara's AnimList
int Animlist[6] = { 1, 2, 3, 4, 3, 2 };
// MenuItem.
std::string menuItem[2] = { "newGame", "exit" };

// Enimys
map<int, CEnimy> EnimyDict;
vector<CEnimy> EnimyList;
vector<RECT> GoalList;

char debug[100] = {};


				flag = 0;
				// 如果卡墙里了
				for (int i = Chara.detectRect.left; i < Chara.detectRect.right; i++)
				{
					judx = Chara.GetX() + i;
					judy = Chara.GetY() + Chara.detectRect.bottom - 1;
					// 由于这个时候还没有画人物所以可以这么检测：
					if (GetPixelRGB(judx, judy) != Role::bkg.GetPixelRGB(judx, judy))
					{
						flag += 1;// 设置一个判定的特殊值,说明卡墙里了
						break;
					}
				}
				// 如果没卡墙里
				// 进行落地检测
				if (flag <= 3)
switch (mGameState)
	{
	case __GAME_STATE_MENU__:
	{
	}
	break;
	case __GAME_STATE_RUN__:
	{
		Draw(Timer);
		RECT src, dest;
		src.left = Role::mCamerax;
		src.right = Role::mCamerax + Role::mClientx;

		src.top = Role::mCameray;
		src.bottom = Role::mCameray + Role::mClienty;

		dest.left = 0;
		dest.top = 0;
		dest.right = mClientWidth;
		dest.left = mClientHeight;

		if (FAILED(mlpDDSurefacePrimary->Blt(&dest, Role::canvas, &src, DDBLT_WAIT, NULL)))
		{
			__POSTERR("Blt Failed");
		}
	}
	break;
	default:break;
	}
DDSURFACEDESC2 ddsd;
		memset(&ddsd, 0, sizeof(ddsd));
		ddsd.dwSize = sizeof(ddsd);
		ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;
		ddsd.dwHeight = Height; ddsd.dwWidth = Width;

		if (FAILED(app.mlpDD7->CreateSurface(&ddsd, &Role::canvas, NULL)))
		{
			throw 3;
		}
		Role::GetCanvasPF();

abandon.

void static DrawBkgToCanvas();
	void static GetCanvasPF();

void Role::DrawBkgToCanvas()
{
	RECT SrcRect = { 0,0,mClientx, mClienty };
	UCHAR r = 0, g = 0, b = 0;

	for (int j = 0; j < mClienty; j++)
	{
		for (int i = 0; i < mClientx; i++)
		{
			Role::bkg.GetPixelRGB(SrcRect.left + i, SrcRect.top + j, r, g, b);
			//PlotPixel(ddsd, mClientRect.left + x, mClientRect.top + y, r, g, b);
			PlotPixel(Role::canvas, i, j, r, g, b);
		}
	}

	return;
}

void Role::GetCanvasPF()
{
	//memset(&CanvasPF, 0, sizeof(DDPIXELFORMAT));
	//CanvasPF.dwSize = sizeof(DDPIXELFORMAT);
	////CanvasPF.dwSize = sizeof(decltype(CanvasPF));

	//canvas->GetPixelFormat(&CanvasPF);
	return;
}

	void DrawImageToCanvas();
void Role::DrawImageToCanvas()
{
	Image* tag = nullptr;
	if (mfaceRight)
	{
		if (mAnimIndex)
			tag = &rAnim[Animlist[mAnimIndex % 6]];
		else
			tag = &rAnim[0];
	}
	else
	{
		if (mAnimIndex)
			tag = &lAnim[Animlist[mAnimIndex % 6]];
		else
			tag = &lAnim[0];
	}

	RECT SrcRect = tag->GetRect();
	UCHAR r = 0, g = 0, b = 0;

	for (int j = 0; j < SrcRect.bottom - SrcRect.top; j++)
	{
		for (int i = 0; i < SrcRect.right - SrcRect.left; i++)
		{
			tag->GetPixelRGB(SrcRect.left + i, SrcRect.top + j, r, g, b);
			//PlotPixel(ddsd, mClientRect.left + x, mClientRect.top + y, r, g, b);
			PlotPixel(canvas, mCharax + i, mCharay + j, r, g, b);
		}
	}

	return;
}

if (Chara.mCharay + 20 < mClientRect.bottom)
				Chara.mCharavy = 20;

if (Chara.faceRight)
		{
			if (g_AnimIndex)
				DrawImageToDDSurface(Chara.rAnim[Animlist[g_AnimIndex % 6]], mDDSD, Chara.rAnim[Animlist[g_AnimIndex % 6]].GetRect(), Chara.mCharax, Chara.mCharay);
			else
				DrawImageToDDSurface(Chara.rAnim[0], mDDSD, Chara.rAnim[0].GetRect(), Chara.mCharax, Chara.mCharay);
		}
		else
		{
			if (g_AnimIndex)
				DrawImageToDDSurface(Chara.lAnim[Animlist[g_AnimIndex % 6]], mDDSD, Chara.lAnim[Animlist[g_AnimIndex % 6]].GetRect(), Chara.mCharax, Chara.mCharay);
			else
				DrawImageToDDSurface(Chara.lAnim[0], mDDSD, Chara.lAnim[0].GetRect(), Chara.mCharax, Chara.mCharay);
		}

int lpitch32 = (int)(mDDSD.lPitch >> 2);
	UINT* video_buffer = (UINT*)mDDSD.lpSurface;

	auto rd = [](int max = 255) {return rand() % max; };

	//DrawImageToDDSurface(uBmp, mDDSD, uBmp.GetRect(), rd() + 100, rd() + 100);
	//DrawImageToDDSurface(bkg, mDDSD, bkg.GetRect(), 0, 0);
	//DrawImageToDDSurface(uBmp, mDDSD, uBmp.GetRect(), mCharax, mCharay);
	DDSURFACEDESC2 ddsd;
	memset(&ddsd, 0, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);

	//char sz[100] = { 0 };
	//sprintf_s(sz, "Chara point:x = %d, y = %d", mCharax, mCharay);
	//__POSTERR(sz);
	//__POSTERR("Next Frame?");

	for (int i = 0; i < 1000; i++)
	{
		video_buffer[rd(mClientWidth) + rd(mClientHeight) * lpitch32] = __RGB32BIT(rd(), rd(), rd(), rd());
	}
	// edge detect
		if (Chara.mCharax + uBmp.mBitMapInfoHeader.biWidth > mClientWidth)
			Chara.mCharax = mClientWidth - uBmp.mBitMapInfoHeader.biWidth;
		if (Chara.mCharax < 0)
			Chara.mCharax = 0;
		if (Chara.mCharay + uBmp.mBitMapInfoHeader.biHeight > mClientHeight)
			Chara.mCharay = mClientHeight - uBmp.mBitMapInfoHeader.biHeight;
		if (Chara.mCharay < 0)
			Chara.mCharay = 0;

*/