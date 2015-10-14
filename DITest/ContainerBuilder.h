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
		return std::make_unique<Container>(_service_instances);
	}

private:
	ServiceInstances _service_instances;
};
