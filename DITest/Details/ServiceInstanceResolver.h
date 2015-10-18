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

			virtual const T& getServiceAsConstRef() const override
			{
				return *_instance.get();
			}

			virtual T& getServiceAsRef() const override
			{
				return *_instance.get();
			}

			virtual T* getServiceAsPtr() const override
			{
				return _instance.get();
			}

			virtual std::shared_ptr<T> getServiceAsSharedPtr() const override
			{
				return _instance;
			}

			virtual std::unique_ptr<T> getServiceAsUniquePtr() const override
			{
				throw Error::ServiceInstanceNotResolvableAs();
			}

		private:
			std::shared_ptr<T> const _instance;
		};

	}
}