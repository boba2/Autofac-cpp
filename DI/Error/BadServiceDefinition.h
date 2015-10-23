#pragma once

#include <system_error>

namespace DI
{
	namespace Error
	{

		class BadServiceDefinition : public std::logic_error
		{
		public:
			explicit BadServiceDefinition()
				: logic_error("Invalid service definition")
			{}
		};

	}
}