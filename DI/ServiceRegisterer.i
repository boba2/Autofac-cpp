#pragma once

#include "ServiceRegisterer.h"
#include "ContainerBuilder.h"

namespace DI
{

	template<class U>
	inline auto ServiceRegisterer::registerInstance(U &&instance) -> ServiceInstanceRegisterer<typename Details::UnderlyingType<U>::Type>
	{
		return _container_builder->registerInstance(std::forward<U>(instance));
	}

	template<class U>
	inline auto ServiceRegisterer::registerType() -> ServiceTypeRegisterer<U>
	{
		return _container_builder->registerType<U>();
	}

	template<class U>
	inline auto ServiceRegisterer::registerFactory(U factory) -> ServiceFactoryRegisterer<typename Details::UnderlyingType<typename Details::FunctionResultType<U>::Type>::Type>
	{
		return _container_builder->registerFactory(factory);
	}

	inline Container ServiceRegisterer::build() const
	{
		return _container_builder->build();
	}

}