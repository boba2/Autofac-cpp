#pragma once

#include <memory>
#include "TypeIndex.h"
#include "../Error/ServiceInstanceNotResolvableAsUniquePtr.h"

namespace DI
{
	namespace Details
	{

		template<class T = void>
		class ServiceResolver;

		template<>
		class ServiceResolver<void>
		{
		public:
			virtual ~ServiceResolver() {}

			virtual TypeIndex<> getServiceType() const = 0;
		};

		template<class T>
		class ServiceResolver : public ServiceResolver<>
		{
		public:
			virtual TypeIndex<> getServiceType() const override
			{
				return TypeIndex<T>();
			}

			virtual const T& getServiceAsConstRef() const
			{
				return *getServiceAsSharedPtr().get();
			}

			virtual T& getServiceAsRef() const
			{
				return *getServiceAsSharedPtr().get();
			}

			virtual T* getServiceAsPtr() const
			{
				return getServiceAsSharedPtr().get();
			}

			virtual std::shared_ptr<T> getServiceAsSharedPtr() const
			{
				return std::shared_ptr<T>(std::move(getServiceAsUniquePtr()));
			}

			virtual std::unique_ptr<T> getServiceAsUniquePtr() const
			{
				throw std::logic_error("Not implemented");
			}
		};

	}
}