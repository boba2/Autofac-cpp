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
			using ServiceType = typename ServiceResolver<T>::ServiceType;
			using ServiceRefType = typename ServiceResolver<T>::ServiceRefType;
			using ServicePtrType = typename ServiceResolver<T>::ServicePtrType;
			using ServiceSharedPtrType = typename ServiceResolver<T>::ServiceSharedPtrType;
			using ServiceUniquePtrType = typename ServiceResolver<T>::ServiceUniquePtrType;

			template<class U>
			struct ServiceCreator
			{
				static U createInstance()
				{
					return U();
				}

				static std::unique_ptr<U> createUniquePtr()
				{
					return std::make_unique<U>();
				}

				static std::shared_ptr<U> createSharedPtr()
				{
					return std::make_shared<U>();
				}
			};

			template<class U>
			struct ServiceCreator<const U&>
			{
				static const U& createInstance()
				{
					throw Error::ServiceInstanceNotResolvableAs();
				}

				static std::unique_ptr<U> createUniquePtr()
				{
					throw Error::ServiceInstanceNotResolvableAs();
				}

				static std::shared_ptr<U> createSharedPtr()
				{
					throw Error::ServiceInstanceNotResolvableAs();
				}
			};

			virtual ServiceType getService() const override
			{
				return ServiceCreator<ServiceType>::createInstance();
			}

			virtual ServiceRefType getServiceAsRef() const override
			{
				throw Error::ServiceInstanceNotResolvableAs();
			}

			virtual ServicePtrType getServiceAsPtr() const override
			{
				throw Error::ServiceInstanceNotResolvableAs();
			}

			virtual ServiceSharedPtrType getServiceAsSharedPtr() const override
			{
				return ServiceCreator<ServiceType>::createSharedPtr();
			}

			virtual ServiceUniquePtrType getServiceAsUniquePtr() const override
			{
				return ServiceCreator<ServiceType>::createUniquePtr();
			}
		};

	}
}