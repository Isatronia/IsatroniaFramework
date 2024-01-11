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
}