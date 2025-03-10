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
		// TODO: 在此处添加实现代码.
		return GetTickCount64() - mBaseTime;
	}

	__int64 Timer::DeltaTime()
	{
		// TODO: 在此处添加实现代码.
		return GetTickCount64() - mPrevTime;
	}

	void Timer::Reset()
	{
		// TODO: 在此处添加实现代码.
		mBaseTime = GetTickCount64();
	}

	void Timer::Start()
	{
		// TODO: 在此处添加实现代码.
		if ( mStopped )
		{
			mStopped = false;
		}
	}

	void Timer::Stop()
	{
		// TODO: 在此处添加实现代码.
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