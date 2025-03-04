//--------------------------------------------------------------------------------------
// File: Animation.h
//
// Copyright (c) Ishgrina. All rights reserved.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------
#pragma once
#include <vector>

#include "Image.h"
#include "Resource.h"

namespace Isatronia::Resource
{
	class Animation: protected Resource
	{
	private:
		std::vector<Image*> mAnimClip;
		unsigned __int32 mIndex;

	public:
		Animation();
		Animation(Animation&);
		Animation(Animation&&);
		~Animation();

	public:
		const std::vector<Image*>& getClip();
		void setClip(std::vector<Image*> clip);

		const Image* getCurrentImage();
		const Image* getImageByIndex(const __int32 index);
	protected:
		void deleteClip();
	};
}