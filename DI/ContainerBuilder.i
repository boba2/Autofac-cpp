#pragma once

#include "Details/ServiceInstanceRegisterer.h"
#include "Details/ServiceTypeRegisterer.h"
#include "Details/ServiceFactoryRegisterer.h"

namespace DI
{

	template<class T>
	auto ContainerBuilder::registerInstance(T &&instance) -> ServiceInstanceRegisterer<T>
	{
		return createRegisterer<Details::ServiceInstanceRegisterer<T>, ServiceInstanceRegisterer<T>>(std::forward<T>(instance));
	}

	template<class T>
	auto ContainerBuilder::registerType() -> ServiceTypeRegisterer<T>
	{
		return createRegisterer<Details::ServiceTypeRegisterer<T>, ServiceTypeRegisterer<T>>();
	}

	template<class T>
	auto ContainerBuilder::registerFactory(T factory) -> ServiceFactoryRegisterer<T>
	{
		return createRegisterer<Details::ServiceFactoryRegisterer<T>, ServiceFactoryRegisterer<T>>(factory);
	}

	template<class T, class S, class... U>
	auto ContainerBuilder::createRegisterer(U&&... param)
	{
		auto registerer = std::make_shared<T>(std::forward<U>(param)...);
		addRegisterer(registerer);

		return S(registerer, *this);
	}

}