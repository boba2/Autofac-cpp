#pragma once

#include "ServiceResolver.h"
#include "ServiceAliasRegisterer.h"
#include "ServiceResolvers.h"
#include "ServiceAliasRegisterers.h"

namespace DI
{
	namespace Details
	{

		template<class T = void>
		class ServiceRegisterer;

		template<>
		class ServiceRegisterer<void>
		{
		public:
			virtual ~ServiceRegisterer() {}

			virtual ServiceResolvers getServiceResolvers() const = 0;
		};

		template<class T>
		class ServiceRegisterer : public ServiceRegisterer<>
		{
		public:
			virtual ServiceResolvers getServiceResolvers() const override
			{
				auto main_resolver = getServiceResolver();
				auto alias_resolvers = getServiceAliasResolvers(main_resolver);

				if (!alias_resolvers.empty())
					return alias_resolvers;
				
				return ServiceResolvers{ main_resolver };
			}

			virtual void registerAlias(std::shared_ptr<ServiceAliasRegisterer<>> alias_registerer)
			{
				_alias_registerers.add(alias_registerer);
			}

			virtual std::shared_ptr<ServiceResolver<>> getServiceResolver() const = 0;

		private:
			auto getServiceAliasResolvers(std::shared_ptr<ServiceResolver<>> main_resolver) const
			{
				auto result = ServiceResolvers();
				_alias_registerers.forEach([&](auto& registerer) { result.add(registerer.getServiceAliasResolver(main_resolver)); });

				return result;
			}

		private:
			ServiceAliasRegisterers _alias_registerers;
		};

	}
}