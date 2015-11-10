#pragma once

#include <memory>

namespace DI
{
	class Container;

	namespace Details
	{

		template<class T = void>
		class ServiceResolver;

		template<>
		class ServiceResolver<void>
		{
		public:
			virtual ~ServiceResolver() {}
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

			virtual ServiceType getService(Container* container) = 0;
			virtual ServiceRefType getServiceAsRef(Container* container) = 0;
			virtual ServicePtrType getServiceAsPtr(Container* container) = 0;
			virtual ServiceSharedPtrType getServiceAsSharedPtr(Container* container) = 0;
			virtual ServiceUniquePtrType getServiceAsUniquePtr(Container* container) = 0;
		};

		template<class T = void>
		using ServiceResolverPtr = std::shared_ptr<ServiceResolver<T>>;

	}
}