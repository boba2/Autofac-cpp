#pragma once

#include "ServiceResolver.h"

namespace DI
{
	namespace Details
	{
		
		template<class T, class U>
		class ServiceAliasResolver : public ServiceResolver<T>
		{
		public:
			explicit ServiceAliasResolver(std::shared_ptr<ServiceResolver<>> inner_resolver)
				: _inner_resolver(std::dynamic_pointer_cast<ServiceResolver<U>>(inner_resolver))
			{}

			virtual std::shared_ptr<T> getService() const override
			{
				return std::dynamic_pointer_cast<T>(_inner_resolver->getService());
			}

			virtual TypeIndex<> getServiceType() const override
			{
				return TypeIndex<T>();
			}

		private:
			std::shared_ptr<ServiceResolver<U>> const _inner_resolver;
		};
	}
}