#pragma once

#include "ServiceRegisterer.h"
#include "ContainerBuilder.h"

namespace DI
{

	template<class T>
	template<class U>
	auto ServiceRegisterer<T>::registerInstance(U &&instance)
	{
		return _container_builder->registerInstance(std::forward<U>(instance));
	}

	template<class T>
	template<class U>
	auto ServiceRegisterer<T>::registerType()
	{
		return _container_builder->registerType<U>();
	}

	template<class T>
	template<class U>
	auto ServiceRegisterer<T>::registerFactory(U factory)
	{
		return _container_builder->registerFactory(factory);
	}

	template<class T>
	Container ServiceRegisterer<T>::build() const
	{
		return _container_builder->build();
	}

}