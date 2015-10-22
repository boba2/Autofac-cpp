#pragma once

#include <system_error>

namespace DI
{
	namespace Error
	{

		class ServiceNotResolvableAs : public std::logic_error
		{
		public:
			ServiceNotResolvableAs()
				: logic_error("Cannot resolve service")
			{}
		};

	}
}