#pragma once

#include "ServiceInstances.h"
#include <algorithm>

class ServiceResolvers
{
public:
	explicit ServiceResolvers(const ServiceInstances service_instances)
	{
		for (auto instance : service_instances.getAll())
			_service_resolvers[instance.first] = std::dynamic_pointer_cast<ServiceResolver<>>(instance.second);
	}

	template<class T>
	void add(T &&instance)
	{
		_service_resolvers[TypeIndex<T>()] = std::make_shared<ServiceInstanceHolder<typename UnderlyingType<T>::Type>>(std::forward<T>(instance));
	}

	template<class T>
	bool has()
	{
		return _service_resolvers.find(TypeIndex<T>()) != _service_resolvers.end();
	}

	template<class T>
	T get()
	{
		return ServiceInstanceReferenceTypeConverter<T>::convert(std::dynamic_pointer_cast<ServiceResolver<typename UnderlyingType<T>::Type>>(_service_resolvers.at(TypeIndex<T>()))->get());
	}

private:
	std::unordered_map<std::type_index, std::shared_ptr<ServiceResolver<>>> _service_resolvers;
};
