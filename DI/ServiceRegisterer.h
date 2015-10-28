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

	template<class T>
	class ServiceRegisterer
	{
	public:
		explicit ServiceRegisterer(std::shared_ptr<T> impl, ContainerBuilder* container_builder)
			: _impl(impl), _container_builder(container_builder)
		{}

		template<class U>
		auto registerInstance(U &&instance) -> ServiceInstanceRegisterer<typename Details::UnderlyingType<U>::Type>;

		template<class U>
		auto registerType() -> ServiceTypeRegisterer<U>;

		template<class U>
		auto registerFactory(U factory) -> ServiceFactoryRegisterer<typename Details::UnderlyingType<typename Details::FunctionResultType<U>::Type>::Type>;

		Container build() const;

	protected:
		std::shared_ptr<T> const _impl;

	private:
		ContainerBuilder* const _container_builder;
	};

}