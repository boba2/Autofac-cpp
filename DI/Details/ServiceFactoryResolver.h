#pragma once

#include <functional>
#include "ServiceResolver.h"
#include "Error/ServiceInstanceNotResolvableAs.h"

namespace DI
{
	namespace Details
	{

		template<class T>
		class ServiceFactoryResolver : public ServiceResolver<T>
		{
			using ServiceType = typename ServiceResolver<T>::ServiceType;
			using ServiceRefType = typename ServiceResolver<T>::ServiceRefType;
			using ServicePtrType = typename ServiceResolver<T>::ServicePtrType;
			using ServiceSharedPtrType = typename ServiceResolver<T>::ServiceSharedPtrType;
			using ServiceUniquePtrType = typename ServiceResolver<T>::ServiceUniquePtrType;

		public:
			explicit ServiceFactoryResolver(std::function<std::shared_ptr<T>()> factory)
				: _factory(factory)
			{}

			virtual ServiceType getService() const override
			{
				return *getServiceInstance().get();
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
				return getServiceInstance();
			}

			virtual ServiceUniquePtrType getServiceAsUniquePtr() const override
			{
				throw std::logic_error("Not implemented");
			}

		private:
			std::shared_ptr<T> getServiceInstance() const
			{
				return _factory();
			}

		private:
			std::function<std::shared_ptr<T>()> _factory;
		};

	}
}