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
			explicit ServiceAliasResolver(std::shared_ptr<ServiceResolver<>> inner_resolver)
				: _inner_resolver(std::dynamic_pointer_cast<ServiceResolver<S>>(inner_resolver))
			{}

			virtual ServiceType getService() const override
			{
				return _inner_resolver->getService();
			}

			virtual ServiceRefType getServiceAsRef() const override
			{
				return _inner_resolver->getServiceAsRef();
			}

			virtual ServicePtrType getServiceAsPtr() const override
			{
				return _inner_resolver->getServiceAsPtr();
			}

			virtual ServiceSharedPtrType getServiceAsSharedPtr() const override
			{
				return _inner_resolver->getServiceAsSharedPtr();
			}

			virtual ServiceUniquePtrType getServiceAsUniquePtr() const override
			{
				return std::move(_inner_resolver->getServiceAsUniquePtr());
			}

		private:
			std::shared_ptr<ServiceResolver<S>> const _inner_resolver;
		};
	}
}