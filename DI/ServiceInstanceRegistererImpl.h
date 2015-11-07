#pragma once

#include "Details/ServiceAliasRegisterer.h"

namespace DI
{
	
	class ServiceInstanceRegistererImpl
	{
	public:
		virtual ~ServiceInstanceRegistererImpl() {}

		virtual void registerAlias(std::shared_ptr<Details::ServiceAliasRegisterer<>> alias_registerer) = 0;
	};

}