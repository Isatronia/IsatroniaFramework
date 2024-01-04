//***************************************************************************************
// UvcTimer.cpp by Aaron Jsc (C) 2020 All Rights Reserved.
// licenced under CC BY-NC-SA License.
//***************************************************************************************
#include "UvcTimer.h"

UvcTimer::UvcTimer() {
	mBaseTime = GetTickCount64();
	return;
}

//return total time sence the Timer been setted up
__int64 UvcTimer::TotalTIme()
{
	// TODO: 在此处添加实现代码.
	return GetTickCount64() - mBaseTime;
}

__int64 UvcTimer::DeltaTime()
{
	// TODO: 在此处添加实现代码.
	return GetTickCount64() - mPrevTime;
}

void UvcTimer::Reset()
{
	// TODO: 在此处添加实现代码.
	mBaseTime = GetTickCount64();
}

void UvcTimer::Start()
{
	// TODO: 在此处添加实现代码.
	if (mStopped)
	{
		mStopped = false;
	}
}

void UvcTimer::Stop()
{
	// TODO: 在此处添加实现代码.
	if (!mStopped)
	{
		mStopped = true;
	}
}

void UvcTimer::Sign()
{
	mPrevTime = GetTickCount64();
}

void UvcTimer::FrameBegin()
{
	mTimeOfThisFrime = GetTickCount64();
	return;
}