//--------------------------------------------------------------------------------------
// File: Job.h
//
// Copyright (c) Ishgrina. All rights reserved.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------


#include <iostream>

namespace Isatronia::Framework{

	template <typename T>
	concept Callable = requires( T t )
	{
		{ t() } -> std::invocable<>;
	};

	class Job
	{

	};

}