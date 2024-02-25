//--------------------------------------------------------------------------------------
// File: Animation.h
//
// Copyright (c) Ishgrina. All rights reserved.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------
#pragma once
#include <vector>

#include "Image.h"

namespace Isatronia::Resource
{
	class Animation
	{
	private:
		std::vector<Image*> mAnimClip;
		int mCurrentIndex;

	public:
		Animation();

	public:
		std::vector<Image*> getClip();
		void setClip(std::vector<Image*> clip);

		Image* getCurrentImage();
	};
}