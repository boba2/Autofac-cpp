#pragma once

#include "ServiceAliasResolver.h"
#include "ServiceResolvers.h"

namespace DI
{
	namespace Details
	{

		template<class T = void, class S = void>
		class ServiceAliasRegisterer;

		template<>
		class ServiceAliasRegisterer<void, void>
		{
		public:
			virtual ~ServiceAliasRegisterer() {}

			virtual ServiceResolverData getServiceAliasResolver(ServiceResolverPtr<> main_resolver) const = 0;
		};

		template<class T, class S>
		class ServiceAliasRegisterer : public ServiceAliasRegisterer<>
		{
		public:
			static_assert(std::is_base_of<T, S>::value, "Alias should be a resolvable base class of the service class being registered");

			virtual ServiceResolverData getServiceAliasResolver(ServiceResolverPtr<> main_resolver) const override
			{
				return ServiceResolverData{TypeIndex::from<T>(), std::make_shared<ServiceAliasResolver<T, S>>(std::dynamic_pointer_cast<ServiceResolver<S>>(main_resolver))};
			}
		};

		template<class T>
		class ServiceAliasRegisterer<T, T> : public ServiceAliasRegisterer<>
		{
		public:
			virtual ServiceResolverData getServiceAliasResolver(ServiceResolverPtr<> main_resolver) const override
			{
				return ServiceResolverData{TypeIndex::from<T>(), main_resolver};
			}
		};

		template<class T = void, class S = void>
		using ServiceAliasRegistererPtr = std::shared_ptr<ServiceAliasRegisterer<T, S>>;

	}
}