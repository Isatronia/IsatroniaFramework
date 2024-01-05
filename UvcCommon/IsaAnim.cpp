#include "IsaAnim.h"

namespace IsaFrame::IsaSpriteFrame {
	using std::vector;

	IsaAnim::IsaAnim() {
		this->mAnimClip = vector<IsaImage>();
		return;
	}

	vector<IsaImage> IsaAnim::getClip() {
		return this->mAnimClip;
	}

	void IsaAnim::setClip(vector<IsaImage> clip) {
		this->mAnimClip = clip;
		return;
	}
}