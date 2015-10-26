#pragma once

#include "ContainerBuilder.h"
#include "Details/ServiceInstanceRegisterer.h"
#include "Details/ServiceTypeRegisterer.h"
#include "Details/ServiceFactoryRegisterer.h"

namespace DI
{

	template<class T>
	auto ContainerBuilder::registerInstance(T &&instance) -> ServiceInstanceRegisterer<typename Details::UnderlyingType<T>::Type>
	{
		using Registerer = Details::ServiceInstanceRegisterer<T>;
		using PublicType = ServiceInstanceRegisterer<typename Details::UnderlyingType<T>::Type>;

		return createRegisterer<Registerer, PublicType>(std::forward<T>(instance));
	}

	template<class T>
	auto ContainerBuilder::registerType() -> ServiceTypeRegisterer<T>
	{
		using Registerer = Details::ServiceTypeRegisterer<T>;
		using PublicType = ServiceTypeRegisterer<T>;

		return createRegisterer<Registerer, PublicType>();
	}

	template<class T>
	auto ContainerBuilder::registerFactory(T factory) -> ServiceFactoryRegisterer<typename Details::UnderlyingType<typename Details::FunctionResultType<T>::Type>::Type>
	{
		using Registerer = Details::ServiceFactoryRegisterer<T>;
		using PublicType = ServiceFactoryRegisterer<typename Details::UnderlyingType<typename Details::FunctionResultType<T>::Type>::Type>;

		return createRegisterer<Registerer, PublicType>(factory);
	}

	template<class T, class S, class... U>
	auto ContainerBuilder::createRegisterer(U&&... param)
	{
		auto registerer = std::make_shared<T>(std::forward<U>(param)...);
		_service_registerers.insert(registerer);

		return S(this, registerer);
	}

}