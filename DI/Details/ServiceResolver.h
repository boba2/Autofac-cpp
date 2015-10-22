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
			using ServiceType = std::conditional_t<std::is_abstract<T>::value, const T&, T>;
			using ServiceRefType = T&;
			using ServicePtrType = T*;
			using ServiceSharedPtrType = std::shared_ptr<T>;
			using ServiceUniquePtrType = std::unique_ptr<T>;

		public:
			virtual TypeIndex<> getServiceType() const override
			{
				return TypeIndex<T>();
			}

			virtual ServiceType getService() const = 0;
			virtual ServiceRefType getServiceAsRef() const = 0;
			virtual ServicePtrType getServiceAsPtr() const = 0;
			virtual ServiceSharedPtrType getServiceAsSharedPtr() const = 0;
			virtual ServiceUniquePtrType getServiceAsUniquePtr() const = 0;
		};

	}
}