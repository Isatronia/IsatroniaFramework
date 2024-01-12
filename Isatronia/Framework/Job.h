#include <iostream>

namespace Isatronia::Framework{

	template <typename T>
	concept Callable = requires( T t )
	{
		{ t() } -> std::invocable<>;
	};

	class Job
	{

	};

}