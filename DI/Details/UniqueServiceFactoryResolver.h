#pragma once

#include <functional>
#include "ServiceResolver.h"
#include "Error/ServiceInstanceNotResolvableAs.h"

namespace DI
{
	namespace Details
	{

		template<class T>
		class UniqueServiceFactoryResolver : public ServiceResolver<T>
		{
			using ServiceType = typename ServiceResolver<T>::ServiceType;
			using ServiceRefType = typename ServiceResolver<T>::ServiceRefType;
			using ServicePtrType = typename ServiceResolver<T>::ServicePtrType;
			using ServiceSharedPtrType = typename ServiceResolver<T>::ServiceSharedPtrType;
			using ServiceUniquePtrType = typename ServiceResolver<T>::ServiceUniquePtrType;

		public:
			explicit UniqueServiceFactoryResolver(std::function<std::unique_ptr<T>()> factory)
				: _factory(factory)
			{}

			virtual ServiceType getService() const override
			{
				return *_factory().get();
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
				return _factory();
			}

			virtual ServiceUniquePtrType getServiceAsUniquePtr() const override
			{
				return _factory();
			}

		private:
			std::function<std::unique_ptr<T>()> _factory;
		};

	}
}