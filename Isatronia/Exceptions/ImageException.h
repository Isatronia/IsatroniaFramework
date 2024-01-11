#pragma once

#include "IsaException.h"

namespace Isatronia::Exception {

	class ImageException : public FileException {
	public:
		ImageException(wstring desc, wstring ImagePath) : FileException(desc, ImagePath) {};
	};

	class BitmapFlipException : public ImageException
	{
	public:
		BitmapFlipException(wstring ExceptionDescription, wstring ImagePath) : ImageException(ExceptionDescription, ImagePath) {};
		BitmapFlipException(wstring ImagePath) {
			setFilePath(ImagePath);
			
		}
	};
}