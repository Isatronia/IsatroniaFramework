#include "Exception.h"

namespace Isatronia::Exception
{
	using std::string;

	class RuntimeException : public LogicException
	{
	public:
		//RuntimeException(const char*&);
		using LogicException::LogicException;
	};
}