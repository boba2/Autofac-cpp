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
		public:
			explicit ServiceInstanceResolver(std::shared_ptr<T> instance)
				: _instance(instance)
			{}

			virtual typename ServiceResolver<T>::ServiceType getService() const override
			{
				return *_instance.get();
			}

			virtual typename ServiceResolver<T>::ServiceRefType getServiceAsRef() const override
			{
				return *_instance.get();
			}

			virtual typename ServiceResolver<T>::ServicePtrType getServiceAsPtr() const override
			{
				return _instance.get();
			}

			virtual typename ServiceResolver<T>::ServiceSharedPtrType getServiceAsSharedPtr() const override
			{
				return _instance;
			}

			virtual typename ServiceResolver<T>::ServiceUniquePtrType getServiceAsUniquePtr() const override
			{
				throw Error::ServiceInstanceNotResolvableAs();
			}

		private:
			std::shared_ptr<T> const _instance;
		};

	}
}