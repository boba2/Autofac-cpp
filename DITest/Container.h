#pragma once

#include <set>
#include <unordered_map>
#include "Details/ServiceInstanceRegisterer.h"
#include "Details/ServiceReferenceTypeConverter.h"
#include "Details/Error/Error.h"

namespace DI 
{

	class Container
	{
	public:
		explicit Container(std::set<std::shared_ptr<Details::ServiceResolver<>>> service_resolvers)
		{
			for (auto &resolver : service_resolvers)
				_service_resolvers[resolver->getServiceType()] = resolver;

			_service_resolvers[Details::TypeIndex<Container>()] = Details::ServiceInstanceRegisterer<Container>(this).getServiceResolver();
		}

		template<class T>
		T resolve()
		{
			if (!has<T>())
				throw Error::ServiceNotRegistered::fromType<typename Details::UnderlyingType<T>::Type>();


			return get<T>();
		}

	private:
		template<class T>
		bool has()
		{
			return _service_resolvers.find(Details::TypeIndex<T>()) != _service_resolvers.end();
		}

		template<class T>
		T get()
		{
			return Details::ServiceReferenceTypeConverter<T>::convert(std::dynamic_pointer_cast<Details::ServiceResolver<typename Details::UnderlyingType<T>::Type>>(_service_resolvers.at(Details::TypeIndex<T>()))->getService());
		}

	private:
		std::unordered_map<Details::TypeIndex<>, std::shared_ptr<Details::ServiceResolver<>>> _service_resolvers;
	};

}