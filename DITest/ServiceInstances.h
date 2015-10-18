#pragma once

#include <set>
#include "ServiceInstanceRegisterer.h"

class ServiceInstances
{
public:
	template<class T>
	void add(T &&instance)
	{
		_service_instances.insert(std::make_shared<ServiceInstanceRegisterer<typename UnderlyingType<T>::Type>>(std::forward<T>(instance)));
	}

	std::set<std::shared_ptr<ServiceResolver<>>> getServiceResolvers() const
	{
		std::set<std::shared_ptr<ServiceResolver<>>> result;
		for (auto &instance : _service_instances)
			result.insert(instance->getServiceResolver());

		return result;
	}

private:
	std::set<std::shared_ptr<ServiceRegisterer<>>> _service_instances;
};
