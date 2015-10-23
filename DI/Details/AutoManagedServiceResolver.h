#pragma once

#include <list>
#include "Details/ServiceResolver.h"
#include "Error/ServiceNotResolvableAs.h"

namespace DI
{
	namespace Details
	{

		template<class T>
		class AutoManagedServiceResolver : public ServiceResolver<T>
		{
			using ServiceType = typename ServiceResolver<T>::ServiceType;
			using ServiceRefType = typename ServiceResolver<T>::ServiceRefType;
			using ServicePtrType = typename ServiceResolver<T>::ServicePtrType;
			using ServiceSharedPtrType = typename ServiceResolver<T>::ServiceSharedPtrType;
			using ServiceUniquePtrType = typename ServiceResolver<T>::ServiceUniquePtrType;

		public:
			explicit AutoManagedServiceResolver(std::shared_ptr<ServiceResolver<T>> inner_resolver)
				: _inner_resolver(inner_resolver)
			{}

			virtual ServiceType getService() override
			{
				return _inner_resolver->getService();
			}

			virtual ServiceRefType getServiceAsRef() override
			{
				return *getNewManagedInstance().get();
			}

			virtual ServicePtrType getServiceAsPtr() override
			{
				return getNewManagedInstance().get();
			}

			virtual ServiceSharedPtrType getServiceAsSharedPtr() override
			{
				return _inner_resolver->getServiceAsSharedPtr();
			}

			virtual ServiceUniquePtrType getServiceAsUniquePtr() override
			{
				return _inner_resolver->getServiceAsUniquePtr();
			}

			ServiceSharedPtrType getNewManagedInstance()
			{
				_managed_instances.push_back(getServiceAsSharedPtr());

				return _managed_instances.back();
			}

			std::shared_ptr<ServiceResolver<T>> const _inner_resolver;
			std::list<std::shared_ptr<T>> _managed_instances;
		};

	}
}