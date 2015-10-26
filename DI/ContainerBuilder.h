#pragma once

#include "Container.h"
#include "ServiceFactoryRegisterer.h"
#include "ServiceInstanceRegisterer.h"
#include "ServiceTypeRegisterer.h"
#include "Details/ServiceRegisterer.h"
#include "Details/FunctionTraits.h"

namespace DI
{

	class ContainerBuilder
	{
	public:
		template<class T>
		auto registerInstance(T &&instance) -> ServiceInstanceRegisterer<typename Details::UnderlyingType<T>::Type>;

		template<class T>
		auto registerType() -> ServiceTypeRegisterer<T>;

		template<class T>
		auto registerFactory(T factory) -> ServiceFactoryRegisterer<typename Details::UnderlyingType<typename Details::FunctionResultType<T>::Type>::Type>;

		Container build() const;

	private:
		template<class T, class S, class... U>
		auto createRegisterer(U&&... param);

		auto getServiceResolvers() const;

	private:
		std::set<std::shared_ptr<Details::ServiceRegisterer<>>> _service_registerers;
	};

}

#include "ContainerBuilder.i"
#include "ServiceRegisterer.i"