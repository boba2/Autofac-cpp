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

	template<class T>
	bool has()
	{
		return _service_instances.find(TypeIndex<T>()) != _service_instances.end();
	}

	template<class T>
	T get()
	{
		return ServiceInstanceReferenceTypeConverter<T>::convert(std::dynamic_pointer_cast<ServiceInstanceHolder<typename UnderlyingType<T>::Type>>(_service_instances.at(TypeIndex<T>()))->get());
	}

private:
	std::unordered_map<std::type_index, std::shared_ptr<ServiceInstanceHolder<>>> _service_instances;
};
