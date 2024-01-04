//***************************************************************************************
// UvcTimer.h by Aaron Jsc (C) 2020 All Rights Reserved.
// licenced under CC BY-NC-SA License.
//***************************************************************************************

#pragma once
#include<Windows.h>

class UvcTimer
{
public:
	// ine seconds
	UvcTimer();
	__int64	TotalTIme();
	__int64 DeltaTime();

	void Reset();	//call before msg loop
	void Start();	//call when unpaused
	void Stop();	// call When paused
	void Sign();	// set a Sign and use to calculate delta time.
	void FrameBegin();	// call when a frame is begin calculate.
private:
	__int64 mSecondPerCount = 0;
	__int64 mDeltaTime = 0;

	__int64 mBaseTime;			// the Time when the Timer been setted up
	__int64 mPausedTime = 0;	// the Time while the Timer is paused
	__int64 mStopTime = 0;		// the last time when Stop() is called.
	__int64 mPrevTime = 0;		// the last time when Sign() is called.
	__int64 mTimeOfThisFrime = 0; // the time when a frame is begin render.

	bool mStopped = false;
};
