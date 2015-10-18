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

			virtual std::shared_ptr<T> getService() const override
			{
				return std::static_pointer_cast<T>(_inner_resolver->getService());
			}

		private:
			std::shared_ptr<ServiceResolver<S>> const _inner_resolver;
		};
	}
}