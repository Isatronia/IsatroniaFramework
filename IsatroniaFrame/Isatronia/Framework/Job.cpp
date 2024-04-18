//--------------------------------------------------------------------------------------
// File: Job.cpp
//
// Copyright (c) Ishgrina. All rights reserved.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------
#include "Job.h"

namespace Isatronia::Framework
{
	Job::Job(std::jthread* thread)
	{
		this->job = thread;
		thread = nullptr;
		return;
	}

	template<std::invocable F>
	Job AddJob(F func)
	{
		Job* ret = new Job(std::jthread(func));
		return ret;
	}
}