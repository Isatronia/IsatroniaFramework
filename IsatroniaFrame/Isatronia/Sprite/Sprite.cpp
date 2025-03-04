#include "Sprite.h"
#include "Exception.h"
#include "RuntimeException.h"

namespace Isatronia::Sprite
{
	using namespace Isatronia::Exception;

	__int64 Destroyable::getHealth()
	{
		return mHealth;
	}

	void Destroyable::setHealth(__int64 Health)
	{
		mHealth = Health;
		return;
	}

	Sprite::Sprite(const std::string& path)
	{
		mAnimList = std::map<string, Animation*>();
		mFacing = FacingDirection::right;
		mHitBox = new RECT;
		mPosition = new POINT;
		mState = SpriteState::beforeCreate;
		mVelocity = new POINT;
		mAnimationIndex = std::string();
	}

	Sprite::Sprite(Sprite&& _S) noexcept
	{
		mAnimList.swap(_S.mAnimList);
		mFacing = _S.mFacing;
		mState = _S.mState;
		mAnimationIndex = _S.mAnimationIndex;

		// deal with pointers.
		if ( mHitBox ) delete mHitBox;
		mHitBox = _S.mHitBox;
		_S.mHitBox = nullptr;

		if ( mPosition ) delete mPosition;
		mPosition = _S.mPosition;
		_S.mPosition = nullptr;

		if ( mVelocity ) delete mVelocity;
		mVelocity = _S.mVelocity;
		_S.mVelocity = nullptr;
		return;
	}

	Sprite::~Sprite()
	{
		for ( auto [s, anim] : mAnimList )
		{
			delete anim;
		}
		delete mHitBox;
		delete mPosition;
		delete mVelocity;
		return;
	}

	const Image* const Sprite::getRenderingTarget()
	{
		try
		{
			return mAnimList[mAnimationIndex]->getCurrentImage();
		}
		catch ( ... )
		{
			throw new RuntimeException("Animation Index not included");
		}
		return nullptr;
	}

	void Sprite::setAnimClip(std::string& state)
	{
		if ( mAnimList.contains(state) ) { mAnimationIndex = state; }
		return;
	}

	void Sprite::loadSpriteFromFile(const std::string& path)
	{

	}
}