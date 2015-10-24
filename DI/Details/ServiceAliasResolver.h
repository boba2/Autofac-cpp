#pragma once

#include "ServiceResolver.h"

namespace DI
{
	namespace Details
	{

		template<class T, class S>
		class ServiceAliasResolver : public ServiceResolver<T>
		{
			using ServiceType = typename ServiceResolver<T>::ServiceType;
			using ServiceRefType = typename ServiceResolver<T>::ServiceRefType;
			using ServicePtrType = typename ServiceResolver<T>::ServicePtrType;
			using ServiceSharedPtrType = typename ServiceResolver<T>::ServiceSharedPtrType;
			using ServiceUniquePtrType = typename ServiceResolver<T>::ServiceUniquePtrType;

		public:
			explicit ServiceAliasResolver(std::shared_ptr<ServiceResolver<S>> inner_resolver)
				: _inner_resolver(inner_resolver)
			{}

		private:
			virtual ServiceType getService(Container* container) override
			{
				return getService<T>(container);
			}

			virtual ServiceRefType getServiceAsRef(Container* container) override
			{
				return _inner_resolver->getServiceAsRef(container);
			}

			virtual ServicePtrType getServiceAsPtr(Container* container) override
			{
				return _inner_resolver->getServiceAsPtr(container);
			}

			virtual ServiceSharedPtrType getServiceAsSharedPtr(Container* container) override
			{
				return _inner_resolver->getServiceAsSharedPtr(container);
			}

			virtual ServiceUniquePtrType getServiceAsUniquePtr(Container* container) override
			{
				return _inner_resolver->getServiceAsUniquePtr(container);
			}

			template<class U>
			ServiceType getService(Container* container, std::enable_if_t<std::is_abstract<U>::value>* = nullptr)
			{
				return _inner_resolver->getServiceAsRef(container);
			}

			template<class U>
			ServiceType getService(Container* container, std::enable_if_t<!std::is_abstract<U>::value>* = nullptr)
			{
				return _inner_resolver->getService(container);
			}

			std::shared_ptr<ServiceResolver<S>> const _inner_resolver;
		};
	}
}