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
			using ServiceResolver<T>::ServiceType;
			using ServiceResolver<T>::ServiceRefType;
			using ServiceResolver<T>::ServicePtrType;
			using ServiceResolver<T>::ServiceSharedPtrType;
			using ServiceResolver<T>::ServiceUniquePtrType;

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
				throw Error::ServiceInstanceNotResolvableAs();
			}

		private:
			std::shared_ptr<T> const _instance;
		};

	}
}