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

			static Result convertFrom(ServiceResolver<T>& resolver)
			{	
				return resolver.getService();
			}
		};

		template<class T>
		struct ServiceReferenceTypeConverter<T&>
		{
			using Result = typename ServiceResolver<T>::ServiceRefType;

			static Result convertFrom(ServiceResolver<T>& resolver)
			{
				return resolver.getServiceAsRef();
			}
		};

		template<class T>
		struct ServiceReferenceTypeConverter<T*>
		{
			using Result = typename ServiceResolver<T>::ServicePtrType;

			static Result convertFrom(ServiceResolver<T>& resolver)
			{
				return resolver.getServiceAsPtr();
			}
		};

		template<class T>
		struct ServiceReferenceTypeConverter<std::shared_ptr<T>>
		{
			using Result = typename ServiceResolver<T>::ServiceSharedPtrType;

			static Result convertFrom(ServiceResolver<T>& resolver)
			{
				return resolver.getServiceAsSharedPtr();
			}
		};

		template<class T>
		struct ServiceReferenceTypeConverter<std::shared_ptr<T> &>
		{
			using Result = typename ServiceResolver<T>::ServiceUniquePtrType;

			static Result convertFrom(ServiceResolver<T>& resolver)
			{
				return resolver.getServiceAsSharedPtr();
			}
		};

		template<class T>
		struct ServiceReferenceTypeConverter<std::unique_ptr<T>>
		{
			using Result = std::unique_ptr<T>;

			static Result convertFrom(ServiceResolver<T>& resolver)
			{
				return resolver.getServiceAsUniquePtr();
			}
		};

	}
}
