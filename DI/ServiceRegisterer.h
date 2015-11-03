#pragma once

#include "Details/FunctionTraits.h"

namespace DI
{
	class ContainerBuilder;

	template<class T>
	class ServiceTypeRegisterer;

	template<class T>
	class ServiceInstanceRegisterer;

	template<class T>
	class ServiceFactoryRegisterer;

	class ServiceRegisterer
	{
	public:
		explicit ServiceRegisterer(ContainerBuilder* container_builder)
			: _container_builder(container_builder)
		{}

		template<class U>
		auto registerInstance(U &&instance) -> ServiceInstanceRegisterer<U>;

		template<class U>
		auto registerType() -> ServiceTypeRegisterer<U>;

		template<class U>
		auto registerFactory(U factory) -> ServiceFactoryRegisterer<U>;

		Container build() const;

	private:
		ContainerBuilder* const _container_builder;
	};

}