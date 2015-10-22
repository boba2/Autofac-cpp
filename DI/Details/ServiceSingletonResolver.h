#pragma once

#include "ServiceResolver.h"
#include "Error/ServiceNotResolvableAs.h"

namespace DI
{
	namespace Details
	{

		template<class T>
		class ServiceSingletonResolver : public ServiceResolver<T>
		{
			using ServiceType = typename ServiceResolver<T>::ServiceType;
			using ServiceRefType = typename ServiceResolver<T>::ServiceRefType;
			using ServicePtrType = typename ServiceResolver<T>::ServicePtrType;
			using ServiceSharedPtrType = typename ServiceResolver<T>::ServiceSharedPtrType;
			using ServiceUniquePtrType = typename ServiceResolver<T>::ServiceUniquePtrType;

		public:
			explicit ServiceSingletonResolver(std::shared_ptr<ServiceResolver<T>> inner_resolver)
				: _inner_resolver(inner_resolver)
			{}

			virtual ServiceType getService() override
			{
				return *getServiceInstance().get();
			}

			virtual ServiceRefType getServiceAsRef() override
			{
				return *getServiceInstance().get();
			}

			virtual ServicePtrType getServiceAsPtr() override
			{
				return getServiceInstance().get();
			}

			virtual ServiceSharedPtrType getServiceAsSharedPtr() override
			{
				return getServiceInstance();
			}

			virtual ServiceUniquePtrType getServiceAsUniquePtr() override
			{
				throw Error::ServiceNotResolvableAs();
			}

		private:
			ServiceSharedPtrType getServiceInstance()
			{
				if (!_instance)
					_instance = _inner_resolver->getServiceAsSharedPtr();

				return _instance;
			}

		private:
			std::shared_ptr<ServiceResolver<T>> const _inner_resolver;
			ServiceSharedPtrType _instance;
		};

	}
}