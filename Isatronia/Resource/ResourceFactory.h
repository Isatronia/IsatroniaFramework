//--------------------------------------------------------------------------------------
// File: ResourceFactory.h
//
// Copyright (c) Ishgrina. All rights reserved.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------
#pragma once
#include "Resource.h"

namespace Isatronia::Resource {


	// Factory to Create Resource
	class ResourceFactory {
	private:
		static ResourceFactory* mFactory;

	};

	ResourceFactory* ResourceFactory::mFactory = nullptr;
}

int a(int, int);

int a(int b, int c) {
	b = c;
	return;
}