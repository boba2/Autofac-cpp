#pragma once

#include "Details/ServiceAliasRegisterer.h"
#include "ServiceInstanceRegistererImpl.h"
#include "Details/UnderlyingType.h"

namespace DI
{

	template<class T>
	class ServiceInstanceRegisterer : public ServiceRegisterer
	{
	public:
		using ServiceType = typename Details::UnderlyingType<T>::Type;

		ServiceInstanceRegisterer(std::shared_ptr<ServiceInstanceRegistererImpl> impl, ServiceRegisterer& service_registerer)
			: ServiceRegisterer(service_registerer),
			  _impl(impl)
		{}

		template<class U>
		ServiceInstanceRegisterer& as()
		{
			static_assert(std::is_base_of<U, ServiceType>::value, "Alias should be a resolvable base class of the service being registered");

			_impl->registerAlias(std::make_shared<Details::ServiceAliasRegisterer<U, ServiceType>>());

			return *this;
		}

		ServiceInstanceRegisterer& asSelf()
		{
			return as<ServiceType>();
		}

	private:
		std::shared_ptr<ServiceInstanceRegistererImpl> const _impl;
	};

}