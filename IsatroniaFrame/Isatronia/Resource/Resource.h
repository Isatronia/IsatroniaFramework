//--------------------------------------------------------------------------------------
// File: Resource.h
//
// Copyright (c) Ishgrina. All rights reserved.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------
#pragma once

#include <Windows.h>

namespace Isatronia::Resource {

	enum class ResourceType {
		none,
		string,
		image,
		sound,
		animation,
		mesh,
	};


	// Base Resource Class, it should be virtual
	class Resource
	{
	public:
		static __int64 GUIDCount;
	private:
		__int64 mGUID;
		ResourceType mResourceType;
	protected:
		void setGUID(__int64 GUID) { mGUID = GUID; };
		virtual void setResourceType(ResourceType type) { mResourceType = type; };
	public:
		Resource() {
			mGUID = Resource::GUIDCount++;
			mResourceType = ResourceType::none;
		};

		__int64 getGUID() { return mGUID; };
		ResourceType getType() { return mResourceType; };
	};
}