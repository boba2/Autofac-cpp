#pragma once

#include "Support/DIdecl.h"

namespace DI
{
	class Container;
	class ContainerBuilder;

	template<class T>
	class ServiceTypeRegisterer;

	template<class T>
	class ServiceInstanceRegisterer;

	template<class T>
	class ServiceFactoryRegisterer;

	class DI_API ServiceRegisterer
	{
	public:
		explicit ServiceRegisterer(ContainerBuilder& container_builder)
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
		ContainerBuilder& _container_builder;
	};

}