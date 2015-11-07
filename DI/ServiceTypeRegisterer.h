#pragma once

#include "Details/ServiceAliasRegisterer.h"
#include "Details/UnderlyingType.h"
#include "Details/ServiceTypeRegisterer.h"

namespace DI
{

	template<class T>
	class ServiceTypeRegisterer : public ServiceRegisterer
	{
	public:
		static_assert(!std::is_abstract<T>::value, "Cannot register service of an abstract type");
		static_assert(std::is_same<T, typename Details::UnderlyingType<T>::Type>::value, "Cannot register service of a decorated type");

		using ServiceType = T;

		auto singleInstance() -> ServiceTypeRegisterer&;
		auto autoManaged() -> ServiceTypeRegisterer&;
		auto asSelf() -> ServiceTypeRegisterer&;

		template<class U>
		auto as() -> ServiceTypeRegisterer&;


	private:
		ServiceTypeRegisterer(std::shared_ptr<Details::ServiceTypeRegisterer<T>> impl, ServiceRegisterer& service_registerer);

		friend class ServiceRegisterer;

		std::shared_ptr<Details::ServiceTypeRegisterer<T>> const _impl;
	};

	template<class T>
	auto ServiceTypeRegisterer<T>::singleInstance() -> ServiceTypeRegisterer&
	{
		_impl->setSingleInstance();

		return *this;
	}

	template<class T>
	auto ServiceTypeRegisterer<T>::autoManaged() -> ServiceTypeRegisterer&
	{
		_impl->setAutoManaged();

		return *this;
	}

	template<class T>
	template<class U>
	auto ServiceTypeRegisterer<T>::as() -> ServiceTypeRegisterer&
	{
		static_assert(std::is_base_of<U, ServiceType>::value, "Alias should be a resolvable base class of the service class being registered");

		_impl->registerAlias(std::make_shared<Details::ServiceAliasRegisterer<U, ServiceType>>());

		return *this;
	}

	template<class T>
	auto ServiceTypeRegisterer<T>::asSelf() -> ServiceTypeRegisterer&
	{
		return as<ServiceType>();
	}

	template<class T>
	ServiceTypeRegisterer<T>::ServiceTypeRegisterer(std::shared_ptr<Details::ServiceTypeRegisterer<T>> impl, ServiceRegisterer& service_registerer)
		: ServiceRegisterer(service_registerer),
		_impl(impl)
	{}
}