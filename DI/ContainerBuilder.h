#pragma once

#include "Support/DIdecl.h"
#include "ServiceFactoryRegisterer.h"
#include "ServiceInstanceRegisterer.h"
#include "ServiceTypeRegisterer.h"
#include "Details/ServiceRegisterer.h"

namespace DI
{

	class Container;

	class DI_API ContainerBuilder
	{
	public:
		ContainerBuilder();
		ContainerBuilder(ContainerBuilder&& other);
		~ContainerBuilder();

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

#pragma warning(disable:4251)
		std::unique_ptr<Impl> _impl;
#pragma warning(default:4251)
	};

}

#include "ContainerBuilder.i"
#include "ServiceRegisterer.i"