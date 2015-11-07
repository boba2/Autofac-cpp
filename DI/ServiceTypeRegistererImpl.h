#pragma once

#include "Details/ServiceAliasRegisterer.h"

namespace DI
{
	
	class ServiceTypeRegistererImpl
	{
	public:
		virtual ~ServiceTypeRegistererImpl() {}

		virtual void setSingleInstance() = 0;
		virtual void setAutoManaged() = 0;
		virtual void registerAlias(std::shared_ptr<Details::ServiceAliasRegisterer<>> alias_registerer) = 0;
	};

}