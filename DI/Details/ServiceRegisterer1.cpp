#include "ServiceRegisterer.h"
#include <vector>
#include <algorithm>

namespace DI
{
	namespace Details
	{
		
		class ServiceRegisterer::Impl
		{
		public:
			void registerAlias(ServiceAliasRegistererPtr<> alias_registerer)
			{
				_alias_registerers.push_back(alias_registerer);
			}

			ServiceResolvers getServiceResolvers(ServiceResolverCreatorPtr main_resolver) const
			{
				if (_alias_registerers.empty())
				{
					auto result = ServiceResolvers();
					result.add(main_resolver);

					return result;
				}

				return getServiceAliasResolvers(main_resolver->getServiceResolver());
			}

		private:
			ServiceResolvers getServiceAliasResolvers(ServiceResolverPtr<> main_resolver) const
			{
				auto result = ServiceResolvers();

				std::for_each(
					begin(_alias_registerers), end(_alias_registerers),
					[&](auto& registerer) { result.add(registerer->getServiceAliasResolver(main_resolver)); }
				);

				return result;
			}

			std::vector<ServiceAliasRegistererPtr<>> _alias_registerers;
		};

		ServiceRegisterer::ServiceRegisterer()
			: _impl(std::make_unique<Impl>())
		{}

		ServiceRegisterer::ServiceRegisterer(ServiceRegisterer&& other)
			: _impl(move(other._impl))
		{}

		ServiceRegisterer::~ServiceRegisterer()
		{}

		void ServiceRegisterer::registerAlias(ServiceAliasRegistererPtr<> alias_registerer)
		{
			_impl->registerAlias(alias_registerer);
		}

		ServiceResolvers ServiceRegisterer::getServiceResolvers() const
		{
			return _impl->getServiceResolvers(getServiceResolver());
		}

	}
}