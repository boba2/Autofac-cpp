#pragma once

#include <set>
#include <unordered_map>
#include "../Container.h"
#include "../Error/ServiceNotRegistered.h"
#include "ServiceAliasResolver.h"

namespace DI
{
	namespace Details
	{
		
		class Container : public DI::Container
		{
		public:
			explicit Container(const std::set<std::shared_ptr<ServiceResolver<>>>& service_resolvers)
			{
				registerResolvers(service_resolvers);
				registerSelf();
			}

		protected:
			ServiceResolver<> &getResolver(const TypeIndex<>& type_index) const override
			{
				auto resolver_it = _service_resolvers.find(type_index);
				if (resolver_it == end(_service_resolvers))
					throw Error::ServiceNotRegistered(type_index.getTypeName());

				return *resolver_it->second;
			}

		private:
			void registerResolvers(const std::set<std::shared_ptr<ServiceResolver<>>>& service_resolvers)
			{
				for (auto &resolver : service_resolvers)
					_service_resolvers[resolver->getServiceType()] = resolver;
			}

			void registerSelf()
			{
				auto registerer = ServiceInstanceRegisterer<Container>(this);
				registerer.as<DI::Container>();

				registerResolvers(registerer.getServiceResolvers());
			}

		private:
			std::unordered_map<TypeIndex<>, std::shared_ptr<ServiceResolver<>>> _service_resolvers;
		};

	}
}