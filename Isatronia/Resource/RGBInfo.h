#pragma once

#include <Windows.h>

namespace Isatronia::Resource {
	class RGBInfo {
	public:
		UCHAR r;
		UCHAR g;
		UCHAR b;

	public:
		explicit RGBInfo(UCHAR R, UCHAR G, UCHAR B);
		RGBInfo(const RGBInfo&) noexcept;
		RGBInfo(const RGBInfo&&) noexcept;
		RGBInfo();

		virtual bool operator==(const RGBInfo&);
		virtual void operator=(const RGBInfo&);
		virtual void operator=(const RGBInfo&&) noexcept;
	};

	class RGBAInfo : public RGBInfo
	{
	public:
		UCHAR a;
	public:
		explicit RGBAInfo(UCHAR R, UCHAR G, UCHAR B, UCHAR A);
		RGBAInfo(const RGBAInfo&);
		RGBAInfo(const RGBAInfo&&) noexcept;
		RGBAInfo();

		virtual bool operator==(const RGBAInfo&);
		virtual bool operator==(const RGBInfo&) override;
		virtual void operator=(const RGBAInfo&);
		virtual void operator=(const RGBAInfo&&) noexcept;
	};
}