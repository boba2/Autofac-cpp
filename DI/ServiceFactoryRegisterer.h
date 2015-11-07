#pragma once

#include "Details/ServiceAliasRegisterer.h"
#include "Details/FunctionTraits.h"
#include "Details/UnderlyingType.h"
#include "Details/ServiceFactoryRegisterer.h"

namespace DI
{

	template<class T>
	class ServiceFactoryRegisterer : public ServiceRegisterer
	{
	public:
		using ServiceType = typename Details::UnderlyingType<typename Details::FunctionResultType<T>::Type>::Type;

		auto singleInstance() -> ServiceFactoryRegisterer&;
		auto autoManaged() -> ServiceFactoryRegisterer&;
		auto asSelf() -> ServiceFactoryRegisterer&;

		template<class V>
		auto as()->ServiceFactoryRegisterer&;

	private:
		ServiceFactoryRegisterer(std::shared_ptr<Details::ServiceFactoryRegisterer<T>> impl, ServiceRegisterer& service_registerer);

		friend class ServiceRegisterer;

		std::shared_ptr<Details::ServiceFactoryRegisterer<T>> const _impl;
	};

	template<class T>
	auto ServiceFactoryRegisterer<T>::singleInstance() -> ServiceFactoryRegisterer&
	{
		_impl->setSingleInstance();

		return *this;
	}

	template<class T>
	auto ServiceFactoryRegisterer<T>::autoManaged() -> ServiceFactoryRegisterer&
	{
		_impl->setAutoManaged();

		return *this;
	}

	template<class T>
	template<class V>
	auto ServiceFactoryRegisterer<T>::as() -> ServiceFactoryRegisterer&
	{
		static_assert(std::is_base_of<V, ServiceType>::value, "Alias should be a resolvable base class of the service class being registered");

		_impl->registerAlias(std::make_shared<Details::ServiceAliasRegisterer<V, ServiceType>>());

		return *this;
	}

	template<class T>
	auto ServiceFactoryRegisterer<T>::asSelf() -> ServiceFactoryRegisterer&
	{
		return as<ServiceType>();
	}

	template<class T>
	ServiceFactoryRegisterer<T>::ServiceFactoryRegisterer(std::shared_ptr<Details::ServiceFactoryRegisterer<T>> impl, ServiceRegisterer& service_registerer)
		: ServiceRegisterer(service_registerer),
		_impl(impl)
	{}
}