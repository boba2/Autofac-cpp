#pragma once

#include "ServiceResolver.h"

namespace DI
{
	namespace Details
	{

		template<class T>
		struct ServiceReferenceTypeConverter
		{
			using Result = typename ServiceResolver<T>::ServiceType;

			static Result convertFrom(ServiceResolver<T>& resolver, Container* container)
			{	
				return resolver.getService(container);
			}
		};

		template<class T>
		struct ServiceReferenceTypeConverter<T&>
		{
			using Result = typename ServiceResolver<T>::ServiceRefType;

			static Result convertFrom(ServiceResolver<T>& resolver, Container* container)
			{
				return resolver.getServiceAsRef(container);
			}
		};

		template<class T>
		struct ServiceReferenceTypeConverter<T*>
		{
			using Result = typename ServiceResolver<T>::ServicePtrType;

			static Result convertFrom(ServiceResolver<T>& resolver, Container* container)
			{
				return resolver.getServiceAsPtr(container);
			}
		};

		template<class T>
		struct ServiceReferenceTypeConverter<std::shared_ptr<T>>
		{
			using Result = typename ServiceResolver<T>::ServiceSharedPtrType;

			static Result convertFrom(ServiceResolver<T>& resolver, Container* container)
			{
				return resolver.getServiceAsSharedPtr(container);
			}
		};

		template<class T>
		struct ServiceReferenceTypeConverter<std::unique_ptr<T>>
		{
			using Result = typename ServiceResolver<T>::ServiceUniquePtrType;

			static Result convertFrom(ServiceResolver<T>& resolver, Container* container)
			{
				return resolver.getServiceAsUniquePtr(container);
			}
		};

	}
}
