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

			virtual const T& getServiceAsConstRef() const override
			{
				return _inner_resolver->getServiceAsConstRef();
			}

			virtual T& getServiceAsRef() const override
			{
				return _inner_resolver->getServiceAsRef();
			}

			virtual T* getServiceAsPtr() const override
			{
				return _inner_resolver->getServiceAsPtr();
			}

			virtual std::shared_ptr<T> getServiceAsSharedPtr() const override
			{
				return _inner_resolver->getServiceAsSharedPtr();
			}

			virtual std::unique_ptr<T> getServiceAsUniquePtr() const override
			{
				return std::move(_inner_resolver->getServiceAsUniquePtr());
			}

		private:
			std::shared_ptr<ServiceResolver<S>> const _inner_resolver;
		};
	}
}