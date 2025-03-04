//--------------------------------------------------------------------------------------
// File: Animation.cpp
//
// Copyright (c) Ishgrina. All rights reserved.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------
#include "Animation.h"

namespace Isatronia::Resource
{
	using std::vector;

	Animation::Animation()
	{
		this->mAnimClip = vector<Image*>();
		this->mIndex = static_cast<unsigned __int32>( 0 );
		return;
	}
	Animation::Animation(Animation& anim)
	{
		this->mAnimClip = std::move(anim.mAnimClip);
		this->mIndex = anim.mIndex;
		return;
	}

	Animation::Animation(Animation&& anim)
	{
		this->mAnimClip = std::move(anim.mAnimClip);
		this->mIndex = anim.mIndex;
		return;
	}

	Animation::~Animation()
	{
		deleteClip();
		return;
	}

	const vector<Image*>& Animation::getClip()
	{
		return this->mAnimClip;
	}

	void Animation::setClip(vector<Image*> clip)
	{
		this->mAnimClip = clip;
		return;
	}

	const Image* Animation::getCurrentImage()
	{
		return mAnimClip[( mIndex++ ) % mAnimClip.size()];
	}

	const Image* Animation::getImageByIndex(const __int32 index)
	{
		return mAnimClip[index % mAnimClip.size()];
	}

	void Animation::deleteClip()
	{
		for ( auto img : mAnimClip )
		{
			if ( img )
			{
				delete img;
			}
		}
		vector<Image*>().swap(mAnimClip);
		this->mIndex = 0;
		return;
	}
}