//--------------------------------------------------------------------------------------
// File: Timer.cpp
//
// Copyright (c) Ishgrina. All rights reserved.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------
#include "Timer.h"

namespace Isatronia::Framework
{
	Timer::Timer()
	{
		mBaseTime = GetTickCount64();
		return;
	}

	//return total time sence the Timer been setted up
	__int64 Timer::TotalTIme()
	{
		// TODO: �ڴ˴����ʵ�ִ���.
		return GetTickCount64() - mBaseTime;
	}

	__int64 Timer::DeltaTime()
	{
		// TODO: �ڴ˴����ʵ�ִ���.
		return GetTickCount64() - mPrevTime;
	}

	void Timer::Reset()
	{
		// TODO: �ڴ˴����ʵ�ִ���.
		mBaseTime = GetTickCount64();
	}

	void Timer::Start()
	{
		// TODO: �ڴ˴����ʵ�ִ���.
		if ( mStopped )
		{
			mStopped = false;
		}
	}

	void Timer::Stop()
	{
		// TODO: �ڴ˴����ʵ�ִ���.
		if ( !mStopped )
		{
			mStopped = true;
		}
	}

	void Timer::Sign()
	{
		mPrevTime = GetTickCount64();
	}

	void Timer::FrameBegin()
	{
		mTimeOfThisFrime = GetTickCount64();
		return;
	}
}