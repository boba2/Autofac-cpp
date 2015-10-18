#pragma once

#include <string>

namespace DI
{
	namespace Error
	{

		class ServiceNotRegistered : public std::logic_error
		{
		public:
			template<class T>
			auto static fromType()
			{
				return ServiceNotRegistered(typeid(T).name());
			}

		private:
			explicit ServiceNotRegistered(std::string type_name)
				: logic_error(std::string("Trying to resolve service of an unknown type: ") + type_name)
			{}
		};

	}
}