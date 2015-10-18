#pragma once

#include <set>
#include <unordered_map>
#include "ServiceResolver.h"
#include "ServiceReferenceTypeConverter.h"

class ServiceResolvers
{
public:
	explicit ServiceResolvers(std::set<std::shared_ptr<ServiceResolver<>>> service_resolvers)
	{
		for (auto &resolver : service_resolvers)
			_service_resolvers[resolver->getServiceType()] = resolver;
	}

	template<class T>
	void add(T &&instance)
	{
		_service_resolvers[TypeIndex<T>()] = ServiceInstanceRegisterer<typename UnderlyingType<T>::Type>(instance).getServiceResolver();
	}

	template<class T>
	bool has()
	{
		return _service_resolvers.find(TypeIndex<T>()) != _service_resolvers.end();
	}

	template<class T>
	T get()
	{
		return ServiceReferenceTypeConverter<T>::convert(std::dynamic_pointer_cast<ServiceResolver<typename UnderlyingType<T>::Type>>(_service_resolvers.at(TypeIndex<T>()))->getService());
	}

private:
	std::unordered_map<TypeIndex<>, std::shared_ptr<ServiceResolver<>>> _service_resolvers;
};
