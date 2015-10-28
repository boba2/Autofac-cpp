#pragma once

#include <vector>
#include <algorithm>
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

			virtual std::vector<std::shared_ptr<ServiceResolver<>>> getServiceResolvers() const = 0;
		};

		template<class T, class S>
		class ServiceRegisterer : public ServiceRegisterer<>, public S
		{
		public:
			virtual std::vector<std::shared_ptr<ServiceResolver<>>> getServiceResolvers() const override
			{
				auto main_resolver = getServiceResolver();
				auto alias_resolvers = getServiceAliasResolvers(main_resolver);

				if (alias_resolvers.empty())
					return std::vector<std::shared_ptr<ServiceResolver<>>>{main_resolver};

				return alias_resolvers;
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
				auto result = std::vector<std::shared_ptr<ServiceResolver<>>>(_alias_registerers.size());

				std::transform(
					begin(_alias_registerers), end(_alias_registerers), begin(result),
					[&main_resolver](auto& registerer) { return registerer->getServiceAliasResolver(main_resolver); }
				);

				return result;
			}

		private:
			std::vector<std::shared_ptr<ServiceAliasRegisterer<>>> _alias_registerers;
		};

	}
}