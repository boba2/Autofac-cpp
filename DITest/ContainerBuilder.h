#pragma once

#include "ServiceInstances.h"
#include "Container.h"

class ContainerBuilder
{
public:
	template<class T>
	void registerInstance(T &&instance)
	{
		_service_instances.add(std::forward<T>(instance));
	}

	std::unique_ptr<Container> build() const
	{
		return std::make_unique<Container>(ServiceResolvers(_service_instances.getServiceResolvers()));
	}

private:
	ServiceInstances _service_instances;
};
