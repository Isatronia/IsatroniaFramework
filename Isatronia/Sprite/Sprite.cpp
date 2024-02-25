#include "Sprite.h"
#include "../Exceptions/Exception.h"

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

	Image* Sprite::getRenderingTarget()
	{
		try
		{
			return mAnimList[mAnimationIndex]->getCurrentImage();
		}
		catch ( ... )
		{
			throw new RuntimeException(L"Animation Index not included");
		}
		return;
	}
}