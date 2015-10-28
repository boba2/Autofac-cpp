#pragma once

#include "ServiceFactoryRegisterer.h"
#include "ServiceInstanceRegisterer.h"
#include "ServiceTypeRegisterer.h"
#include "Details/FunctionTraits.h"

namespace DI
{

	class ContainerBuilder
	{
	public:
		ContainerBuilder();
		ContainerBuilder(const ContainerBuilder&) = delete;
		ContainerBuilder(ContainerBuilder&& other);
		~ContainerBuilder();

		ContainerBuilder& operator=(const ContainerBuilder&) = delete;
		ContainerBuilder& operator=(ContainerBuilder&& other);

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
		class Impl;

		std::unique_ptr<Impl> _impl;
	};

}

#include "ContainerBuilder.i"
#include "ServiceRegisterer.i"