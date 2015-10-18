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
			registerAlias(std::make_shared<Details::ServiceAliasRegisterer<U, T>>());

			return *this;
		}

	protected:
		virtual void registerAlias(std::shared_ptr<Details::ServiceAliasRegisterer<>> alias_registerer) = 0;
	};

}