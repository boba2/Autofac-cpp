#pragma once

namespace DI
{

	template<class U>
	inline auto ServiceRegisterer::registerInstance(U &&instance) -> ServiceInstanceRegisterer<U>
	{
		return _container_builder->registerInstance(std::forward<U>(instance));
	}

	template<class U>
	inline auto ServiceRegisterer::registerType() -> ServiceTypeRegisterer<U>
	{
		return _container_builder->registerType<U>();
	}

	template<class U>
	inline auto ServiceRegisterer::registerFactory(U factory) -> ServiceFactoryRegisterer<U>
	{
		return _container_builder->registerFactory(factory);
	}

	inline Container ServiceRegisterer::build() const
	{
		return _container_builder->build();
	}

}