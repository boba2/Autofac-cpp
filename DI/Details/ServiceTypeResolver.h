#pragma once
#include "ServiceResolver.h"
#include "Error/ServiceNotResolvableAs.h"

namespace DI
{
	namespace Details
	{

		template<class T>
		class ServiceTypeResolver : public ServiceResolver<T>
		{
			using ServiceType = typename ServiceResolver<T>::ServiceType;
			using ServiceRefType = typename ServiceResolver<T>::ServiceRefType;
			using ServicePtrType = typename ServiceResolver<T>::ServicePtrType;
			using ServiceSharedPtrType = typename ServiceResolver<T>::ServiceSharedPtrType;
			using ServiceUniquePtrType = typename ServiceResolver<T>::ServiceUniquePtrType;

			virtual ServiceType getService() override
			{
				return T();
			}

			virtual ServiceRefType getServiceAsRef() override
			{
				throw Error::ServiceNotResolvableAs();
			}

			virtual ServicePtrType getServiceAsPtr() override
			{
				throw Error::ServiceNotResolvableAs();
			}

			virtual ServiceSharedPtrType getServiceAsSharedPtr() override
			{
				return std::make_shared<T>();
			}

			virtual ServiceUniquePtrType getServiceAsUniquePtr() override
			{
				return std::make_unique<T>();
			}
		};

	}
}