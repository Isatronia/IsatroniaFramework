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
#include "BitMap.h"

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

enum class GameState
{
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// APP ENTRY /////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int APIENTRY WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hprevInstance,
	_In_ LPSTR cmdLine,
	_In_ int showcmd
)
{
	using std::ifstream;

	// buffer String
	char sz[100] = { 0 };

	try
	{
		// ǰ����������

		// Init App
		TestApp app(hInstance);
		app.Initialize();
		return app.Run();
	}
	catch ( Isatronia::Exception::Exception* e )
	{
		e->showErrorDialog();
		return -1;
	}
	catch ( ... )
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
	// TODO: �ڴ˴����ʵ�ִ���.

	// To Draw Debug Info
	HDC hdc;
	COLORREF old_fcol, old_bcol;
	int old_tmode;

	memset(&mDDSD, 0, sizeof(mDDSD));
	mDDSD.dwSize = sizeof(mDDSD);
	if ( FAILED(mlpDDSurefacePrimary->Lock(NULL, &mDDSD,
		DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT,
		NULL)) )
	{
		//MessageBox(mhMainWnd, "Lock Falied", "Error", MB_OK);
		//PostQuitMessage(0);
		return;
	}

	Draw(Timer);

	if ( FAILED(mlpDDSurefacePrimary->Unlock(NULL)) )
	{
		MessageBoxA(mhMainWnd, "Unlock Falied", "Error", MB_OK);
		PostQuitMessage(0);
		return;
	}

	//if (!ShowDebugInfo)	return;
	if ( FAILED(mlpDDSurefacePrimary->GetDC(&hdc)) )
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
	if ( FAILED(mlpDDSurefacePrimary->ReleaseDC(hdc)) )
	{
		Exception* e = new Exception("DC release ERR");
		e->showErrorDialog();
		delete e;
		return;
	}

	return;
}

void TestApp::GlobalInitialization()
{
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
	// TODO: �ڴ˴����ʵ�ִ���.
	if ( !InitMainWindow() )
	{
		throw new Isatronia::Exception::RuntimeException(
			"Initralize main window Failed.");
	}

	if ( !InitDDraw() )
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
	// TODO: �ڴ˴����ʵ�ִ���.
	switch ( msg )
	{
	case WM_ACTIVATE:
		if ( LOWORD(wParam) == WA_INACTIVE )
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
		// TODO: �ڴ˴����ʹ�� hdc ���κλ�ͼ����...
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

int flag = 0;// ���ڲ����ж�
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
		// ���������һ���ƶ�
		if (Chara.GetX() > 960 && Chara.GetX() < (Map.mBitMapInfoHeader.biWidth - 960))
		{
			Camerax = Chara.GetX() - 960;
		}

		if (Chara.GetX() < 960)
		{
			Camerax = 0;
		}

		// ����׼��дһ�µ�����ж�
		// ˼·�Ƕ���ҽ�ɫ�·������ؽ���rgb�ȶԣ�����ͱ�����ɫһ��˵��û����ŵ�
		// �����µ�(0v0)

		// Anim slect
		// ����ǻ�������
		DrawImageToDDSurface(TestApp::bkg, mDDSD, TestApp::bkg.GetRect(), 0, 0);

		// ���ﻭ��ͼ
		DrawImageToDDSurface(Map, mDDSD, Map.GetCameraRECT(Camerax, Cameray, mClientWidth, mClientHeight), 0, 0);

		// ��ʼ����ȶ�
		// ʹ���ж�������������ͷû
		// ��Ϊ����֡����������ÿ��ֻ��Ҫ�ȶ�Vy������
		// ���y�᷽���ٶ�С����˵���������Ϸɣ����ù�
		if (Chara.Getvy() >= 0)
		{
			// �����ɫ���ڵ���
			if (Chara.IsFalling())
			{
				for (int j = 0; j < Chara.Getvy(); j++)
				{
					for (int i = Chara.detectRect.left; i < Chara.detectRect.right; i++)
					{
						// ����Ҫ����ֵʱһ����סҪ���������
						// Ҫ����xֵ��ΧΪ ��ײ���� -- ��ײ����
						judx = Chara.GetX() - Camerax + i;
						// Ҫ����yֵ��ΧΪ ��ײ���� -- ��ײ����+ y�᷽���ٶ�
						judy = Chara.GetY() - Cameray + Chara.detectRect.bottom + j;

						// �����߽�û�м���Ҫ
						if (judx > mClientWidth || judx < 0) break;
						if (judy > mClientHeight || judy < 0) break;

						//�����رȶ�,��ǽ��վס
						// ��Ϊ�������������Ͻ��м�����Բ����ü���������������
						if (GetPixelRGB(judx, judy) != TestApp::bkg.GetPixelRGB(judx, judy))
						{
							Chara.ForceSetVy(j);
							Chara.StopFall();
						}
					}
					// ����Ĺ�˵��֮ǰ��ѭ�����Ѿ������쳣�������˳�ѭ��
					if (!Chara.IsFalling()) break;
				}
			}
			// ���û�ڵ�������еĻ�ÿһ֡���һ���Ƿ�����
			else
			{
				flag = 0;
				for (int i = Chara.detectRect.left; i < Chara.detectRect.right; i++)
				{
					// ��ײ�����ֹ��
					// x�᣺ ��ײ������
					judx = Chara.GetX() - Camerax + i;
					judy = Chara.GetY() - Cameray + Chara.detectRect.bottom + 1;
					if (GetPixelRGB(judx, judy) == TestApp::bkg.GetPixelRGB(judx, judy))
					{
						// �˴�flag�������ڱ���ÿ�����뱳��ɫһ�µ����ظ���
						flag++;
					}
				}
				// ���������Ѿ���ȫ�뿪ƽ̨
				if (flag >= (Chara.detectRect.right - Chara.detectRect.left))
				{
					Chara.Fall();
				}
			}
		}
		// �������������ײ��⣬��Ҫ��������ײͣ���Ῠ��ǽ��
		if (Chara.Getvx() != 0 && Chara.Getvy() >= 20)
		{
			flag = 0;
			// �ı�һ��ϵ�����򻯺����ж�
			if (Chara.Getvx() > 0)	flag = 1;
			if (Chara.Getvx() < 0)	flag = -1;

			// ����������
			// ����x����Ϊ �����������
			judx = Chara.GetX() - Camerax	// ��׼���꣨��������ӽ��µ���������
				+ ((Chara.detectRect.left + Chara.detectRect.right) >> 1)	// �������ֵ��õ���ɫ��x����
				+ (flag * ((Chara.detectRect.right - Chara.detectRect.left) >> 1)); // �����ײ�������������ж���ʼx
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
				// ���Ǳ�׼ֵ˵�����Ĺ��ˣ�ǰ���⵽ǽ����
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

		// ���ڿ���
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

		// ����ǻ���ҵ�
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
		// ����ǻ�������
		DrawImageToDDSurface(TestApp::bkg, mDDSD, TestApp::bkg.GetRect(), 0, 0);

		// ���ﻭ��ͼ
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

// ������ǰ������
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
				// �����ǽ����
				for (int i = Chara.detectRect.left; i < Chara.detectRect.right; i++)
				{
					judx = Chara.GetX() + i;
					judy = Chara.GetY() + Chara.detectRect.bottom - 1;
					// �������ʱ��û�л��������Կ�����ô��⣺
					if (GetPixelRGB(judx, judy) != Role::bkg.GetPixelRGB(judx, judy))
					{
						flag += 1;// ����һ���ж�������ֵ,˵����ǽ����
						break;
					}
				}
				// ���û��ǽ��
				// ������ؼ��
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