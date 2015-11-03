#pragma once

#include "Details/ServiceAliasRegisterer.h"
#include "ServiceRegisterer.h"

namespace DI
{

	class ServiceInstanceRegistererImpl
	{
	public:
		virtual ~ServiceInstanceRegistererImpl() {}

		virtual void registerAlias(std::shared_ptr<Details::ServiceAliasRegisterer<>> alias_registerer) = 0;
	};

	template<class T>
	class ServiceInstanceRegisterer : public ServiceRegisterer
	{
	public:
		using ServiceType = typename Details::UnderlyingType<T>::Type;

		ServiceInstanceRegisterer(std::shared_ptr<ServiceInstanceRegistererImpl> impl, ContainerBuilder* container_builder)
			: ServiceRegisterer(container_builder),
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