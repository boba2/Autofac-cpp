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
			virtual ServiceType getService() override
			{
				return getService<T>();
			}

			virtual ServiceRefType getServiceAsRef() override
			{
				return _inner_resolver->getServiceAsRef();
			}

			virtual ServicePtrType getServiceAsPtr() override
			{
				return _inner_resolver->getServiceAsPtr();
			}

			virtual ServiceSharedPtrType getServiceAsSharedPtr() override
			{
				return _inner_resolver->getServiceAsSharedPtr();
			}

			virtual ServiceUniquePtrType getServiceAsUniquePtr() override
			{
				return std::move(_inner_resolver->getServiceAsUniquePtr());
			}

			template<class U>
			ServiceType getService(std::enable_if_t<std::is_abstract<U>::value>* = 0)
			{
				return _inner_resolver->getServiceAsRef();
			}

			template<class U>
			ServiceType getService(std::enable_if_t<!std::is_abstract<U>::value>* = 0)
			{
				return _inner_resolver->getService();
			}

			std::shared_ptr<ServiceResolver<S>> const _inner_resolver;
		};
	}
}