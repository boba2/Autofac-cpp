#pragma once
#include "ServiceResolver.h"

namespace DI
{
	namespace Details
	{
		
		template<class T = void>
		class ServiceResolverGroup;

		template<>
		class ServiceResolverGroup<void>
		{
		public:
			virtual ~ServiceResolverGroup() {};
		};

		template<class T>
		class ServiceResolverGroup : public ServiceResolver<T>, public ServiceResolverGroup<>
		{
			using ServiceType = typename ServiceResolver<T>::ServiceType;
			using ServiceRefType = typename ServiceResolver<T>::ServiceRefType;
			using ServicePtrType = typename ServiceResolver<T>::ServicePtrType;
			using ServiceSharedPtrType = typename ServiceResolver<T>::ServiceSharedPtrType;
			using ServiceUniquePtrType = typename ServiceResolver<T>::ServiceUniquePtrType;

		public:
			virtual ServiceType getService(Container* container) override
			{
				return _resolver->getService(container);
			}

			virtual ServiceRefType getServiceAsRef(Container* container) override
			{
				return _resolver->getServiceAsRef(container);
			}

			virtual ServicePtrType getServiceAsPtr(Container* container) override
			{
				return _resolver->getServiceAsPtr(container);
			}

			virtual ServiceSharedPtrType getServiceAsSharedPtr(Container* container) override
			{
				return _resolver->getServiceAsSharedPtr(container);
			}

			virtual ServiceUniquePtrType getServiceAsUniquePtr(Container* container) override
			{
				return _resolver->getServiceAsUniquePtr(container);
			}

			ServiceResolverPtr<T> _resolver;
		};

	}
}