#pragma once
#include "ServiceResolver.h"
#include "Error/ServiceInstanceNotResolvableAs.h"

namespace DI
{
	namespace Details
	{
		
		template<class T>
		class ServiceTypeResolver : public ServiceResolver<T>
		{
			virtual const T& getServiceAsConstRef() const override
			{
				throw Error::ServiceInstanceNotResolvableAs();
			}

			virtual T& getServiceAsRef() const override
			{
				throw Error::ServiceInstanceNotResolvableAs();
			}

			virtual T* getServiceAsPtr() const override
			{
				throw Error::ServiceInstanceNotResolvableAs();
			}

			virtual std::shared_ptr<T> getServiceAsSharedPtr() const override
			{
				return std::make_shared<T>();
			}

			virtual std::unique_ptr<T> getServiceAsUniquePtr() const override
			{
				return std::make_unique<T>();
			}
		};

	}
}