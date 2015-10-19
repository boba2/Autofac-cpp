#pragma once

#include <system_error>


namespace DI
{
	namespace Error
	{

		class ServiceInstanceNotResolvableAs : public std::logic_error
		{
		public:
			ServiceInstanceNotResolvableAs()
				: logic_error("Cannot resolve service instance through {xxx}")
			{}
		};

	}
}