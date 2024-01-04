#include <vector>

#include "UvcImage.h"

namespace IsaD9Frame {

	class IsaAnim {
	private:
		std::vector<UvcImage> mAnimClip;

	public:
		IsaAnim();

	public:
		std::vector<UvcImage> getClip();
		void setClip(std::vector<UvcImage> clip);
	};

}