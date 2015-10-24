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

			virtual ServiceType getService(Container* container) override
			{
				return _inner_resolver->getService(container);
			}

			virtual ServiceRefType getServiceAsRef(Container* container) override
			{
				return *getNewManagedInstance(container).get();
			}

			virtual ServicePtrType getServiceAsPtr(Container* container) override
			{
				return getNewManagedInstance(container).get();
			}

			virtual ServiceSharedPtrType getServiceAsSharedPtr(Container* container) override
			{
				return _inner_resolver->getServiceAsSharedPtr(container);
			}

			virtual ServiceUniquePtrType getServiceAsUniquePtr(Container* container) override
			{
				return _inner_resolver->getServiceAsUniquePtr(container);
			}

			ServiceSharedPtrType getNewManagedInstance(Container* container)
			{
				_managed_instances.push_back(getServiceAsSharedPtr(container));

				return _managed_instances.back();
			}

			std::shared_ptr<ServiceResolver<T>> const _inner_resolver;
			std::list<std::shared_ptr<T>> _managed_instances;
		};

	}
}