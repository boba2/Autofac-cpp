#pragma once

#include "ServiceFactoryRegisterer.h"
#include "ServiceInstanceRegisterer.h"
#include "ServiceTypeRegisterer.h"
#include "Details/ServiceRegisterer.h"

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
		auto registerInstance(T &&instance) -> ServiceInstanceRegisterer<T>;

		template<class T>
		auto registerType() -> ServiceTypeRegisterer<T>;

		template<class T>
		auto registerFactory(T factory) -> ServiceFactoryRegisterer<T>;

		Container build() const;

	private:
		template<class T, class S, class... U>
		auto createRegisterer(U&&... param);

		void addRegisterer(std::shared_ptr<Details::ServiceRegisterer<>> registerer);

	private:
		class Impl;

		std::unique_ptr<Impl> _impl;
	};

}

#include "ContainerBuilder.i"
#include "ServiceRegisterer.i"