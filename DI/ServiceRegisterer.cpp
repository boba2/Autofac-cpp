#include "ServiceRegisterer.h"

#include <algorithm>
#include "ContainerBuilder.h"
#include "Container.h"

namespace DI
{

	class ServiceRegisterer::Impl
	{
	public:	
		void addRegisterer(Details::ServiceRegistererPtr<> registerer)
		{
			_service_registerers.push_back(registerer);
		}

		Details::ServiceResolvers getServiceResolvers() const
		{
			auto resolvers = Details::ServiceResolvers();

			std::for_each(
				begin(_service_registerers), end(_service_registerers),
				[&resolvers](auto& registerer) { resolvers.merge(registerer->getServiceResolvers()); }
			);

			return resolvers;
		}

	private:
		std::vector<Details::ServiceRegistererPtr<>> _service_registerers;
	};

	ServiceRegisterer::ServiceRegisterer(ContainerBuilder& container_builder)
		: _impl(std::make_shared<Impl>()),
		_container_builder(container_builder)
	{
	}

	ServiceRegisterer::ServiceRegisterer(const ServiceRegisterer& other)
		: _impl(other._impl),
		_container_builder(other._container_builder)
	{
	}

	Container ServiceRegisterer::build() const
	{
		return _container_builder.build();
	}

	void ServiceRegisterer::addRegisterer(Details::ServiceRegistererPtr<> registerer)
	{
		_impl->addRegisterer(registerer);
	}

	Details::ServiceResolvers ServiceRegisterer::getServiceResolvers() const
	{
		return _impl->getServiceResolvers();
	}

}