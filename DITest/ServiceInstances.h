#pragma once

#include <typeindex>
#include <unordered_map>
#include "ServiceInstanceReferenceTypeConverter.h"
#include "ServiceInstanceHolder.h"
#include "TypeIndex.h"

class ServiceInstances
{
public:
	template<class T>
	void add(T &&instance)
	{
		_service_instances[TypeIndex<T>()] = std::make_shared<ServiceInstanceHolder<typename UnderlyingType<T>::Type>>(std::forward<T>(instance));
	}

	std::unordered_map<std::type_index, std::shared_ptr<ServiceInstanceHolder<>>> getAll() const
	{
		return _service_instances;
	}

private:
	std::unordered_map<std::type_index, std::shared_ptr<ServiceInstanceHolder<>>> _service_instances;
};
