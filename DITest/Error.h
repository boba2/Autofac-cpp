#pragma once

#include <string>
#include "UnderlyingType.h"

namespace Error 
{
	class ServiceNotRegistered : public std::logic_error
	{
	public:
		template<class T>
		auto static fromType()
		{
			return ServiceNotRegistered(typeid(typename UnderlyingType<T>::Type).name());
		}

	private:
		explicit ServiceNotRegistered(std::string type_name)
			: logic_error(std::string("Trying to resolve service of an unknown type: ") + type_name)
		{}
	};

	class ServiceInstanceNotResolvableAsUniquePtr : public std::logic_error
	{
	public:
		ServiceInstanceNotResolvableAsUniquePtr()
			: logic_error("Cannot resolve service instance as std::unique_ptr")
		{}
	};
}
