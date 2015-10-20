#pragma once

#include "ServiceResolver.h"
#include "Error/ServiceInstanceNotResolvableAs.h"

namespace DI
{
	namespace Details
	{

		template<class T>
		class ServiceInstanceResolver : public ServiceResolver<T>
		{
			using ServiceType = typename ServiceResolver<T>::ServiceType;
			using ServiceRefType = typename ServiceResolver<T>::ServiceRefType;
			using ServicePtrType = typename ServiceResolver<T>::ServicePtrType;
			using ServiceSharedPtrType = typename ServiceResolver<T>::ServiceSharedPtrType;
			using ServiceUniquePtrType = typename ServiceResolver<T>::ServiceUniquePtrType;

		public:
			ServiceInstanceResolver()
			{}

			explicit ServiceInstanceResolver(std::shared_ptr<T> instance)
				: _instance(instance)
			{}

			virtual ServiceType getService() const override
			{
				return *getServiceInstance().get();
			}

			virtual ServiceRefType getServiceAsRef() const override
			{
				return *getServiceInstance().get();
			}

			virtual ServicePtrType getServiceAsPtr() const override
			{
				return getServiceInstance().get();
			}

			virtual ServiceSharedPtrType getServiceAsSharedPtr() const override
			{
				return getServiceInstance();
			}

			virtual ServiceUniquePtrType getServiceAsUniquePtr() const override
			{
				throw Error::ServiceInstanceNotResolvableAs();
			}

		private:
			std::shared_ptr<T> getServiceInstance() const
			{
				if (!_instance)
					_instance = std::make_shared<T>();

				return _instance;
			}

		private:
			mutable std::shared_ptr<T> _instance;
		};

	}
}