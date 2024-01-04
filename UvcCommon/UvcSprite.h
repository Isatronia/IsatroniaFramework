#include "UvcImage.h"

namespace IsaFrame {
	// Role类：
	// 存储了玩家信息，包括贴图和位置
	// 以及一部分的物理信息，如速度
	// 开枪高度y+36
	class Sprite
	{
		// constuctor & desrturctor
	public:
		Sprite();
		explicit Sprite(int CharaX, int CharaY);
		Sprite(const Sprite&) = delete;

		// public methods
	public:
		// 读取人物坐标
		inline int getX() { return mCharax; };
		inline int getY() { return mCharay; };
		inline POINT getPoint()
		{
			POINT p;
			p.x = mCharax;
			p.y = mCharay;
			return p;
		};

		// 读取待渲染贴图，依据内部变量自动选择。
		UvcImage getBMP();

		// 判断角色是否在移动
		inline bool isMoving() { return (mCharavx) ? 1 : 0; };

		// 角色移动操作
		virtual inline void Jump();
		virtual inline void RunLeft() { mCharavx = -mStdvx; mfaceRight = false; };
		virtual inline void RunRight() { mCharavx = mStdvx; mfaceRight = true; };
		virtual inline void StopRun();

		// call when Role is falling
		inline void Fall() { mFall = true; };
		// Call when Role stop Falling.
		inline void StopFall() { mFall = false; mJumpTimes = 2; };
		inline bool IsFalling() { return mFall; };

		// 角色移动的时候的更新函数
		void Move();
		// 设置碰撞箱
		void SetDetectRECT(UINT Width = 65535, UINT Height = 65535);
		// 动画计数
		void Count();

		inline bool IsFaceRight() { return mfaceRight; };
		inline bool IsFireing() { return mFire; };
		inline void Fireing() { if (LastFireTick - GetTickCount64() < 100 || Getvx())return; mFire = true; LastFireTick = GetTickCount64(); return; };
		inline void Fired() { mFire = false; return; };

		inline void Damage(ULONGLONG Dmg);

	public:
		// getters for debug and Edge-Detect.
		inline LONG Getvy() { return mCharavy; };
		inline void ForceSetVy(LONG v) { mCharavy = v; return; };
		inline LONG Getvx() { return mCharavx; };
		inline void ForceSetVx(LONG v) { mCharavx = v; return; };
		inline POINT GetCenterPos();
		inline int GetDieState() { return mdie; };
		inline void SetDieState(int state) { mdie = state; return; }
		inline void ForceSetPos(LONG X, LONG Y) { mCharax = X; mCharay = Y; return; };
		inline LONG GetStdVx() { return mStdvx; };

	protected:
		void PlotPixel(DDSURFACEDESC2& ddsd, int x, int y, int r, int g = -1, int b = -1, int a = 0);
		static void PlotPixel(UvcImage UImg, int x, int y, int r, int g = -1, int b = -1, int a = 0);

	public:
		// 角色贴图
		UvcImage uBmp;
		UvcImage rAnim[5];
		UvcImage lAnim[5];

		RECT detectRect;

	public:
		void SetClientSize(int Width, int Height);
		static int mClientWidth;
		static int mClientHeight;
		/*static DDPIXELFORMAT CanvasPF;
		static DDSURFACEDESC2 CanvasDDSD;*/

	private:
		int mJumpTimes;

		LONG mCharax;
		LONG mCharay;
		LONG mCharavx;
		LONG mCharavy;
		LONG mStdvx;

		int mAnimIndex;
		int mAnimIndexAddCount;
		int mdie;

		bool mfaceRight;
		bool mFall;

		ULONGLONG LastFireTick;
		bool mFire;

		int mAtk;
		UCHAR mHp;
	};
}