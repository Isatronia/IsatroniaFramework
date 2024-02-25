//--------------------------------------------------------------------------------------
// File: Animation.cpp
//
// Copyright (c) Ishgrina. All rights reserved.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------
#include "Animation.h"

namespace Isatronia::Resource {
	using std::vector;

	Animation::Animation() {
		this->mAnimClip = vector<Image*>();
		return;
	}

	vector<Image*> Animation::getClip() {
		return this->mAnimClip;
	}

	void Animation::setClip(vector<Image*> clip) {
		this->mAnimClip = clip;
		return;
	}

	Image* Animation::getCurrentImage()
	{
		return mAnimClip[mCurrentIndex++];
	}
}