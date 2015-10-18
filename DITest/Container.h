#pragma once

#include <set>
#include <unordered_map>
#include "Error.h"
#include "ServiceInstanceRegisterer.h"
#include "ServiceReferenceTypeConverter.h"

namespace DI 
{

	class Container
	{
	public:
		explicit Container(std::set<std::shared_ptr<ServiceResolver<>>> service_resolvers)
		{
			for (auto &resolver : service_resolvers)
				_service_resolvers[resolver->getServiceType()] = resolver;

			_service_resolvers[TypeIndex<Container>()] = ServiceInstanceRegisterer<Container>(this).getServiceResolver();
		}

		template<class T>
		T resolve()
		{
			if (!has<T>())
				throw Error::ServiceNotRegistered::fromType<T>();


			return get<T>();
		}

	private:
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

}