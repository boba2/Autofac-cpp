#pragma once

#include <set>
#include "ServiceResolver.h"
#include "ServiceAliasRegisterer.h"

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

			virtual std::set<std::shared_ptr<ServiceResolver<>>> getServiceResolvers() const = 0;
		};

		template<class T, class S>
		class ServiceRegisterer : public ServiceRegisterer<>, public S
		{
		public:
			virtual std::set<std::shared_ptr<ServiceResolver<>>> getServiceResolvers() const override
			{
				auto main_resolver = getServiceResolver();

				std::set<std::shared_ptr<ServiceResolver<>>> result;

				auto alias_resolvers = getServiceAliasResolvers(main_resolver);
				if (alias_resolvers.empty())
					result.insert(main_resolver);
				else
					result.insert(begin(alias_resolvers), end(alias_resolvers));

				return result;
			}

		protected:
			virtual void registerAlias(std::shared_ptr<ServiceAliasRegisterer<>> alias_registerer) override
			{
				_alias_registerers.insert(alias_registerer);
			}

			virtual std::shared_ptr<ServiceResolver<>> getServiceResolver() const = 0;

		private:
			std::set<std::shared_ptr<ServiceResolver<>>> getServiceAliasResolvers(std::shared_ptr<ServiceResolver<>> main_resolver) const
			{
				std::set<std::shared_ptr<ServiceResolver<>>> result;

				for (auto& registerer : _alias_registerers)
					result.insert(registerer->getServiceAliasResolver(main_resolver));

				return result;
			}

		private:
			std::set<std::shared_ptr<ServiceAliasRegisterer<>>> _alias_registerers;
		};

	}
}