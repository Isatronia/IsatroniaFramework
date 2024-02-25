//--------------------------------------------------------------------------------------
// File: Job.h
//
// Copyright (c) Ishgrina. All rights reserved.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------
#include <iostream>
#include <thread>
#include <concepts>
namespace Isatronia::Framework
{
	class Job
	{
	private:
		std::jthread* job = nullptr;
	public:
		Job(std::jthread* thread);
	};

	template<std::invocable F>
	void AddJob(F func);
}