#pragma once

#include <memory>
#include <set>
#include "ServiceResolver.h"
#include "../ServiceRegisterer.h"

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

			virtual std::set<std::shared_ptr<ServiceResolver<>>> getServiceResolvers() const = 0;
		};

		template<class T>
		class ServiceRegisterer : public ServiceRegisterer<>, public DI::ServiceRegisterer<T>
		{
		protected:
			virtual void registerAlias(std::shared_ptr<ServiceAliasRegisterer<>> alias_registerer) override
			{
				_alias_registerers.insert(alias_registerer);
			}

		public:
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