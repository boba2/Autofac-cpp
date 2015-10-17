#pragma once

#include "ServiceResolvers.h"
#include "Error.h"

class Container
{
public:
	explicit Container(const ServiceResolvers &service_resolvers)
		: _service_resolvers(service_resolvers)
	{
		_service_resolvers.add(static_cast<Container *>(this));
	}

	template<class T>
	T resolve()
	{
		if (!_service_resolvers.has<T>())
			throw Error::ServiceNotRegistered::fromType<T>();


		return _service_resolvers.get<T>();
	}

private:
	ServiceResolvers _service_resolvers;
};
