#pragma once

#include "ServiceResolver.h"

namespace DI
{
	namespace Details
	{
		
		template<class T, class S>
		class ServiceAliasResolver : public ServiceResolver<T>
		{
		public:
			explicit ServiceAliasResolver(std::shared_ptr<ServiceResolver<>> inner_resolver)
				: _inner_resolver(std::dynamic_pointer_cast<ServiceResolver<S>>(inner_resolver))
			{}

			virtual typename ServiceResolver<T>::ServiceType getService() const override
			{
				return _inner_resolver->getService();
			}

			virtual typename ServiceResolver<T>::ServiceRefType getServiceAsRef() const override
			{
				return _inner_resolver->getServiceAsRef();
			}

			virtual typename ServiceResolver<T>::ServicePtrType getServiceAsPtr() const override
			{
				return _inner_resolver->getServiceAsPtr();
			}

			virtual typename ServiceResolver<T>::ServiceSharedPtrType getServiceAsSharedPtr() const override
			{
				return _inner_resolver->getServiceAsSharedPtr();
			}

			virtual typename ServiceResolver<T>::ServiceUniquePtrType getServiceAsUniquePtr() const override
			{
				return std::move(_inner_resolver->getServiceAsUniquePtr());
			}

		private:
			std::shared_ptr<ServiceResolver<S>> const _inner_resolver;
		};
	}
}