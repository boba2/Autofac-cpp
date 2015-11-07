#pragma once

#include "Support/DIdecl.h"
#include "Details/ServiceRegisterer.h"

namespace DI
{

	class Container;
	class ContainerBuilder;

	template<class T>
	class ServiceInstanceRegisterer;

	template<class T>
	class ServiceTypeRegisterer;

	template<class T>
	class ServiceFactoryRegisterer;

	class DI_API ServiceRegisterer
	{
	public:
		template<class U>
		auto registerInstance(U &&instance) -> ServiceInstanceRegisterer<U>;

		template<class U>
		auto registerType() -> ServiceTypeRegisterer<U>;

		template<class U>
		auto registerFactory(U factory) -> ServiceFactoryRegisterer<U>;

		Container build() const;

	protected:
		class Impl;

		explicit ServiceRegisterer(ContainerBuilder& container_builder);
		ServiceRegisterer(const ServiceRegisterer& other);

		Details::ServiceResolvers getServiceResolvers() const;

	private:
		template<class T, class S, class... U>
		auto createRegisterer(U&&... param);

		void addRegisterer(Details::ServiceRegistererPtr<> registerer);

#pragma warning(disable:4251)
		std::shared_ptr<Impl> _impl;
#pragma warning(default:4251)
		ContainerBuilder& _container_builder;
	};

}

#include "ServiceInstanceRegisterer.h"
#include "ServiceTypeRegisterer.h"
#include "ServiceFactoryRegisterer.h"

namespace DI
{
	template<class T>
	auto ServiceRegisterer::registerInstance(T &&instance) -> ServiceInstanceRegisterer<T>
	{
		return createRegisterer<Details::ServiceInstanceRegisterer<T>, ServiceInstanceRegisterer<T>>(std::forward<T>(instance));
	}

	template<class T>
	auto ServiceRegisterer::registerType() -> ServiceTypeRegisterer<T>
	{
		return createRegisterer<Details::ServiceTypeRegisterer<T>, ServiceTypeRegisterer<T>>();
	}

	template<class T>
	auto ServiceRegisterer::registerFactory(T factory) -> ServiceFactoryRegisterer<T>
	{
		return createRegisterer<Details::ServiceFactoryRegisterer<T>, ServiceFactoryRegisterer<T>>(factory);
	}

	template<class T, class S, class... U>
	auto ServiceRegisterer::createRegisterer(U&&... param)
	{
		auto registerer = std::make_shared<T>(std::forward<U>(param)...);
		addRegisterer(registerer);

		return S(registerer, *this);
	}

}