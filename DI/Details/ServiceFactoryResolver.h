#pragma once

#include <functional>
#include "Details/ServiceResolver.h"
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
			explicit ServiceFactoryResolver(std::function<std::shared_ptr<T>()> shared_service_factory, std::function<std::unique_ptr<T>()> unique_service_factory)
				: _shared_service_factory(shared_service_factory),
				_unique_service_factory(unique_service_factory)
			{}

			virtual ServiceType getService() const override
			{
				return *_shared_service_factory().get();
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
				return _shared_service_factory();
			}

			virtual ServiceUniquePtrType getServiceAsUniquePtr() const override
			{
				if (!_unique_service_factory)
					throw Error::ServiceInstanceNotResolvableAs();

				return _unique_service_factory();
			}

		private:
			std::function<std::shared_ptr<T>()> _shared_service_factory;
			std::function<std::unique_ptr<T>()> _unique_service_factory;
		};

	}
}