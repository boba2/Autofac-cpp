#pragma once
#include "ServiceResolver.h"
#include "Error/ServiceInstanceNotResolvableAs.h"

namespace DI
{
	namespace Details
	{
		
		template<class T>
		class ServiceTypeResolver : public ServiceResolver<T>
		{
			virtual typename ServiceResolver<T>::ServiceType getService() const override
			{
				return T();
			}

			virtual typename ServiceResolver<T>::ServiceRefType getServiceAsRef() const override
			{
				throw Error::ServiceInstanceNotResolvableAs();
			}

			virtual typename ServiceResolver<T>::ServicePtrType getServiceAsPtr() const override
			{
				throw Error::ServiceInstanceNotResolvableAs();
			}

			virtual typename ServiceResolver<T>::ServiceSharedPtrType getServiceAsSharedPtr() const override
			{
				return std::make_shared<T>();
			}

			virtual typename ServiceResolver<T>::ServiceUniquePtrType getServiceAsUniquePtr() const override
			{
				return std::make_unique<T>();
			}
		};

	}
}