#pragma once

#include "ServiceResolver.h"
#include "../Error/ServiceNotResolvableAs.h"

namespace DI
{
	namespace Details
	{

		template<class T>
		class SingletonServiceResolver : public ServiceResolver<T>
		{
			using ServiceType = typename ServiceResolver<T>::ServiceType;
			using ServiceRefType = typename ServiceResolver<T>::ServiceRefType;
			using ServicePtrType = typename ServiceResolver<T>::ServicePtrType;
			using ServiceSharedPtrType = typename ServiceResolver<T>::ServiceSharedPtrType;
			using ServiceUniquePtrType = typename ServiceResolver<T>::ServiceUniquePtrType;

		public:
			explicit SingletonServiceResolver(std::shared_ptr<ServiceResolver<T>> inner_resolver)
				: _inner_resolver(inner_resolver)
			{}

		private:
			virtual ServiceType getService(Container* container) override
			{
				return *getServiceInstance(container).get();
			}

			virtual ServiceRefType getServiceAsRef(Container* container) override
			{
				return *getServiceInstance(container).get();
			}

			virtual ServicePtrType getServiceAsPtr(Container* container) override
			{
				return getServiceInstance(container).get();
			}

			virtual ServiceSharedPtrType getServiceAsSharedPtr(Container* container) override
			{
				return getServiceInstance(container);
			}

			virtual ServiceUniquePtrType getServiceAsUniquePtr(Container*) override
			{
				throw Error::ServiceNotResolvableAs();
			}

			ServiceSharedPtrType getServiceInstance(Container* container)
			{
				if (!_instance)
					_instance = _inner_resolver->getServiceAsSharedPtr(container);

				return _instance;
			}

			std::shared_ptr<ServiceResolver<T>> const _inner_resolver;
			ServiceSharedPtrType _instance;
		};

	}
}