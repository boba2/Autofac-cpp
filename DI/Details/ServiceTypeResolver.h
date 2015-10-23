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
				return getService<T>();
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
				return getServiceAsSharedPtr<T>();
			}

			virtual ServiceUniquePtrType getServiceAsUniquePtr() override
			{
				return getServiceAsUniquePtr<T>();
			}

			template<class U>
			ServiceType getService(std::enable_if_t<std::is_abstract<U>::value>* = 0)
			{
				throw Error::ServiceNotResolvableAs();
			}

			template<class U>
			ServiceType getService(std::enable_if_t<!std::is_abstract<U>::value>* = 0)
			{
				return U();
			}

			template<class U>
			ServiceSharedPtrType getServiceAsSharedPtr(std::enable_if_t<std::is_abstract<U>::value>* = 0)
			{
				throw Error::ServiceNotResolvableAs();
			}

			template<class U>
			ServiceSharedPtrType getServiceAsSharedPtr(std::enable_if_t<!std::is_abstract<U>::value>* = 0)
			{
				return std::make_shared<T>();
			}

			template<class U>
			ServiceUniquePtrType getServiceAsUniquePtr(std::enable_if_t<std::is_abstract<U>::value>* = 0)
			{
				throw Error::ServiceNotResolvableAs();
			}

			template<class U>
			ServiceUniquePtrType getServiceAsUniquePtr(std::enable_if_t<!std::is_abstract<U>::value>* = 0)
			{
				return std::make_unique<T>();
			}
		};

	}
}