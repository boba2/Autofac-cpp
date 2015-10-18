#pragma once

#include <string>

namespace DI
{
	namespace Error
	{

		class ServiceNotRegistered : public std::logic_error
		{
		public:
			explicit ServiceNotRegistered(std::string type_name)
				: logic_error(std::string("Trying to resolve service of an unknown type: ") + type_name)
			{}
		};

	}
}