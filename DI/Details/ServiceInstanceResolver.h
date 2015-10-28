#pragma once

#include "ServiceResolver.h"
#include "../Error/ServiceNotResolvableAs.h"

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

		private:
			virtual ServiceType getService(Container*) override
			{
				return *_instance.get();
			}

			virtual ServiceRefType getServiceAsRef(Container*) override
			{
				return *_instance.get();
			}

			virtual ServicePtrType getServiceAsPtr(Container*) override
			{
				return _instance.get();
			}

			virtual ServiceSharedPtrType getServiceAsSharedPtr(Container*) override
			{
				return _instance;
			}

			virtual ServiceUniquePtrType getServiceAsUniquePtr(Container*) override
			{
				throw Error::ServiceNotResolvableAs();
			}

			std::shared_ptr<T> const _instance;
		};

	}
}