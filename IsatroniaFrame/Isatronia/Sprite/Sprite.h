#include <iostream>
#include <map>

#include "../Resource/Animation.h"
#include "../Resource/Image.h"

namespace Isatronia::Sprite
{
	using std::map;
	using std::string;
	using Isatronia::Resource::Animation;
	using Isatronia::Resource::Image;

	enum class FacingDirection
	{
		// 2D
		left,
		right,
		// 3D
		east,
		west,
		south,
		north,
	};

	enum class SpriteState
	{
		beforeCreate,
		created,
		beforeDestroy,
	};

	class Destroyable
	{
	private:
		__int64 mHealth;

	public:
		__int64 getHealth();
		void setHealth(__int64 Health);
	};

	class Sprite
	{
	private:
		std::map<string, Animation*> mAnimList;
		FacingDirection mFacing;
		RECT* mHitBox;
		POINT* mPosition;
		SpriteState mState;
		POINT* mVelocity;
		std::string mAnimationIndex;
	public:
		Sprite(const std::string& path);
		Sprite(Sprite& _S) = delete;
		Sprite(Sprite&& _S) noexcept;
		~Sprite();

		const Image* const getRenderingTarget();

		void setAnimClip(std::string& state);
	private:
		void loadSpriteFromFile(const std::string& path);
	};
}