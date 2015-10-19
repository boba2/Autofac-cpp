#pragma once

#include "Details/ServiceAliasRegisterer.h"

namespace DI
{
	
	template<class T>
	class ServiceRegisterer
	{
	public:
		virtual ~ServiceRegisterer() {}

		template<class U>
		ServiceRegisterer& as()
		{
			static_assert(std::is_base_of<U, T>::value, "Alias should be a base class of the service being registered");

			registerAlias(std::make_shared<Details::ServiceAliasRegisterer<U, T>>());

			return *this;
		}

		ServiceRegisterer& asSelf()
		{
			return as<T>();
		}

	protected:
		virtual void registerAlias(std::shared_ptr<Details::ServiceAliasRegisterer<>> alias_registerer) = 0;
	};

}