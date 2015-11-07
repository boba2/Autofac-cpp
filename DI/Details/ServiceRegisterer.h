#pragma once

#include <vector>
#include <algorithm>
#include "ServiceResolver.h"
#include "ServiceAliasRegisterer.h"
#include "ServiceResolvers.h"

namespace DI
{
	namespace Details
	{

		template<class T = void, class S = void>
		class ServiceRegisterer;

		template<>
		class ServiceRegisterer<void, void>
		{
		public:
			virtual ~ServiceRegisterer() {}

			virtual ServiceResolvers getServiceResolvers() const = 0;
		};

		template<class T, class S>
		class ServiceRegisterer : public ServiceRegisterer<>, public S
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

		protected:
			virtual void registerAlias(std::shared_ptr<ServiceAliasRegisterer<>> alias_registerer) override
			{
				_alias_registerers.push_back(alias_registerer);
			}

			virtual std::shared_ptr<ServiceResolver<>> getServiceResolver() const = 0;

		private:
			auto getServiceAliasResolvers(std::shared_ptr<ServiceResolver<>> main_resolver) const
			{
				auto result = ServiceResolvers();

				std::for_each(
					begin(_alias_registerers), end(_alias_registerers),
					[&](auto registerer) { result.add(registerer->getServiceAliasResolver(main_resolver)); }
				);

				return result;
			}

		private:
			std::vector<std::shared_ptr<ServiceAliasRegisterer<>>> _alias_registerers;
		};

	}
}