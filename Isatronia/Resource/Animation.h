#pragma once
#include <vector>

#include "Image.h"

namespace Isatronia::Resource {

	class Animation {
	private:
		std::vector<Image*> mAnimClip;

	public:
		Animation();

	public:
		std::vector<Image*> getClip();
		void setClip(std::vector<Image*> clip);
	};

}