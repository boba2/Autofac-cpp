#pragma once
#include "ServiceResolver.h"
#include "../Error/ServiceNotResolvableAs.h"
#include "ServiceCreator.h"

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

			virtual ServiceType getService(Container* container) override
			{
				return getService<T>(container);
			}

			virtual ServiceRefType getServiceAsRef(Container*) override
			{
				throw Error::ServiceNotResolvableAs();
			}

			virtual ServicePtrType getServiceAsPtr(Container*) override
			{
				throw Error::ServiceNotResolvableAs();
			}

			virtual ServiceSharedPtrType getServiceAsSharedPtr(Container* container) override
			{
				return getServiceAsSharedPtr<T>(container);
			}

			virtual ServiceUniquePtrType getServiceAsUniquePtr(Container* container) override
			{
				return getServiceAsUniquePtr<T>(container);
			}

			template<class U>
			ServiceType getService(Container* container, std::enable_if_t<!std::is_abstract<U>::value>* = nullptr)
			{
				return ServiceCreator<T>::createService(container);
			}

			template<class U>
			ServiceSharedPtrType getServiceAsSharedPtr(Container* container, std::enable_if_t<!std::is_abstract<U>::value>* = nullptr)
			{
				return ServiceCreator<T>::template createService<ServiceSharedPtrType>(container);
			}

			template<class U>
			ServiceUniquePtrType getServiceAsUniquePtr(Container* container, std::enable_if_t<!std::is_abstract<U>::value>* = nullptr)
			{
				return ServiceCreator<T>::template createService<ServiceUniquePtrType>(container);
			}
		};

	}
}