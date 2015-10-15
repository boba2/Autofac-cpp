#pragma once

#include "ServiceInstances.h"

class Container
{
public:
	explicit Container(const ServiceInstances &service_instances)
		: _service_instances(service_instances)
	{
		_service_instances.add(static_cast<Container *>(this));
	}

	template<class T>
	T resolve()
	{
		if (!_service_instances.has<T>())
			throw Error::ServiceNotRegistered::fromType<T>();


		return _service_instances.get<T>();
	}

private:
	ServiceInstances _service_instances;
};
