#pragma once

#include "ServiceRegisterer.h"
#include "ContainerBuilder.h"

namespace DI
{

	template<class T>
	template<class U>
	auto ServiceRegisterer<T>::registerInstance(U &&instance)// -> ServiceInstanceRegisterer<typename Details::UnderlyingType<U>::Type>
	{
		return _container_builder->registerInstance(std::forward<U>(instance));
	}

	template<class T>
	template<class U>
	auto ServiceRegisterer<T>::registerType()// -> ServiceTypeRegisterer<U>
	{
		return _container_builder->registerType<U>();
	}

	template<class T>
	template<class U>
	auto ServiceRegisterer<T>::registerFactory(U factory)// -> ServiceFactoryRegisterer<typename Details::UnderlyingType<typename Details::FunctionResultType<U>::Type>::Type, void>
	{
		return _container_builder->registerFactory(factory);
	}

	template<class T>
	Container ServiceRegisterer<T>::build() const
	{
		return _container_builder->build();
	}

}