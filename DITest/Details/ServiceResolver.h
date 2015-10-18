#pragma once

#include <memory>
#include "TypeIndex.h"

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

			virtual const T& getServiceAsConstRef() const = 0;
			virtual T& getServiceAsRef() const = 0;
			virtual T* getServiceAsPtr() const = 0;
			virtual std::shared_ptr<T> getServiceAsSharedPtr() const = 0;
			virtual std::unique_ptr<T> getServiceAsUniquePtr() const = 0;
		};

	}
}