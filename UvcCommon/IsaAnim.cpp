#include "IsaAnim.h"

namespace IsaD9Frame {
	using std::vector;

	IsaAnim::IsaAnim() {
		this->mAnimClip = vector<UvcImage>();
		return;
	}

	vector<UvcImage> IsaAnim::getClip() {
		return this->mAnimClip;
	}

	void IsaAnim::setClip(vector<UvcImage> clip) {
		this->mAnimClip = clip;
		return;
	}
}