#pragma once

#include <system_error>

namespace DI
{
	namespace Error
	{

		class ServiceNotRegistered : public std::logic_error
		{
		public:
			explicit ServiceNotRegistered()
				: logic_error("Trying to resolve service of an unknown type")
			{}
		};

	}
}