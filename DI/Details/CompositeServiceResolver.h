#pragma once

#include "ServiceResolver.h"

namespace DI
{
	namespace Details
	{
		template<class T = void>
		class CompositeServiceResolver;

		template<>
		class CompositeServiceResolver<void>
		{
		public:
			virtual ~CompositeServiceResolver() {}

			void addResolver(ServiceResolverPtr<> resolver)
			{
				_inner_resolver = resolver;
			}

			void merge(const CompositeServiceResolver<>& other)
			{
				_inner_resolver = other._inner_resolver;
			}

			ServiceResolverPtr<> _inner_resolver;
		};

		template<class T>
		class CompositeServiceResolver : public ServiceResolver<T>, public CompositeServiceResolver<>
		{
		private:
			using ServiceType = typename ServiceResolver<T>::ServiceType;
			using ServiceRefType = typename ServiceResolver<T>::ServiceRefType;
			using ServicePtrType = typename ServiceResolver<T>::ServicePtrType;
			using ServiceSharedPtrType = typename ServiceResolver<T>::ServiceSharedPtrType;
			using ServiceUniquePtrType = typename ServiceResolver<T>::ServiceUniquePtrType;

			virtual ServiceType getService(Container* container) override
			{
				return getSingleResolver()->getService(container);
			}

			virtual ServiceRefType getServiceAsRef(Container* container) override
			{
				return getSingleResolver()->getServiceAsRef(container);
			}

			virtual ServicePtrType getServiceAsPtr(Container* container) override
			{
				return getSingleResolver()->getServiceAsPtr(container);
			}

			virtual ServiceSharedPtrType getServiceAsSharedPtr(Container* container) override
			{
				return getSingleResolver()->getServiceAsSharedPtr(container);
			}

			virtual ServiceUniquePtrType getServiceAsUniquePtr(Container* container) override
			{
				return getSingleResolver()->getServiceAsUniquePtr(container);
			}

			auto getSingleResolver() const -> ServiceResolverPtr<T>
			{
				return std::dynamic_pointer_cast<ServiceResolver<T>>(_inner_resolver);
			}
		};

		template<class T = void>
		using CompositeServiceResolverPtr = std::shared_ptr<CompositeServiceResolver<T>>;
	}
}