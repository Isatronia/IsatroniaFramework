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