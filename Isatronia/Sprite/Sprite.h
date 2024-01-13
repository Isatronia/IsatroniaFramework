//--------------------------------------------------------------------------------------
// File: Sprite.h
//
// Copyright (c) Ishgrina. All rights reserved.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------
#include <vector>

#include "../Resource/Image.h"
#include "../Resource/Animation.h"

namespace Isatronia::Sprite {
	using std::vector;
	enum class spriteState {
		die,
	};

	using Isatronia::Resource::Animation;
	using Isatronia::Resource::Image;

	// Role类：
	// 存储了玩家信息，包括贴图和位置
	// 以及一部分的物理信息，如速度
	// 开枪高度y+36
	

	// Sprite - 精灵基类
	// Basic Class for all Sprite.
	// Define your Sprite form this class
	class Sprite
	{
	protected:
		int mJumpTimes;

		LONG mCharax;
		LONG mCharay;
		LONG mCharavx;
		LONG mCharavy;

		bool mFacing;
		bool mIsFall;

		int mAtk;
		int mHp;

		RECT mHitBox;

		// 角色贴图
		Animation mImgRes;


		//void SetClientSize(int Width, int Height);
		//static int mClientWidth;
		//static int mClientHeight;
		/*static DDPIXELFORMAT CanvasPF;
		static DDSURFACEDESC2 CanvasDDSD;*/

	// -----------------------------------------------
	// constuctor & desrturctor
	// -----------------------------------------------
	public:
		Sprite();
		explicit Sprite(int CharaX, int CharaY);
		Sprite(const Sprite&) = delete;

	// -----------------------------------------------
	// public methods
	// -----------------------------------------------
	public:
		// 读取待渲染贴图，依据内部变量自动选择。
		Image* getCurrentImage();
		// 角色移动操作
		virtual inline void Jump();
		virtual inline void RunLeft();
		virtual inline void RunRight();
		virtual inline void StopRun();

		// 角色移动的时候的更新函数
		void Move();

		// 动画计数
		void Count();

		inline void Damage(ULONGLONG Dmg);

		// 判断角色是否在移动
		inline bool isMoving() { return (mCharavx) ? 1 : 0; };
	// -----------------------------------------------
	// Getters and Setters.
	// -----------------------------------------------
	public:
		// 读取人物坐标
		inline int getX();
		inline int getY();
		inline void setX(LONG x);
		inline void setY(LONG y);
		inline POINT getPoint();
		inline void setPoint(POINT p);

		// 设置碰撞箱
		void setHitBox(RECT rect);


		// getters for debug and Edge-Detect.
		inline LONG Getvy() { return mCharavy; };
		inline void ForceSetVy(LONG v) { mCharavy = v; return; };
		inline LONG Getvx() { return mCharavx; };
		inline void ForceSetVx(LONG v) { mCharavx = v; return; };
		inline POINT GetCenterPos();

	protected:
		void PlotPixel(DDSURFACEDESC2& ddsd, int x, int y, int r, int g = -1, int b = -1, int a = 0);
		//static void PlotPixel(Image& UImg, int x, int y, int r, int g = -1, int b = -1, int a = 0);
		inline void ForceSetPos(LONG X, LONG Y) { mCharax = X; mCharay = Y; return; };


		//inline LONG GetStdVx() { return mStdvx; };
		//inline int GetDieState() { return mdie; };
		//inline void SetDieState(int state) { mdie = state; return; }

	};
}