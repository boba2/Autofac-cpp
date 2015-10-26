#pragma once

#include "Container.h"
#include "Details/ServiceRegisterer.h"

namespace DI
{

	class ContainerBuilder
	{
	public:
		template<class T>
		auto registerInstance(T &&instance);

		template<class T>
		auto registerType();

		template<class T>
		auto registerFactory(T factory);

		Container build() const;

	private:
		template<class T, class... U>
		auto createRegisterer(U&&... param);

		auto getServiceResolvers() const;

	private:
		std::set<std::shared_ptr<Details::ServiceRegisterer<>>> _service_registerers;
	};

}

#include "ContainerBuilder.i"