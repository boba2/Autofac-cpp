#pragma once

#include <stdexcept>

namespace DI
{
	namespace Error
	{

		class ServiceInstanceNotResolvableAsUniquePtr : public std::logic_error
		{
		public:
			ServiceInstanceNotResolvableAsUniquePtr()
				: logic_error("Cannot resolve service instance as std::unique_ptr")
			{}
		};

	}
}