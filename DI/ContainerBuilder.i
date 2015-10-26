#pragma once

#include "ContainerBuilder.h"
#include "Details/ServiceInstanceRegisterer.h"
#include "Details/ServiceTypeRegisterer.h"
#include "Details/ServiceFactoryRegisterer.h"

namespace DI
{

	template<class T>
	auto ContainerBuilder::registerInstance(T &&instance)
	{
		return createRegisterer<Details::ServiceInstanceRegisterer<T>>(std::forward<T>(instance));
	}

	template<class T>
	auto ContainerBuilder::registerType()
	{
		return createRegisterer<Details::ServiceTypeRegisterer<T>>();
	}

	template<class T>
	auto ContainerBuilder::registerFactory(T factory)
	{
		return createRegisterer<Details::ServiceFactoryRegisterer<T>>(factory);
	}

	template<class T, class... U>
	auto ContainerBuilder::createRegisterer(U&&... param)
	{
		auto registerer = std::make_shared<T>(std::forward<U>(param)...);
		_service_registerers.insert(registerer);

		return typename T::PublicType(this, registerer);
	}

}