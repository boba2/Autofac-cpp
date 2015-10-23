#pragma once

#include "ServiceRegisterer.h"

namespace DI
{

	class ServiceFactoryRegistererImpl
	{
	public:
		virtual ~ServiceFactoryRegistererImpl() {}

		virtual void setAutoManaged() = 0;
		virtual void registerAlias(std::shared_ptr<Details::ServiceAliasRegisterer<>> alias_registerer) = 0;
	};

	template<class T>
	class ServiceFactoryRegisterer : public ServiceRegisterer<ServiceFactoryRegistererImpl>
	{
	public:
		using ServiceRegisterer::ServiceRegisterer;

		ServiceFactoryRegisterer& autoManaged()
		{
			_impl->setAutoManaged();

			return *this;
		}
	};

}