#pragma once

#include "ServiceResolver.h"
#include "Error/ServiceNotResolvableAs.h"

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
			explicit ServiceInstanceResolver(std::shared_ptr<T> instance)
				: _instance(instance)
			{}

			virtual ServiceType getService() const override
			{
				return *_instance.get();
			}

			virtual ServiceRefType getServiceAsRef() const override
			{
				return *_instance.get();
			}

			virtual ServicePtrType getServiceAsPtr() const override
			{
				return _instance.get();
			}

			virtual ServiceSharedPtrType getServiceAsSharedPtr() const override
			{
				return _instance;
			}

			virtual ServiceUniquePtrType getServiceAsUniquePtr() const override
			{
				throw Error::ServiceNotResolvableAs();
			}

		private:
			std::shared_ptr<T> const _instance;
		};

	}
}